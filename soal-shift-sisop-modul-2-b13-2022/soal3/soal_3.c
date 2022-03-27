#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <time.h>
#include <dirent.h>


char *dirName[] = {"darat", "air"};
char *url[] = {"https://drive.google.com/uc?export=download&id=1YkmBhpfCQ3DBxeFmregqmwBs6Q2cy4BI"};
char *zipFile[] = {"animal.zip"};
char *fileName[] = {"animal"};

int main() {
    pid_t tuna = fork();
    int statustuna;

    if(tuna < 0 ) exit(EXIT_FAILURE);

        if(tuna == 0) {
            pid_t tiger = fork();
            int statustiger;

            if(tiger < 0) exit(EXIT_FAILURE);

            if(tiger == 0) {
                char *argv[]={"mkdir", "-p",dirName[0],dirName[1], NULL};
                execv("/usr/bin/mkdir", argv);
            }   
                

            else {
                while((wait(&statustiger)) > 0);
                pid_t child1 = fork();
                int status1;

                if(child1 < 0) exit(EXIT_FAILURE);

                if(child1 == 0){
                    pid_t child2 = fork();
                    int status2;

                    if(child2 < 0) exit(EXIT_FAILURE);

                    if(child2 == 0) { //download & unzip animal.zip
                        pid_t child3 = fork();
                        int status3;

                        if(child3 < 0) exit(EXIT_FAILURE);

                        if(child3 == 0) {
                            char *argv[] = {"wget", "--no-check-certificate", url[0], "-O",zipFile[0], NULL};
                            execv("/bin/wget", argv);
                        }
                            else{
                                while((wait(&status3)) > 0);
                                char *argv[] = {"unzip","-qq", zipFile[0], NULL};
                                execv("/bin/unzip", argv);
                        }
                        
                    }
                    else{
                        while((wait(&status2)) > 0);
                        //move file dan rm
                        DIR *moveDir;
                        struct dirent *ep;
                        moveDir = opendir("/home/danielpepuho/modul2/");
                        char foto[100];
                        while ((ep=readdir(moveDir))){
                            if( fork() == 0) {
                                    if (strstr(ep->d_name, ".jpg")) {
                                        snprintf(foto, 100,"/home/danielpepuho/modul2/%s", ep->d_name);
                                        if (strstr(ep->d_name,"darat")) {
                                            char *argv6[] = {"mv", foto, "/home/danielpepuho/modul2/darat/",NULL};
                                            execv("/bin/mv", argv6);
                                        }else if (strstr(ep -> d_name, "air")){
                                            char *argv6[] = {"mv",foto, "/home/danielpepuho/modul2/air/",NULL};
                                            execv("/bin/mv", argv6);
                                        }else{
                                            char *argv6[] = {"rm", foto,NULL};
                                            execv("/bin/rm",argv6);
                                        }
                                    }
                                }
                                (void) closedir(moveDir);
                        }          
                    }
                }                       
                
            }     
        }
        return 0;
    }
}    


// void rmFile() {
//     pid_t salmon = fork();
//     int statussalmon;

//     if(salmon < 0) exit(EXIT_FAILURE);
    
//     if(salmon == 0) {

//         pid_t child6 = fork();
//             int status6;

//             if(child6 < 0) exit(EXIT_FAILURE);

//             if(child6) { //rm bird
//                 char *argv[] = {"rm", "/darat/*bird*", NULL};
//                 execv("/usr/bin/rm", argv);
//             }
//             else{
//                 while ((wait(&status6)) > 0);
//                 char *argv[] = {"rm", "/animal/*frog*", NULL};
//                 execv("/usr/bin/rm", argv);
//             }
//     }
//     else{
//         while((wait(&statussalmon)) > 0);
//     }
    
// }