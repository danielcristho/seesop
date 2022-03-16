#!/bin/bash
OUTPUT=$(date "+%Y%m%d%H")

max_mem_total=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{print $1}' | sort | tail -1)
min_mem_total=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{print $1}' | sort | head -1)
avg_mem_total=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{ total += $1; count++ } 
END { print total/count }')
avg_mem_total=${avg_mem_total/,/.}

max_mem_used=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{print $2}' | sort | tail -1)
min_mem_used=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{print $2}' | sort | head -1)
avg_mem_used=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{ total += $2; count++ } 
END { print total/count }')
avg_mem_used=${avg_mem_used/,/.}

max_mem_free=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{print $3}' | sort | tail -1)
min_mem_free=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{print $3}' | sort | head -1)
avg_mem_free=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{ total += $3; count++ } 
END { print total/count }')
avg_mem_free=${avg_mem_free/,/.}

max_mem_shared=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{print $4}' | sort | tail -1)
min_mem_shared=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{print $4}' | sort | head -1)
avg_mem_shared=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{ total += $4; count++ } 
END { print total/count }')
avg_mem_shared=${avg_mem_shared/,/.}

max_mem_buff=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{print $5}' | sort | tail -1)
min_mem_buff=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{print $5}' | sort | head -1)
avg_mem_buff=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{ total += $5; count++ } 
END { print total/count }')
avg_mem_buff=${avg_mem_buff/,/.}

max_mem_avail=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{print $6}' | sort | tail -1)
min_mem_avail=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{print $6}' | sort | head -1)
avg_mem_avail=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{ total += $6; count++ } 
END { print total/count }')
avg_mem_avail=${avg_mem_avail/,/.}

max_swap_total=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{print $7}' | sort | tail -1)
min_swap_total=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{print $7}' | sort | head -1)
avg_swap_total=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{ total += $7; count++ } 
END { print total/count }')
avg_swap_total=${avg_swap_total/,/.}

max_swap_used=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{print $8}' | sort | tail -1)
min_swap_used=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{print $8}' | sort | head -1)
avg_swap_used=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{ total += $8; count++ } 
END { print total/count }')
avg_swap_used=${avg_swap_used/,/.}

max_swap_free=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{print $9}' | sort | tail -1)
min_swap_free=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{print $9}' | sort | head -1)
avg_swap_free=$(cat /home/{user}/log/metrics_$OUTPUT*.log | grep /home/ | awk -F "," '{ total += $9; count++ } 
END { print total/count }')
avg_swap_free=${avg_swap_free/,/.}

echo "type,mem_total,mem_used,mem_free,mem_shared,mem_buff,mem_available,swap_total,swap_used,swap_free,path,path_size" > /home/{user}/log/metrics_agg_$OUTPUT.log
echo "minimum,$min_mem_total,$min_mem_used,$min_mem_free,$min_mem_shared,$min_mem_buff,$min_mem_avail,$min_swap_total,$min_swap_used,$min_swap_free,/home/{user}/,$min_path_size" >> /home/{user}/log/metrics_agg_$OUTPUT.log
echo "maximum,$max_mem_total,$max_mem_used,$max_mem_free,$max_mem_shared,$max_mem_buff,$max_mem_avail,$max_swap_total,$max_swap_used,$max_swap_free,/home/{user}/,$max_path_size" >> /home/{user}/log/metrics_agg_$OUTPUT.log
echo "average,$avg_mem_total,$avg_mem_used,$avg_mem_free,$avg_mem_shared,$avg_mem_buff,$avg_mem_avail,$avg_swap_total,$avg_swap_used,$avg_swap_free,/home/{user}/,$avg_path_size" >> /home/{user}/log/metrics_agg_$OUTPUT.log

chmod u+x ./aggregate_minutes_to_hourly_log.sh
chmod 400 /home/{user}/log/metrics_agg_$OUTPUT.log

# 59 * * * * /home/{user}/aggregate_minutes_to_hourly_log.sh
# C. Crontab nya ^
