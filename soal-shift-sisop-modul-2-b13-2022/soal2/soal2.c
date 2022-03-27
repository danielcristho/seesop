#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <dirent.h>
#include <sys/stat.h>

int status;
pid_t child_id;

void BackToHome();
pid_t CreateChildProcess();
void Execute(char *argv[], char command[]);
void CreateFolder(char folder_name[]);
void ExtractFiles();
void ChangeWorkingDirectory(const char *dir);
void CopyFile(char source[], char destination[]);
void RenameFile(char source[], char destination[]);
void RemoveFile(char file[]);
void SortData();
void StoreData(char category[]);
void ParseString(char *d, char s[], int *i);
void InsertData(char year[], char title[]);
void ProcessPhoto(char name[]);
void DeleteFolders();
void CreateCategory();
void ProcessCategoryData();

int main() {
	BackToHome();
	ExtractFiles();		
	ChangeWorkingDirectory("shift2/drakor");
	DeleteFolders();
	CreateCategory();
	ProcessCategoryData();
  	
  	return 0;
}

void BackToHome() {
	char home_dir[30] = "/home/";

	char *usr;
	usr=(char *)malloc(10*sizeof(char));
	usr=getlogin();
	
	strcat(home_dir, usr);
	ChangeWorkingDirectory(home_dir);
}

pid_t CreateChildProcess() {

 	pid_t child_id = fork();

  	if (child_id < 0) {
    		exit(EXIT_FAILURE); 
  	}
  	
  	return child_id;
}

void Execute(char *argv[], char command[]) {
	child_id = CreateChildProcess();
	
	if (child_id == 0) {
		execv(command, argv);
	}
	while ((wait(&status)) > 0);
}

void CreateFolder(char folder_name[]) {
	char *argv[] = {"mkdir", "-p", folder_name, NULL};
	Execute(argv, "/usr/bin/mkdir");
}

void ExtractFiles() {
	CreateFolder("shift2");
	
  	char *argv[] = {"unzip", "drakor.zip", "-d", "shift2/drakor", NULL};
  	Execute(argv, "/usr/bin/unzip");  	
}

void ChangeWorkingDirectory(const char *dir) {
	if ((chdir(dir)) < 0) {
  		exit(EXIT_FAILURE);
	}
}
void CopyFile(char source[], char destination[]) {
  	char *argv[] = {"cp", source, destination, NULL};
  	Execute(argv, "/bin/cp"); 
}

void RenameFile(char source[], char destination[]) {
  	char *argv[] = {"mv", source, destination, NULL};
  	Execute(argv, "/usr/bin/mv");	
}

void RemoveFile(char file[]) {
    	char *argv[] = {"remove", "-r", file, NULL};
    	Execute(argv, "/usr/bin/rm");
}

void SortData() { 	
    	FILE *file = fopen("sort.txt" , "w");
    	fclose(file);
    				
    	char *argv[] = {"sort", "-o", "sort.txt", "temp.txt", NULL};
    	Execute(argv, "/usr/bin/sort");

    	RemoveFile("temp.txt");
}

void StoreData(char category[]) {
	FILE *file = fopen("sort.txt" , "r");
	FILE *output = fopen("data.txt", "w");
	
	char year[10][10];
	char title[10][50];
	int i = 0;
	while(fscanf(file, "%s %s", year[i], title[i]) != EOF) {
		i++;
	}
	
	fprintf(output, "kategori : %s\n", category);
	for(int j = 0; j < i; j++) {
		fprintf(output, "\nnama : %s\nrilis : tahun %s\n", title[j], year[j]);
	}
	
	fclose(output);
	fclose(file);
	
	RemoveFile("sort.txt");
}

void ParseString(char *d, char s[], int *i) {
	int j = 0;
	while(s[*i] != ';' && s[*i] != '_' && s[*i] != '.') {
		d[j] = s[*i];
		j++;
		(*i)++;
	}
	d[j] = '\0';
}

void InsertData(char year[], char title[]) {
	FILE *file = fopen("temp.txt" , "a");
	
	fprintf(file, "%s %s\n", year, title);
	
	fclose(file);
}

void ProcessPhoto(char name[]) {
	int i = 0;
	while(name[i] != '.') {
		char title[35], year[10], category[20];
		
		ParseString(title, name, &i);
		i++;
		
		ParseString(year, name, &i);
		i++;
		
		ParseString(category, name, &i);
		if(name[i] == '_') {
			i++;
		}
		CreateFolder(category);
		CopyFile(name, category);
		ChangeWorkingDirectory(category);
		RenameFile(name, title);
		InsertData(year, title);
		ChangeWorkingDirectory("../");	
	}
	RemoveFile(name);
}

void DeleteFolders() {
	struct dirent *dp;
	DIR *dir = opendir("./");
	
	if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) 	{
        	struct stat fs;
        		
		    int r = stat(dp->d_name,&fs);
    		if( r==-1 ) {
        		fprintf(stderr,"File error\n");
        		exit(1);
    		}
    			
    		//Delete non-PNG
    		if(fs.st_mode != 0100664) {
    			RemoveFile(dp->d_name);
    		}
       	}
   	}
    closedir(dir);
}

void CreateCategory() {
	struct dirent *dp;
	DIR *dir = opendir("./");
	
	if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) 	{	
        	ProcessPhoto(dp->d_name);
        }
    }
    closedir(dir);
}

void ProcessCategoryData() {
	struct dirent *dp;
	DIR *dir = opendir("./");
	
	if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL) {
       	if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) 	{
        	ChangeWorkingDirectory(dp->d_name);
        	SortData();
        	StoreData(dp->d_name);
        	ChangeWorkingDirectory("../");
        }
    }
   	closedir(dir);
}
