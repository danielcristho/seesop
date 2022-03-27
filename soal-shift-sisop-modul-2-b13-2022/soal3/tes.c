#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>//for fork
#include <stdlib.h>//for exit
#include <unistd.h>//for fork, execv
#include <wait.h>
#include <dirent.h>//for dir
#include <string.h>

int is_file(const char*path){
	struct stat path_stat;
	stat(path, &path_stat);
	return S_ISREG(path_stat.st_mode);
}

int main(){
	pid_t child_id;
	int status;

	child_id = fork();

	if(child_id < 0){
		exit(EXIT_FAILURE);
	}

	if(child_id == 0){
		pid_t child_id_2;
		int status_2;
		child_id_2 = fork();

		if(child_id_2 < 0) exit(EXIT_FAILURE);

		if(child_id_2 == 0){
			char *argv[] = {"mkdir", "-p", "/home/james/modul2/darat", NULL};
                	execv("/bin/mkdir", argv);
		}
		else{
			while ((wait(&status_2)) > 0);
                	sleep(3);
                	char *argv[] = {"mkdir", "-p", "/home/james/modul2/air", NULL};
                	execv("/bin/mkdir", argv);
		}
	}
	else{
		while((wait(&status)) > 0);
		int status_3;
		pid_t child_id_3;
		child_id_3 = fork();
		if(child_id_3 < 0) exit(EXIT_FAILURE);

		if(child_id_3 == 0){
			char filePath[] = "./animal.zip";
			char pathUnzip[] = "/home/james/modul2";
			char *argv[] = {"unzip", filePath, "-d", pathUnzip, NULL};
			execv("/usr/bin/unzip", argv);
		}
		else{
			while((wait(&status_3)) > 0);
			DIR *folder;
			struct dirent *entry;

			folder = opendir("/home/james/modul2/animal");
			while ( (entry=readdir(folder)) ){
				if (fork() == 0){
					char fileName[300];
                                        snprintf(fileName, 300, "/home/james/modul2/animal/%s", entry->d_name);

					if ( strstr(entry->d_name, "darat" ) != NULL){
						char *argv[] = {"move", fileName, "/home/james/modul2/darat"};
						execv("/usr/bin/mv", argv);
                                	}
					else if (strstr(entry->d_name, "air") != NULL){
						char *argv[] = {"move", fileName, "/home/james/modul2/air"};
						execv("/usr/bin/mv", argv);
					}
					else{
						if(is_file(fileName) == 1){
							char *argv[] = {"remove", fileName};
                                                	execv("/usr/bin/rm", argv);
						}
					}

				}
			}
			closedir(folder);

			DIR *dir;
			struct dirent *ent;

			dir = opendir("/home/james/modul2/darat");
			while ( (ent=readdir(dir)) ){
				if(fork() == 0){
					char fileName[300];
					snprintf(fileName, 300, "/home/james/modul2/darat/%s", ent->d_name);
					if ( strstr(ent->d_name, "bird" ) != NULL){
                                                if(is_file(fileName) == 1){
                                                        char *argv[] = {"remove", fileName};
                                                        execv("/usr/bin/rm", argv);
                                                }

                                        }

				}
			}
			closedir(dir);

			/*pid_t child_id_4;
                        int status_4;
                        child_id_4 = fork();

                        if (child_id_4 == 0){
	                        char *argv[] = {"touch", "/home/james/modul2/air/list.txt"};
                                execv("/usr/bin/touch", argv);
			}
			else{
				while((wait(&status_4)) > 0);
				DIR *fol;
	                        struct dirent *e;
	                        fol = opendir("/home/james/modul2/air");
	                        while ( (ent=readdir(fol)) ){
					uid_t getuid(void);
                                        if(fork() == 0){
                                        	char fileName[300];
                                        	snprintf(fileName, 300, "/home/james/modul2/air/%s", ent->d_name);
						if ( is_file(fileName) == 1 ){
							if(S_IRUSR(fileName) && S_IWUSR(fileName) && S_IXUSR(fileName)){
								char *argv =  {/*IN PROGRESS}
							}
                                        	}

					}
				}
			}*/

		}

	}

}
