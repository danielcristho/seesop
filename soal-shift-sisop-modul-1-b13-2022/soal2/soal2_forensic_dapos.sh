#! bin/bash

folder=forensic_log_website_daffainfo_log

#A
if [ -d "$folder" ]
then
	rm -rf "$folder"
	mkdir "$folder"
else
	mkdir "$folder"	
fi

#B
cat log_website_daffainfo.log | awk -F: 'NR>=2{count[$3]++} END {for (c in count){res++} printf "rata-rata serangan adalah sebanyak %f request per jam", (NR-1)/res}' | uniq > $folder/ratarata.txt

#C
cat log_website_daffainfo.log | awk -F: 'NR>=2{print $1}' | cut -d\" -f2 | sort | uniq -c | sort -rn | awk 'NR==1 {printf "IP yang paling banyak mengakses server adalah: %s sebanyak %s request\n\n", $2, $1}' > $folder/result.txt

#D
cat log_website_daffainfo.log | awk '/curl/ {++n} END {printf "Ada %d request yang menggunakan curl sebagai user-agent\n\n", n}' >> $folder/result.txt

#E
cat log_website_daffainfo.log | awk -F: '{if($2 ~ /22\// && $3 ~ /02/) {print $1}}' | sort | uniq | cut -d\" -f2 >> $folder/result.txt
