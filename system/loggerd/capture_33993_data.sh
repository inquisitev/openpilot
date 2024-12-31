timestamp=$(date +%d-%m-%Y_%H-%M-%S)
log_folder="/data/33993_log/data_from_clear_at_$timestamp"
mkdir $log_folder
cp /data/33993_log/uploader_log.txt $log_folder/
cp /data/33993_log/deleter_log.txt $log_folder/

(
  cd $log_folder
  du -sh /data/media/0/realdata > 'real_data_du.txt'
  sudo du -sh /data/media/lost+found > 'lost_and_found_du.txt'
  df -h > "df.txt"
  ls -alR /data/media/0/realdata > 'lsalr.txt'
  lsof /data/media/0/realdata > 'lsof.txt'
)
