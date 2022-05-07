#define FUSE_USE_VERSION 28
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fuse.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

static const char *dirpath = "/home/danielpepuho/Documents";

void atbash(char str[1000], char newStr[1000]) {
    if (!strcmp(str, ".") || !strcmp(str, "..")) {
        strcpy(newStr, str);
        return;
    };

    int i, flag = 0;
    i = 0;
    while (str[i] != '\0') {
        
    }
}