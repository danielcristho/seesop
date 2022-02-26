# soal-shift-sisop-modul-1-B13-2022
## Nomor 1
### source code: [click here!](https://gitlab.com/hufahamdika/soal-shift-sisop-modul-1-b13-2022/-/tree/main/soal1)

### Deskripsi soal:
Pada suatu hari, Han dan teman-temannya diberikan tugas untuk mencari foto. Namun,
karena laptop teman-temannya rusak ternyata tidak bisa dipakai karena rusak, Han dengan
senang hati memperbolehkan teman-temannya untuk meminjam laptopnya. Untuk
mempermudah pekerjaan mereka, Han membuat sebuah program.

### register.sh:
#### input_username:

```yml
echo -n "Enter username: "
read username
```
- membaca username dari input user

```yml
if ! [ -d "users" ]
then
  mkdir users
fi

if ! [ -f "users/user.txt" ]
then
  touch users/user.txt
fi
```
- membuat direktori users dengan perintah mkdir
- membuat file 'user.txt' untuk menyimpan setiap user yang telah terdaftar.

```yml
user_num=$(awk '$1==temp {++n} END {print n}' temp="$username" users/user.txt)
```
- mencari jumlah user dengan nama $username dari file users/user.txt dan masukkan ke variabel user_num

```yml
if [ -z "$user_num" ]
then
  user_num=0
fi

if [ $user_num -gt 0 ]
then
  echo "User sudah ada!"
  printf '%(%m/%d/%y %H:%M:%S)T REGISTER: ERROR User already exists\n' >> log.txt
  exit
fi
```
- jika user dengan nama $username tidak ditemukan, maka set variabel user_num menjadi 0
- jika user dengan nama $username ditemukan, maka print "MM/DD/YY hh:mm:ss REGISTER: ERROR User already exists" ke log.txt, lalu exit

#### input_password:

```yml
echo "Ketentuan Password:"
echo -e "i.\tMinimal 8 karakter"
echo -e "ii.\tMemiliki minimal 1 huruf kapital dan 1 huruf kecil"
echo -e "iii.\tAlphanumeric"
echo -e "iv.\tTidak boleh sama dengan username"
echo -n "Enter Password: "
read -s password
```
- membaca password dari input user

```yml
if [ ${#password} -lt 8 ]
then
  echo -e "\nPassword minimal harus 8 karakter!"
  exit
elif [[ $password = ${password,,} || $password = ${password^^} ]]
then
  echo -e "\nPassword harus memiliki minimal 1 huruf kapital dan 1 huruf kecil!"
  exit
elif [[ "$password" =~ [^a-zA-Z0-9] ]]
then 
  echo -e "\nPassword harus alphanumeric!"
  exit
elif [[ "$password" = "$username" ]]
then 
  echo -e "\nPassword tidak boleh sama dengan username!"
  exit
fi
```
- Jika password kurang dari 8 karakter, print "Password minimal harus 8 karakter!", lalu exit
- Jika password tidak ada minimal 1 huruf kapital atau huruf kecil, print "Password harus memiliki minimal 1 huruf kapital dan 1 huruf kecil!", lalu exit
- Jika password tidak alphanumeric, print "Password harus alphanumeric!", lalu exit
- Jika password sama dengan username, print "Password tidak boleh sama dengan username!", lalu exit

```yml
echo "$username $password"  >> ./users/user.txt
echo ""
printf '%(%m/%d/%y %H:%M:%S)T ' >> log.txt
printf "REGISTER: INFO User %s registered successfully\n" $username >> log.txt
```
- Jika proses registrasi berhasil, echo $username dan $password ke dalam users/user.txt
- Lalu, print "MM/DD/YY hh:mm:ss REGISTER: INFO User $username registered successfully" ke dalam log.txt

### main.sh:

#### input_login:

```yml
echo -n "Enter username: "
read username
echo -n "Enter password: "
read -s password
```
- Membaca username dan password dari input user

```yml
if ! [ -d "users" ]
then
  mkdir users
fi

if ! [ -f "users/user.txt" ]
then
  touch users/user.txt
fi
```
- membuat direktori users dengan perintah mkdir
- membuat file 'user.txt' untuk menyimpan setiap user yang telah terdaftar.

```yml
password_check=$(awk '$1==temp {print $2}' temp="$username" users/user.txt)
```
- Cari user dengan username pada users/user.txt dan masukkan passwordnya ke dalam variabel password_check

```yml
if ! [[ "$password" = "$password_check" ]]
then
  echo -e "\nPassword salah!"
  printf '%(%m/%d/%y %H:%M:%S)T ' >> log.txt
  printf "LOGIN: ERROR Failed login attempt on user %s \n" $username >> log.txt
  exit
fi

echo -e "\n\nSelamat datang, $username!"
printf '%(%m/%d/%y %H:%M:%S)T ' >> log.txt
printf "LOGIN: INFO User %s logged in\n" $username >> log.txt
```
- Jika password salah, print "MM/DD/YY hh:mm:ss LOGIN: ERROR Failed login attempt on user $username " ke dalam log.txt, lalu exit
- Jika password benar, print "MM/DD/YY hh:mm:ss LOGIN: INFO User $username logged in" ke dalam log.txt

