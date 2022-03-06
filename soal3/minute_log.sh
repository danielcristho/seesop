#!/bin/bash

if [ ! -d "log" ]; then
mkdir -p "/home/{user}/log"
fi

MEMORY="$(free | awk '/Mem:/ {printf "%s,%s,%s,%s,%s,%s", $2,$3,$4,$5,$6,$7}')"
SWAP="$(free | awk '/Swap:/ {printf "%s,%s,%s", $2,$3,$4}')"
STORAGE="$(du -sh /home/ghani/ | awk '{printf "%s,%s",$2,$1}')"


OUTPUT=$(date "+%EY%m%d%H%M%S")

echo "mem_total,mem_used,mem_free,mem_shared,mem_buff,mem_available,swap_total,swap_used,swap_free,path,path_size" > /home/{user}/log/metrics_$OUTPUT.log
echo "$MEMORY,$SWAP,$STORAGE" >> /home/{user}/log/metrics_$OUTPUT.log

chmod u+x ./minute_log.sh
chmod 400 /home/{user}/log/metrics_$OUTPUT.log

# * * * * * /home/{user}/minute_log.sh
# B. Crontab nya 
