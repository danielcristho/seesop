#!/bin/bash

input_username () {
  echo -n "Enter username: "
  read username

  if ! [ -d "users" ]
  then
    mkdir users
  fi

  if ! [ -f "users/user.txt" ]
  then
    touch users/user.txt
  fi
  user_num=$(awk '$1==temp {++n} END {print n}' temp="$username" users/user.txt)

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
}

input_password () {
  echo "Ketentuan Password:"
  echo -e "i.\tMinimal 8 karakter"
  echo -e "ii.\tMemiliki minimal 1 huruf kapital dan 1 huruf kecil"
  echo -e "iii.\tAlphanumeric"
  echo -e "iv.\tTidak boleh sama dengan username"
  echo -n "Enter Password: "
  read -s password

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

  echo "$username $password"  >> ./users/user.txt
  echo ""
  printf '%(%m/%d/%y %H:%M:%S)T ' >> log.txt
  printf "REGISTER: INFO User %s registered successfully\n" $username >> log.txt
} 

input_username
input_password