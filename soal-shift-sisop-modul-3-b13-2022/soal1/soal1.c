#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pthread.h>

char *url_music = "https://drive.google.com/uc?id=1_djk0z-cx8bgISFsMiUaXzty2cT4VZp1&export=download";
char *url_quote = "https://drive.google.com/uc?id=1jR67_JAyozZPs2oYtYqEZxeBLrs-k3dt&export=download";

pid_t CreateChildProcess();
void Execute(char *argv[], char command[]);
void CheckThreadError(int iret);
void *ExtractFiles(void *arg);
void ChangeWorkingDirectory(const char *dir);
void ZipFiles(char *pass, char *source);
void CreateFolder(char folder_name[]);
void RemoveFile(char file[]);
void MoveFile(char source[], char destination[]);
void DownloadFile(char *url, char *output);
void *CreateTextFile(void *arg);
void ProcessUnzipFiles();
void ProcessAddTextFile();
void DecodeBase64(char *name, char *output);
void *ScanDirectory(void *directory);
void ProcessDecode();
void ProcessZipFiles();

int main() {
	DownloadFile(url_music, "music.zip");
	DownloadFile(url_quote, "quote.zip");
	ProcessUnzipFiles();
	ProcessDecode();
	ProcessZipFiles();
	ProcessAddTextFile();
	ProcessZipFiles();
}

pid_t CreateChildProcess() {

 	pid_t child_id = fork();

  	if (child_id < 0) {
    		exit(EXIT_FAILURE); 
  	}
  	
  	return child_id;
}

void Execute(char *argv[], char command[]) {
	int status;

	int fd[2];
	
	char output[50];

	pid_t child_id = CreateChildProcess();
	
	if (child_id == 0) {
		execv(command, argv);
	}
	while ((wait(&status)) > 0);
}

void CheckThreadError(int iret) {
	if(iret) {
        	fprintf(stderr,"Error - pthread_create() return code: %d\n",iret);
        	exit(EXIT_FAILURE);
    	}
}

void *ExtractFiles(void *arg) {
	char **argv_f = (char**) arg;
  	char *argv[] = {"unzip", argv_f[0], "-d", argv_f[1], NULL};
  	Execute(argv, "/usr/bin/unzip");  	
}

void ChangeWorkingDirectory(const char *dir) {
	if ((chdir(dir)) < 0) {
  		exit(EXIT_FAILURE);
	}
}

void ZipFiles(char *pass, char *source) {
	ChangeWorkingDirectory(source);
	char destination[30] = "../";
	strcat(destination, source);
	char *argv[] = {"zip", "-r", "-P", pass, destination, ".", NULL};
	Execute(argv, "/usr/bin/zip");  
	ChangeWorkingDirectory("../");
}

void CreateFolder(char folder_name[]) {
	char *argv[] = {"mkdir", "-p", folder_name, NULL};
	Execute(argv, "/usr/bin/mkdir");
}

void RemoveFile(char file[]) {
	char *argv[] = {"remove", "-r", file, NULL};
    	Execute(argv, "/usr/bin/rm");
}

void MoveFile(char source[], char destination[]) {
  	char *argv[] = {"cp", source, destination, NULL};
  	Execute(argv, "/bin/cp"); 
  	
  	RemoveFile(source);
}

void DownloadFile(char *url, char *output) {
	char *argv[] = {"wget", url, "-O", output};
	Execute(argv, "/usr/bin/wget");  
}

void *CreateTextFile(void *arg) {
	char **argv = (char**) arg;
	char *name = argv[0];
	char *contents = argv[1];

	FILE *file = fopen(name, "w");
	
	fprintf(file, "%s", contents);
	
	fclose(file);
}

void ProcessUnzipFiles() {
	pthread_t thread1, thread2;
    	int  iret1, iret2;
    	
    	char *music_argv_f[] = {"music.zip", "./music"};
    	iret1 = pthread_create( &thread1, NULL, ExtractFiles, (void*) music_argv_f); 
    	CheckThreadError(iret1);
    	
	char *quote_argv_f[] = {"quote.zip", "./quote"};
    	iret2 = pthread_create( &thread2, NULL, ExtractFiles, (void*) quote_argv_f);
    	CheckThreadError(iret2);
    	
    	pthread_join(thread1, NULL);
    	pthread_join(thread2, NULL); 
}

void ProcessAddTextFile() {
	pthread_t thread1, thread2;
    	int  iret1, iret2;
    	
    	CreateFolder("hasil");
    	
    	char *hasil_argv_f[] = {"hasil.zip", "./hasil"};
    	iret1 = pthread_create( &thread1, NULL, ExtractFiles, (void*) hasil_argv_f); 
    	CheckThreadError(iret1);
    	
	char *no_argv_f[] = {"hasil/no.txt", "No"};
    	iret2 = pthread_create( &thread2, NULL, CreateTextFile, (void*) no_argv_f);
    	CheckThreadError(iret2);
    	
    	pthread_join(thread1, NULL);
    	pthread_join(thread2, NULL); 
}

void DecodeBase64(char *name, char *output) {
	int fd[2];
	char decoded_text[50];
	int status;
	
	FILE *file = fopen(output, "a");

	if (pipe(fd)==-1) 
	{ 
		fprintf(stderr, "Pipe Failed" ); 
		exit(EXIT_FAILURE); 
	} 
	
	pid_t child_id = CreateChildProcess();
	
	if (child_id == 0) {
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
    		close(fd[1]);
		execl("/usr/bin/base64", "base64", "-d", name, NULL);
	}

	close(fd[1]);
    	FILE *cmd_output = fdopen(fd[0], "r");
    	if(fgets(decoded_text, sizeof decoded_text, cmd_output)) {
    		fprintf(file, "%s\n", decoded_text);
    	}
    	else {
    		fprintf(file, "HEHEHEHEHE\n");
    	}

	while ((wait(&status)) > 0);
	
	fclose(file);
}

void *ScanDirectory(void *directory) {
	char *dir_name = (char*) directory;
	
	char file_output[50];
	
	struct dirent *dp;
	DIR *dir = opendir(dir_name);
	
	if (!dir)
		exit(EXIT_FAILURE);

    	while ((dp = readdir(dir)) != NULL) {
       	if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) 	{
       		char file_name[50];
       		strcpy(file_name, dir_name);
       		strcat(file_name, "/");
       		strcat(file_name, dp->d_name);
       		
       		strcpy(file_output, dir_name);
       		strcat(file_output, ".txt");

        		DecodeBase64(file_name, file_output);	
        	}
    	}
    	CreateFolder("hasil");
        MoveFile(file_output, "hasil");
    	
   	closedir(dir);
}

void ProcessDecode() {
	pthread_t thread1, thread2;
    	int  iret1, iret2;
    	
    	iret1 = pthread_create(&thread1, NULL, ScanDirectory, (void*) "music"); 
    	CheckThreadError(iret1);
    	
    	iret2 = pthread_create(&thread2, NULL, ScanDirectory, (void*) "quote"); 
    	CheckThreadError(iret2);
    	
    	pthread_join(thread1, NULL);
    	pthread_join(thread2, NULL);
}

void ProcessZipFiles() {
	char *usr;
	usr=(char *)malloc(10*sizeof(char));
	usr=getlogin();

	char pass[30] = "mihinomenest";
	strcat(pass, usr);
	
	ZipFiles(pass, "hasil");
	
	RemoveFile("hasil");
}