#### insert_command:

```yml
echo "Command List:"
echo "1. dl N (N = jumlah gambar yang akan didownload)"
echo "2. att"
echo -n "Command: "
read command n
```
- Baca command dari user

```yml
if [[ $command = "dl" ]]
then
  check_zip
  download_files
```
- Jika commandnya "dl N", maka panggil fungsi check_zip untuk memeriksa apakah user memiliki zip dengan format nama yang sama atau tidak dan panggil fungsi download_files untuk mendownload file dari internet

```yml
elif [[ $command = "att" ]]
then 
  awk -v temp=$username '/LOGIN/&&$0~" " temp " " {++n; print} END {print "Login Attempt: " n}' log.txt
fi
```
- Jika commandnya "att", maka cari pada log.txt dengan pattern "LOGIN" dan "$username" di setiap kalimatnya dan print kalimat yang cocok dengan pattern tersebut ke dalam terminal
- Setelah perintah awk selesai dieksekusi print "Login Attempt: n" dengan n adalah jumlah kemunculan kalimatnya

#### check_zip:

```yml
nama_folder=`printf '%(%Y-%m-%d)T'`_$username
```
- Masukkan hasil `printf "YYYY-MM-DD"`_$username ke dalam variabel nama_folder

```yml
if [ -f "$nama_folder.zip" ]
then 
  unzip -e $nama_folder.zip
  i=`ls ./$nama_folder | wc -l`
  n=$((n + i))
```
- Jika file dengan nama $nama_folder.zip ditemukan, unzip file tersebut
- Hitung jumlah file di dalam folder $nama_folder dengan cara menjalankan perintah ls untuk mendapatkan daftar file yang ada di dalam folder $nama_folder lalu masukkan daftar tersebut sebagai input perintah wc dengan parameter -l untuk menghitung jumlah barisnya
- Hasil perintah wc yang didapatkan kemudian di masukkan ke variabel i
- Variabel n yang tadi diinput user ditambah dengan i

```yml
else
  mkdir $nama_folder
  i=1
fi
```
- Jika file dengan nama $nama_folder.zip tidak ditemukan, buat directory/folder $nama_folder dan set i menjadi 1

#### download_files

```yml
while [ $i -le $n ]
do
  if [ $i -lt 10 ]
  then
    wget https://loremflickr.com/320/240 -O $nama_folder/PIC_0$i
  else
    wget https://loremflickr.com/320/240 -O $nama_folder/PIC_$i
  fi
  ((i++))
done
zip -r -e $nama_folder $nama_folder
rm -r $nama_folder
```
- Loop sebanyak n kali, kemudian di dalam loop:
  - Jika i kurang dari 10, maka download gambar dari https://loremflickr.com/320/240 dan masukkan ke dalam folder $nama_folder dengan nama PIC_0$i
  - Jika i lebih dari atau sama dengan 10, maka download gambar dari https://loremflickr.com/320/240 dan masukkan ke dalam folder $nama_folder dengan nama PIC_$i
  - i ditambah dengan 1
- Saat loop selesai, zip folder $nama_folder menjadi $nama_folder.zip dengan password disetting oleh user
- Remove folder $nama_folder


## Nomor 2
### source code: [click here!](https://gitlab.com/hufahamdika/soal-shift-sisop-modul-1-b13-2022/-/tree/main/soal2)
### Deskripsi soal:

Pada tanggal 22 Januari 2022, website https://daffa.info di hack oleh seseorang yang tidak
bertanggung jawab. Sehingga hari sabtu yang seharusnya hari libur menjadi berantakan.
Dapos langsung membuka log website dan menemukan banyak request yang berbahaya.
Bantulah Dapos untuk membaca log website https://daffa.info Buatlah sebuah script awk
bernama "soal2_forensic_dapos.sh" untuk melaksanakan tugas-tugas berikut:

### soal2_forensic_dapos.sh:
#### A. Membuat directory dengan nama forensic_log_website_daffainfo_log

```yml
folder=forensic_log_website_daffainfo_log
```
- Membuat variable folder untuk mempermudah

```yml
if [ -d "$folder" ]
```
- Melakukan pengeceken apakah folder tersebut sudah ada

```yml
then
  rm -rf "$folder"
  mkdir "$folder"
else
  mkdir "$folder"
fi

```
- Apabila sudah ada maka folder akan dihapus dan dibuat folder baru dengan nama yang sama
- Apabila belum maka akan dibuat folder baru

#### B. Mencari tahu rata-rata request perjam yang dilakukan penyerang

