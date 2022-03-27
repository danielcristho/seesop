#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <dirent.h>

char *url = {"https://drive.google.com/uc?export=download&id=1YkmBhpfCQ3DBxeFmregqmwBs6Q2cy4BI"};
char *zipFile = {"animal.zip"};
char *unzipDST = {"/home/danielpepuho/modul2"};


int main(){
	pid_t child_id;
	int status;

	child_id = fork();

	if(child_id < 0){
		exit(EXIT_FAILURE);
	}

	if(child_id == 0){
		int child_id_2;
		child_id_2 = fork();

		if(child_id_2 < 0) exit(EXIT_FAILURE);

		if(child_id_2 == 0){
			char *argv[] = {"mkdir", "-p", "/home/danielpepuho/modul2/darat", NULL};
                	execv("/bin/mkdir", argv);
		}
		else{
			while ((wait(&status)) > 0);
                	sleep(3);
                	char *argv[] = {"mkdir", "-p", "/home/danielpepuho/modul2/air", NULL};
                	execv("/bin/mkdir", argv);
		}
	}
	else{
		int child_id_3;
		child_id_3 = fork();
		if(child_id_3 < 0) exit(EXIT_FAILURE);

		if(child_id_3 == 0){
			char *argv[] ={"wget", "--no-check-certificate", url[0], "-O",zipFile[0],"-q", NULL};
			execv("/usr/bin/wget", argv);
		}
		else{
			DIR *dir;
			struct dirent *entry;

			dir = opendir("/home/danielpepuho/modul2");
			while ( (entry=readdir(dir)) ){
				if ( strstr(entry->d_name, "darat") != NULL ){
					
				}
			}
		}
	}

	
}
