#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

void jalankan(char *perintah, char*argv[]){
    int status=0;
    if(fork()==0)
        execv(perintah, argv);
    while(wait(&status)>0);
}

int main()
{   
    int getlogin_r(char *buf, size_t bufsize);

    char *argv[] = {"mkdir", "-p", "/home/ubuntu/modul2/", NULL};
    jalankan("/bin/mkdir", argv);

    char *argv1[] = {"mkdir", "-p", "/home/ubuntu/modul2/darat", NULL};
    jalankan("/bin/mkdir", argv1);
    sleep(3);

    char *argv2[] = {"mkdir", "-p", "/home/ubuntu/modul2/air", NULL};
    jalankan("/bin/mkdir", argv2);

    char *argv3[] = {"unzip", "-j", "/home/ubuntu/modul2/animal.zip", "-d", "/home/ubuntu/modul2/", NULL};
    jalankan("/bin/unzip", argv3);

    DIR *dp;
    struct dirent *ep;
    
    dp = opendir("/home/ubuntu/modul2/");

    char filename[100];
    if (dp != NULL)
    {
        while ((ep = readdir (dp))) {
            if (strstr(ep->d_name, ".jpg")){
                snprintf(filename, 100, "/home/ubuntu/modul2/%s", ep->d_name);
                if (strstr(ep->d_name, "darat")){
                    char *argv6[] = {"mv", filename, "/home/ubuntu/modul2/darat/", NULL};
                    jalankan("/bin/mv", argv6);
                }else if (strstr(ep->d_name, "air")){
                    char *argv6[] = {"mv", filename, "/home/ubuntu/modul2/air/", NULL};
                    jalankan("/bin/mv", argv6);
                }else{
                    char *argv6[] = {"rm", filename, NULL};
                    jalankan("/bin/rm", argv6);
                }
            }
        }
        (void) closedir (dp);
    } else perror ("Couldn't open the directory");

    DIR *dp2;
    struct dirent *ep2;

    dp2 = opendir("/home/ubuntu/modul2/darat/");

    if (dp2 != NULL)
    {
        while ((ep2 = readdir(dp2))) {
            if (strstr(ep2->d_name, "bird")){
                snprintf(filename, 100, "/home/ubuntu/modul2/darat/%s", ep2->d_name);
                char *argv7[] = {"rm", filename, NULL};
                jalankan("/bin/rm", argv7);
            }
        }
        (void) closedir (dp2);
    } else perror ("Couldn't open the directory");
    

    DIR *dp3;
    FILE * fptr;
    struct dirent *ep3;
    uid_t getuid(void);
    struct stat fs;
    int r;

    dp3 = opendir("/home/ubuntu/modul2/air/");

    fptr = fopen("/home/ubuntu/modul2/air/list.txt", "a+");
    if (dp3 != NULL)
    {
        while ((ep3 = readdir (dp3))) {
            snprintf(filename, 100, "/home/ubuntu/modul2/darat/%s", ep3->d_name);

            r = stat(filename,&fs);
            if( r==-1 )
            {
                fprintf(stderr,"File error\n");
                exit(1);
            }

            if (strstr(ep3->d_name, ".jpg")){
                fputs(getuid(), fptr);
                
            if( S_ISREG(fs.st_mode) )
                fputs("d", fptr);
            else
                fputs("-", fptr);

            if( fs.st_mode & S_IRUSR ) fputs("read ", fptr);
            else fputs("-", fptr);

            if( fs.st_mode & S_IWUSR ) fputs("write ", fptr);
            else fputs("-", fptr);

            if( fs.st_mode & S_IXUSR ) fputs("execute", fptr);
            else fputs("-", fptr);

            if( fs.st_mode & S_IRGRP ) fputs("read ", fptr);
            else fputs("-", fptr);

            if( fs.st_mode & S_IWGRP ) fputs("write ", fptr);
            else fputs("-", fptr);

            if( fs.st_mode & S_IXGRP ) fputs("execute", fptr);
            else fputs("-", fptr);
            
            if( fs.st_mode & S_IROTH ) fputs("read ", fptr);
            else fputs("-", fptr);

            if( fs.st_mode & S_IWOTH ) fputs("write ", fptr);
            else fputs("-", fptr);
            
            if( fs.st_mode & S_IXOTH ) fputs("execute", fptr);
            else fputs("-", fptr);

            fputs(ep3->d_name, fptr);
            fputs("\n", fptr);
            }
        }
        fclose(fptr);
        (void) closedir (dp3);
    } else perror ("Couldn't open the directory");

    return 0;
}