```yml
cat log_website_daffainfo.log | awk -F: 'NR>=2{count[$3]++} END {for (c in count){res++} printf "rata-rata serangan adalah sebanyak %f request per jam", (NR-1)/res}' | uniq > $folder/ratarata.txt
```
- `cat log_website_daffainfo.log` digunakan untuk menyalin isi dari log
- Mencari tahu pada jam berapa saja penyerangan dilakukan dan menghitung berapa lama
- `(NR-1)/res` digunakan untuk melakukan perhitungan rata-rata
- `> $folder/ratarata.txt` digunakan untuk memasukkan hasil ke dalam file rata-rata.txt 

#### C. Mencari tahu IP yang paling banyak melakukan request dan berapa jumlah request yang dilakukan

```yml
cat log_website_daffainfo.log | awk -F: 'NR>=2{print $1}' | cut -d\" -f2 | sort | uniq -c | sort -rn | awk 'NR==1 {printf "IP yang paling banyak mengakses server adalah: %s sebanyak %s request\n\n", $2, $1}' > $folder/result.txt
```
- Melakukan sorting IP yang melakukan request dengan urutan dari yang paling banyak `awk -F: 'NR>=2{print $1}' | cut -d\" -f2 | sort | uniq -c | sort -rn`
- Melakukan selection dan mencetak hasil dengan `awk 'NR==1 {printf "IP yang paling banyak mengakses server adalah: %s sebanyak %s request\n\n", $2, $1}'`
- Memasukkan hasil ke dalam file result.txt

#### D. Mencari tahu seberapa banyak request yang menggunakan user-agent "curl"

```yml
cat log_website_daffainfo.log | awk '/curl/ {++n} END {printf "Ada %d request yang menggunakan curl sebagai user-agent\n\n", n}' >> $folder/result.txt
```
- Menghitung seberapa banyak "curl" muncul dalam log dengan `awk '/curl/ {++n} `
- Mencetak dan menambahkan hasil ke dalam file result.txt `END {printf "Ada %d request yang menggunakan curl sebagai user-agent\n\n", n}' >> $folder/result.txt`

#### E. Mencari tahu IP address yang melakukan request pada tanggal 22 dan pada jam 02

```yml
cat log_website_daffainfo.log | awk -F: '{if($2 ~ /22\// && $3 ~ /02/) {print $1}}' | sort | uniq | cut -d\" -f2 >> $folder/result.txt
```
- Melakukan pengecekan apabila ada request pada tanggal 22 dan jam 02 `if($2 ~ /22\// && $3 ~ /02/`
- Mencetak IP address unique (tidak ada yang sama) yang sesuai dengan kondisi diatas secara berurutan `{print $1}}' | sort | uniq | cut -d\" -f2`
- Mencetak dan menambahkan hasil ke dalam file result.txt

## Nomor 3
### source code: [click here!](https://gitlab.com/hufahamdika/soal-shift-sisop-modul-1-b13-2022/-/tree/main/soal3)
### Deskripsi soal:

Buatlah program monitoring resource pada komputer kalian. Cukup monitoring ram dan monitoring size suatu directory. Untuk ram gunakan command `free -m`. Untuk disk gunakan command `du -sh <target_path>`. Catat semua metrics yang didapatkan dari hasil `free -m`. Untuk hasil `du -sh <target_path>` catat size dari path directory tersebut. Untuk target_path yang akan dimonitor adalah /home/{user}/.

### A 

Di poin ini, kami diminta untuk membuat sebuah log file dengan format metrics_{YmdHms}.log. Berikut syntax yang digunakan: 

    OUTPUTPATH="log/metrics$(date +"%Y%m%d%H%M%S").log" 
    if [ ! -d "log" ]; then mkdir log
    fi

Fungsi if berfungsi untuk membuat directory baru berupa file log jika belum ada.

Lalu untuk program monitoring resourcenya:

    echo \ "mem_total,mem_used,mem_free,mem_shared,mem_buff,mem_available,swap_total,swap_used,swap_free,path,path_size" \ 
    >$Output 

    MEMORY="$(free | awk '/Mem:/ {print $2","$3","$4","$5","$6","$7}')"
    SWAP="$(free | awk '/Swap:/ {printf $2","$3","$4}')"
    STORAGE="$(du -sh ~ /home/{user}/ | awk '{printf $2","$1}')"

    echo "$MEMORY,$SWAP,$STORAGE" >> $Output

Dimana echo untuk print out keterangan-keterangannya. Lalu di dalam MEMORY, SWAP, dan STORAGE menggunakan metode awk untuk mendapatkan data dari beberapa variabel di memory dan storage (command free untuk melihat isi ram dan du -sh untuk melihat isi storage.) dan echo terakhir untuk print hasil dari scan awk tersebut. Jangan lupa untuk mengganti /home/{user}/ menjadi user sendiri.

## Anggota Kelompok
| Nama                      | NRP      |
|---------------------------|----------|
|Abidjana Zulfa Hamdika     |5025201197|
|Brian Akbar Wicaksana      |5025201207|
|Gloriyano C. Daniel Pepuho |5025201121|
|Muhammad Ghani Taufiqurr   |5025201110|
