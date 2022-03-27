#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>


//definisikan
char *drive[] = {"https://drive.google.com/uc?export=download&id=15gUHyv8RsqB4F9ZRjocSE8b7YJzss5aS"};
char *zipfile[] = {"animal.zip"};
char *filename[] = {"animal"};
char *dir[] = {"darat", "air"};


void function() {
    pid_t mdir = fork() ;
    int statusmdir;

    if (mdir < 0) exit(EXIT_FAILURE);

        if (mdir == 0) { 
            //child process
            char *argv[] = {"mkdir", "-p", dir[0], dir[2], NULL };
            execv("/usr/bin/mkdir", argv);
        }
        else{
            while((wait(&statusmdir) > 0 ));
            pid_t child1 = fork();
            int status1;

            if(child1 < 0) exit(EXIT_FAILURE);

                if(child1 == 0) {
                    pid_t child2 = fork();
                    int status2;

                    if(child2 < 0) exit(EXIT_FAILURE); 

                    //download& unzip file
                    if(child2==0) {
                        pid_t child3 = fork();
                        int status3;

                        if(child3 < 0) exit(EXIT_FAILURE);

                        if(child3 == 0) {
                            char *argv[] = {"wget","-q", "--no-check-certificate",drive[0],"-O",zipfile[0], NULL};
                            execv("/usr/bin/wget", argv);
                        }
                        else {
                            while((wait(&status3)) > 0);
                            char *argv[] = {"unzip", filename[1], NULL};
                            execv("/usr/bin/unzip", argv);
                        }   

                    }
                else {
                    while((wait(&status1)) > 0);
                    pid_t child4 = fork();
                    int status4;

                    if(child4<0) exit(EXIT_FAILURE);

                    if(child4==0){
                    //pindahkan hewan *darat*
                    char *argv[] = {"mv","animal/*darat*", dir[0], NULL};
                    execv("/usr/bin/mv", argv);               
                    }
                    else{
                    //pindahkan *air*
                    while((wait(&status4)) > 0);
                    char *argv[] = {"mv","animal/*air*", dir[1], NULL};
                    execv("/usr/bin/mv", argv);    
                    }
                }
            }
    }
    else {

    }       