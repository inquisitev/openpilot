#!/usr/bin/env python3
import os
import shutil
import datetime
ct = datetime.datetime.now()
ts = ct.timestamp()
time_stamp = datetime.datetime.fromtimestamp(ts).strftime('%Y_%m_%d_%H_%M_%S')
folder = os.path.join('/', 'data', 'media', '0', 'realdata')
deleter_log_path = os.path.join("/", "data", "33993_log", "deleter_log")
deleter_path_on_clear = f"{deleter_log_path}_{time_stamp}.txt"
shutil.copy(f"{deleter_log_path}.txt", deleter_path_on_clear)
uploader_log_path = os.path.join("/", "data", "33993_log", "uploader_log")
uploader_path_on_clear = f"{uploader_log_path}_{time_stamp}.txt"
shutil.copy(f"{uploader_log_path}.txt", uploader_path_on_clear)
for filename in os.listdir(folder):
    file_path = os.path.join(folder, filename)
    try:
        if os.path.isfile(file_path) or os.path.islink(file_path):
            os.unlink(file_path)
        elif os.path.isdir(file_path):
            shutil.rmtree(file_path)
    except Exception as e:
        print('Failed to delete %s. Reason: %s' % (file_path, e))
