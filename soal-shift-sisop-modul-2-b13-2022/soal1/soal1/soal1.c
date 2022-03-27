#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <signal.h>   

int main(){

    // A

    char link[2][500] = {
        "https://docs.google.com/uc?export=download&id=1XSkAqqjkNmzZ0AdIZQt_eWGOZ0eJyNlT", //Weapon Link
        "https://docs.google.com/uc?export=download&id=1xYYmsslb-9s8-4BDvosym7R4EmPi6BHp" //Char Link
    };

    char name[2][50] = {
        "Weapons.zip","Characters.zip"
    };

    for(int i=0;i<2;i++){
        if(fork == 0){
            char *argv[] = {"wget",link[i],"-O",name[i],NULL};
            execv("/usr/local/bin/wget",argv);
        }
    }
    while(wait(NULL)>=0);

    for(int i=0;i<2;i++){
        if(fork == 0){
            char *argv[] = {"unzip",name[i],NULL};
            execv("/usr/bin/unzip",argv);
        }
    }
    while(wait(NULL)>=0);


    for(int i=0;i<2;i++){
        if(fork == 0){
            char *argv[] = {"rm",name[i],NULL};
            execv("/usr/bin/rm",argv);
        }
    }

  if (fork == 0){
    char *argvGacha[] = {"mkdir","gacha_gacha",NULL};
    execv("/usr/bin/mkdir",argvGacha);
  }
   wait(NULL);



}
