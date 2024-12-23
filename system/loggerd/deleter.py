#!/usr/bin/env python3
import os
import shutil
import threading
import datetime
from openpilot.system.hardware.hw import Paths
from openpilot.common.swaglog import cloudlog
from openpilot.system.loggerd.config import get_available_bytes, get_available_percent
from openpilot.system.loggerd.uploader import listdir_by_creation
from openpilot.system.loggerd.xattr_cache import getxattr

MIN_BYTES = 5 * 1024 * 1024 * 1024
MIN_PERCENT = 20

DELETE_LAST = ['boot', 'crash']

PRESERVE_ATTR_NAME = 'user.preserve'
PRESERVE_ATTR_VALUE = b'1'
PRESERVE_COUNT = 5

# Configure logging
import logging
from logging.handlers import RotatingFileHandler
log_file_path = '/data/33993_log/deleter_log.txt'
# Make sure the log directory exists
os.makedirs(os.path.dirname(log_file_path), exist_ok=True)
logger = logging.getLogger('deleter')
logger.setLevel(logging.DEBUG)
handler = RotatingFileHandler(log_file_path, maxBytes=100*1024*1024, backupCount=20)
formatter = logging.Formatter('%(asctime)s - %(levelname)s - [%(filename)s:%(lineno)d] - %(message)s')
handler.setFormatter(formatter)
logger.addHandler(handler)


def has_preserve_xattr(d: str) -> bool:
  # this is annoying
  # logger.debug(f"Checking preserve xattr for directory: {d}")
  return getxattr(os.path.join(Paths.log_root(), d), PRESERVE_ATTR_NAME) == PRESERVE_ATTR_VALUE


def get_preserved_segments(dirs_by_creation: list[str]) -> list[str]:
  logger.debug("Getting preserved segments")
  preserved = []
  for n, d in enumerate(filter(has_preserve_xattr, reversed(dirs_by_creation))):
    if n == PRESERVE_COUNT:
      break
    date_str, _, seg_str = d.rpartition("--")

    # ignore non-segment directories
    if not date_str:
      continue
    try:
      seg_num = int(seg_str)
    except ValueError:
      continue

    # preserve segment and two prior
    for _seg_num in range(max(0, seg_num - 2), seg_num + 1):
      preserved.append(f"{date_str}--{_seg_num}")

  logger.debug(f"Preserved segments: {preserved}")
  return preserved


def deleter_thread(exit_event):
  available_percent = get_available_percent(default=MIN_PERCENT + 1)
  logger.debug("Starting deleter thread")
  while not exit_event.is_set():
    logger.debug(f"Checking available space: {available_percent}")
    out_of_bytes = get_available_bytes(default=MIN_BYTES + 1) < MIN_BYTES
    logger.debug(f"Out of bytes: {out_of_bytes}, min is {MIN_BYTES}")
    out_of_percent = get_available_percent(default=MIN_PERCENT + 1) < MIN_PERCENT
    logger.debug(f"Out of percent: {out_of_percent}, min is {MIN_PERCENT}")

    if out_of_percent or out_of_bytes:
      # Log reason for deletion
      if out_of_bytes:
        logger.info(f"Deleting logs due to low disk space (bytes)")
      if out_of_percent:
        logger.info(f"Deleting logs due to low disk space (percent)")
      dirs = listdir_by_creation(Paths.log_root())
      logger.debug(f"Directories: {dirs}")

      # skip deleting most recent N preserved segments (and their prior segment)
      preserved_dirs = get_preserved_segments(dirs)
      logger.debug(f"Preserved directories: {preserved_dirs}")

      ct = datetime.datetime.now()
      ts = ct.timestamp()
      time_stamp = datetime.datetime.fromtimestamp(ts).strftime('%Y_%m_%d_%H_%M_%S')
      lsof_path = os.path.join("/", "data", "33993_log", f"lsof_from_del_attempt_{time_stamp}_before_deleter.txt")
      logger.debug(f"executing lsof /data/media/0/realdata > {lsof_path}")
      os.system(f"echo 'ls | wc' BEGIN: >> {lsof_path}")
      os.system(f"ls | wc >> {lsof_path}")
      os.system(f"echo lsof BEGIN: >> {lsof_path}")
      os.system(f"lsof /data/media/0/realdata >> {lsof_path}")
      # remove the earliest directory we can
      for delete_dir in sorted(dirs, key=lambda d: (d in DELETE_LAST, d in preserved_dirs)):
        delete_path = os.path.join(Paths.log_root(), delete_dir)
        logger.debug(f"Attempting to delete {delete_path}")

        if any(name.endswith(".lock") for name in os.listdir(delete_path)):
          logger.debug("not deleting because there is a lock file")
          continue

        try:
          cloudlog.info(f"deleting {delete_path}")
          logger.info(f"Deleting {delete_path}")
          if os.path.isfile(delete_path):
            logger.debug(f"Deleting file: {delete_path}")
            os.remove(delete_path)
            logger.debug(f"Deleted file: {delete_path}")
          else:
            logger.debug(f"Deleting directory: {delete_path}")
            shutil.rmtree(delete_path)
            logger.debug(f"Deleted directory: {delete_path}")
          break
        except OSError as e:
          logger.info("cloudlog.exception")
          cloudlog.exception(f"issue deleting {delete_path}")
          logger.exception(f"Issue deleting {delete_path}. {e}, {e.strerror}", exc_info=True)
        except Exception as e:
            logger.exception(f"Unexpected issue deleting {delete_path}: {e}", exc_info=True)
            raise

      os.system(f"echo lsof END: > {lsof_path}")
      lsof_path = os.path.join("/", "data", "33993_log", f"lsof_from_del_attempt_{time_stamp}_after_deleter.txt")
      os.system(f"lsof /data/media/0/realdata >> {lsof_path}")
      os.system(f"ls | wc >> {lsof_path}")
      exit_event.wait(.1)
      logger.debug("setting exit event")
    else:
      logger.debug("Sleeping")
      exit_event.wait(30)
      logger.debug("Waking up")

    logger.debug("loop finished")
  logger.debug("thread finished")


def main():
  logger.debug("Starting deleter thread")
  try:
      exit_event = threading.Event()
      deleter_thread(exit_event)
  except Exception as e:
      logger.exception(f"Deleter thread encountered an unexpected exception: {e}", exc_info=True)
  finally:
      logger.info("Deleter thread exiting, either gracefully or due to an error")


if __name__ == "__main__":
  main()
