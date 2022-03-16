#!/bin/bash

input_login () {
  echo -n "Enter username: "
  read username
  echo -n "Enter password: "
  read -s password

  if ! [ -d "users" ]
  then
    mkdir users
  fi

  if ! [ -f "users/user.txt" ]
  then
    touch users/user.txt
  fi
  
  password_check=$(awk '$1==temp {print $2}' temp="$username" users/user.txt)
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
}

insert_command () {
  echo "Command List:"
  echo "1. dl N (N = jumlah gambar yang akan didownload)"
  echo "2. att"
  echo -n "Command: "
  read command n
  
  if [[ $command = "dl" ]]
  then
    check_zip
    download_files
  elif [[ $command = "att" ]]
  then 
    awk -v temp=$username '/LOGIN/&&$0~" " temp " " {++n; print} END {print "Login Attempt: " n}' log.txt
  fi
}

check_zip () {
  nama_folder=`printf '%(%Y-%m-%d)T'`_$username
  if [ -f "$nama_folder.zip" ]
  then 
    unzip -e $nama_folder.zip
    i=`ls ./$nama_folder | wc -l`
    n=$((n + i))
  else
    mkdir $nama_folder
    i=1
  fi
}
download_files () {
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
}

input_login
insert_command