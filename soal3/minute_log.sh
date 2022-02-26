OUTPUT_PATH="metrics_$(date +"%Y%m%d%H%M%S").log" 

if [ ! -d "log" ]; then mkdir log
fi

echo "mem_total,mem_used,mem_free,mem_shared,mem_buff,mem_available,swap_total,swap_used,swap_free,path,path_size" \
> $OUTPUT_PATH

MEMORY ="$(free | awk '/Mem:/ {Printf "%s,%s,%s,%s,%s,%s", $2,$3,$4,$5,$6,$7}')"
SWAP ="$(free | awk '/Swap:/ {pPrintf "%s,%s,%s", $2,$3,$4}')"
STORAGE ="$(du -sh /home/{user}/ | awk '{Printf "%s,%s",$2,$1}')"

echo "$MEMORY,$SWAP,$STORAGE" >> $OUTPUT_PATH  
