#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

static  const  char *dirpath = "/home/danielpepuho/Documents";
char *key_three = "nam_do-saq_";

// no 1

// encode file yg terdapat huruf besar menggunakan atbash
void atbashEnc(char str[1000], char newStr[1000]) {
    if (!strcmp(str, ".") || !strcmp(str, "..")) {
        strcpy(newStr, str);
        return;
    };

    int i, flag = 0;
    i = 0;
    while (str[i] != '\0') {
        // exclude extension
        if (str[i] == '.') {
            flag = 1;
        }
        if (flag == 1) {
            newStr[i] = str[i];
            i++;
            continue;
        }

        if (!((str[i] >= 0 && str[i] < 65) || (str[i] > 90 && str[i] < 97) ||
            (str[i] > 122 && str[i] <= 127))) {
                if (str[i] >= 'A' && str[i] <= 'Z') {
                    newStr[i] = 'Z' + 'A' - str[i];
                }
            }

        if (!((str[i] >= 0 && str[i] < 65) || (str[i] > 90 && str[i] < 97) ||
            (str[i] > 122 && str[i] <= 127))) {
            newStr[i] = str[i];
            }

            i++;
    }
    newStr[i] = '\0';
}

// encode menggunakan Rot13 jika file menggunakan huruf kecil
void rot13Enc(char str[1000], char newStr[1000]) {
    if (!strcmp(str, ".") || !strcmp(str, "..")) {
        strcpy(newStr, str);
        return;
    };

    int i, flag = 0;
    i = 0;
    while (str[i] != '\0') {
        if (str[i] == '.') {
            flag = 1;
        }
        if (flag == 1) {
            newStr[i] = str[i];
            i++;
            continue;
        }

        if (!((str[i] >= 0 && str[i] < 65) || (str[i] > 90 && str[i] < 97))) {
            if (str[i] >= 'a' && str[i] <= 'z') {
                if (str[i] + 13 > 'z') {
                    newStr[i] = str[i] - 13;
                } else {
                    newStr[i] = str[i] + 13;
                }
            }
        }
        if ((str[i] >= 0 && str[i] < 65) || (str[i] > 90 && str[i] < 97)) {
            newStr[i] = str[i];
        }
        i++;
    }
    newStr[i] = '\0';
}


void logEnc(const char *log, const char *source, const char *destination) {
    FILE *fp;
    fp = fopen("/home/danielpepuho/Downloads/wibu.log", "a");
    fputs("INFO::", fp);
    char timestamp[1000];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(timestamp, "%02d%02d%04d-%02d:%02d:%02d:", tm.tm_mday, tm.tm_mon + 1,
            tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fputs(timestamp,fp);
    fputs(log, fp);
    fputs("::", fp);
    fputs(source, fp);
    fputs("::", fp);
    fputs(destination, fp);
    fputs("\n", fp);
    fclose(fp);
}

void logEnc2(const char *log, const char *path) {
    FILE *fp;
    //NB: SESUAIKAN
    fp = fopen("/home/danielpepuho/Downloads/wibu.log", "a");
    fputs("INFO::", fp);
    char timestamp[1000];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(timestamp, "%02d%02d%04d-%02d:%02d:%02d:", tm.tm_mday, tm.tm_mon + 1,
            tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fputs(timestamp,fp);
    fputs(log, fp);
    fputs("::", fp);
    fputs(path, fp);
    fputs("::", fp);
    fclose(fp);
}


// // encode menggunakan rot13
// void rot13Enc(char str[1000], char newStr[1000]) {
//     //skip if directory
//     if (!strcmp(str, ".") || !strcmp(str, "..")) {
//         strcpy(newStr, str);
//         return;
//     };

//     int i, flag = 0;
//     i = 0;
//     while (str[i] != '\0') {
//         if (str[i] == '.') {
//             flag = 1;
//         }
//         if (flag == 1) {
//             newStr[i] = str[i];
//             i++;
//             continue;
//         }

//         if (!((str[i] >= 0 && str[i] < 65) || (str[i] > 90 && str[i] < 97))) {
//             if (str[i] >= 'A' && str[i] <= 'Z') {
//                 if (str[i] + 13 > 'Z') {
//                     newStr[i] = str[i] - 13;
//                 } else {
//                     newStr[i] = str[i] + 13;
//                 }
//             }
//             if (str[i] >= 'a' && str[i] <= 'z') {
//                 if (str[i] + 13 > 'z') {
//                     newStr[i] = str[i] - 13;
//                 } else {
//                     newStr[i] = str[i] + 13;
//                 }
//             }
//         }

//         if ((str[i] >= 0 && str[i] < 65) || (str[i] > 90 && str[i] < 97 )) {
//             newStr[i] = str[i];
//         }

//         i++;
//     }
//     newStr[i] = '\0';
// }

// // decode dengan rot13
// void rot13Dec(char str[1000], char newStr[1000]) {
//     if (!strcmp(str, ".") || !strcmp(str, "..")) {
//         strcpy(newStr, str);
//         return;
//     };

//     int i, flag = 0;
//     i = 0;
//     while (str[i] != '\0') {
//         if (str[i] == '.') {
//             flag = 1;
//         }
//         if (flag == 1) {
//             newStr[i] = str[i];
//             i++;
//             continue;
//         }

//         if (!((str[i] >= 0 && str[i] < 65) || (str[i] > 90 && str[i] < 97))) {
//             if (str[i] >= 'A' && str[i] <= 'Z') {
//                 if (str[i] - 13 < 'A') {
//                     newStr[i] = str[i] + 13;
//                 }else {
//                     newStr[i] = str[i] - 13;
//                 }
//             }
//             if (str[i] >= 'a' && str[i] <= 'z') {
//                 if (str[i] - 13 < 'a') {
//                     newStr[i] = str[i] + 13;
//                 } else {
//                     newStr[i] = str[i] - 13;
//                 }
//             }
//         }

//         if ((str[i] <= 0 && str[i] < 65) || (str[i] > 90 && str[i] < 97)) {
//             newStr[i] = str[i];
//         }

//         i++;
//     }
//     newStr[i] = '\0';
// }

int binaryToDecimal(unsigned long long binary) {
	int p = 0, decimal = 0, last_digit;
	while(binary) {
		last_digit = binary % 10;
		decimal += last_digit * pow(2, p++);
		binary /= 10;
	}

	return decimal;
}

char *decimalToBinaryReverse(int decimal) {
	char *binary = (char*)malloc(100);
	int i = 0;
	while(decimal) {
		binary[i++] = (decimal % 2) + '0';
		decimal /= 2;
	}
	binary[i] = '\0';

	return binary;
}

char *uppercaseName(char *name_ori) {
	char *name = strstr(name_ori, key_three);
	if(name == NULL) return name_ori;

	int i = 11;
	unsigned long long int binary = 0;
	while(name[i] != '.' && name[i] != '\0') {
		binary *= 10;
		if(islower(name[i])) {
			name[i] = toupper(name[i]);
			binary += 1;
		}
		i++;
	}
	char *encrypted_name = (char *) malloc(1000);
	sprintf(encrypted_name,"%s.%d", name, binaryToDecimal(binary));
	return encrypted_name;
}

char *lowercaseName(char *name_ori) {
	char *name = strstr(name_ori, key_three);
	if(name == NULL) return name_ori;

	char *dec_loc, *dec_loc_next = name;
	while((dec_loc_next = strstr(dec_loc_next, ".")) != NULL) {
		dec_loc = dec_loc_next;
		dec_loc_next = &dec_loc_next[1];
	}
	dec_loc = &dec_loc[1];
	int decimal = atoi(dec_loc);
	char *binary = decimalToBinaryReverse(decimal);

	char *first_dot = strstr(name, ".");

	int i = strlen(name) - strlen(first_dot) - 1;

	for(int j = 0; j < strlen(binary); j++) {
		if(binary[j] == '1') {
			name[i] = tolower(name[i]);
		}
		i--;
	}

	char *dec_name = (char *) malloc(1000);
	dec_name[0] = '\0';
	int diff = strlen(name) - strlen(dec_loc) - 1;
	strncat(dec_name, name, diff);
	dec_name[diff] = '\0';

	return dec_name;
}

char *decryptPath(const char *path_ori) {
	char *path_begin = (char*)path_ori;
	char *path_end = path_begin;
	char *dec_path = (char*)malloc(1000);
	dec_path[0] = '\0';
	while(strstr(path_end, key_three) != NULL) {
		path_end = strstr(path_end, key_three);
		int diff = path_end - path_begin;
		strncat(dec_path, path_begin, diff);
		path_begin = path_end;
		path_end = strstr(path_end, "/");

		if(path_end == NULL) path_end = path_begin + strlen(path_begin);

		char *name_to_dec = (char*)malloc(strlen(path_begin) - strlen(path_end));
		diff = path_end - path_begin;
		strncpy(name_to_dec, path_begin, diff);
		char *dec_name = lowercaseName(name_to_dec);

		strcat(dec_path, dec_name);
		path_begin = path_end;
		free(name_to_dec);
	}
	strcat(dec_path, path_end);
	return dec_path;
}

static  int  xmp_getattr(const char *path, struct stat *stbuf)
{
    int res;
    char fpath[1000];

    char *dec_path = decryptPath(path);
    sprintf(fpath, "%s%s",dirpath,dec_path);

    res = lstat(fpath, stbuf);

    if (res == -1) return -errno;

    return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
    char fpath[1000];

    char *dec_path = decryptPath(path);
    sprintf(fpath, "%s%s",dirpath,dec_path);

    int res = 0;

    DIR *dp;
    struct dirent *de;
    (void) offset;
    (void) fi;

    dp = opendir(fpath);

    if (dp == NULL) return -errno;

    while ((de = readdir(dp)) != NULL) {
        struct stat st;

        memset(&st, 0, sizeof(st));

        st.st_ino = de->d_ino;
        st.st_mode = de->d_type << 12;
    	char *encrypted_name = uppercaseName(de->d_name);
        res = (filler(buf, encrypted_name, &st, 0));

        if(res!=0) break;
    }

    closedir(dp);

    return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    char fpath[1000];

    char *dec_path = decryptPath(path);
    sprintf(fpath, "%s%s",dirpath,dec_path);

    int res = 0;
    int fd = 0 ;

    (void) fi;

    fd = open(fpath, O_RDONLY);

    if (fd == -1) return -errno;

    res = pread(fd, buf, size, offset);

    if (res == -1) res = -errno;

    close(fd);

    return res;
}

static int xmp_mkdir(const char *path, mode_t mode) {
	int res;
	char fpath[1000];

	char *dec_path = decryptPath(path);
	sprintf(fpath, "%s%s",dirpath,dec_path);

	res = mkdir(fpath, mode);

	if (res == -1) return -errno;

    // add to log
    logEnc2("MKDIR", path);

	return 0;
}

static int xmp_rename(const char *from, const char *to) {
    char fpathFrom[1000];
    char fpathTo[1000];

    if (strcmp(from, "/") == 0) {
        from = dirpath;
        sprintf(fpathFrom, "%s", from);
    } else {
        sprintf(fpathFrom, "%s%s", dirpath, from);
    }

    if (strcmp(to, "/") == 0) {
        to = dirpath;
        sprintf(fpathTo, "%s", to);
    } else {
        sprintf(fpathTo, "%s%s", dirpath, to);
    }

    // variabel untuk rename
    int res;
    res = rename(fpathFrom, fpathTo);

    if (res == -1) return -errno;

    logEnc("RENAME", fpathFrom, fpathTo);
    return 0;
}

static struct fuse_operations xmp_oper = {
    .getattr = xmp_getattr,
    .readdir = xmp_readdir,
    .read = xmp_read,
    .rename = xmp_rename,
    .mkdir = xmp_mkdir,
};

int  main(int  argc, char *argv[])
{
    umask(0);

    return fuse_main(argc, argv, &xmp_oper, NULL);
}







































// #define FUSE_USE_VERSION 28
// #include <fuse.h>
// #include <ctype.h>
// #include <math.h>
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdbool.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <dirent.h>
// #include <errno.h>
// #include <sys/time.h>

// static  const  char *dirpath = "/home/brianakbar/Documents";
// char *key_three = "nam_do-saq_";

// // no 1

// // encode file yg terdapat huruf besar menggunakan atbash
// void atbashEnc(char str[1000], char newStr[1000]) {
//     if (!strcmp(str, ".") || !strcmp(str, "..")) {
//         strcpy(newStr, str);
//         return;
//     };

//     int i, flag = 0;
//     i = 0;
//     while (str[i] != '\0') {
//         // exclude extension
//         if (str[i] == '.') {
//             flag = 1;
//         }
//         if (flag == 1) {
//             newStr[i] = str[i];
//             i++;
//             continue;
//         }

//         if (!((str[i] >= 0 && str[i] < 65) || (str[i] > 90 && str[i] < 97) ||
//             (str[i] > 122 && str[i] <= 127))) {
//                 if (str[i] >= 'A' && str[i] <= 'Z') {
//                     newStr[i] = 'Z' + 'A' - str[i];
//                 }
//             }

//         if (!((str[i] >= 0 && str[i] < 65) || (str[i] > 90 && str[i] < 97) ||
//             (str[i] > 122 && str[i] <= 127))) {
//             newStr[i] = str[i];
//             }

//             i++;
//     }
//     newStr[i] = '\0';
// }

// // encode menggunakan Rot13 jika file menggunakan huruf kecil
// void rot13Enc(char str[1000], char newStr[1000]) {
//     if (!strcmp(str, ".") || !strcmp(str, "..")) {
//         strcpy(newStr, str);
//         return;
//     };

//     int i, flag = 0;
//     i = 0;
//     while (str[i] != '\0') {
//         if (str[i] == '.') {
//             flag = 1;
//         }
//         if (flag == 1) {
//             newStr[i] = str[i];
//             i++;
//             continue;
//         }

//         if (!((str[i] >= 0 && str[i] < 65) || (str[i] > 90 && str[i] < 97))) {
//             if (str[i] >= 'a' && str[i] <= 'z') {
//                 if (str[i] + 13 > 'z') {
//                     newStr[i] = str[i] - 13;
//                 } else {
//                     newStr[i] = str[i] + 13;
//                 }
//             }
//         }
//         if ((str[i] >= 0 && str[i] < 65) || (str[i] > 90 && str[i] < 97)) {
//             newStr[i] = str[i];
//         }
//         i++;
//     }
//     newStr[i] = '\0';
// }

// <<<<<<< HEAD
// // void logEnc(const char *log, const char *source, const char *destination) {
// //     FILE *fp;
// //     fp = fopen("/home/danielpepuho/Downloads/wibu.log", "a");
// //     fputs("INFO::", fp);
// //     char timestamp[1000];
// //     time_t t = time(NULL);
// //     struct tm tm = *localtime(&t);
// //     sprintf(timestamp, "%02d%02d%04d-%02d:%02d:%02d:", tm.tm_mday, tm.tm_mon + 1,
// //             tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
// //     fputs(timestamp,fp);
// //     fputs(log, fp);
// //     fputs("::", fp);
// //     fputs(source, fp);
// //     fputs("::", fp);
// //     fputs(destination, fp);
// //     fputs("\n", fp);
// //     fclose(fp);
// // }

// // void logEnc2(const char *log, const char *path) {
// //     FILE *fp;
// //     fp = fopen("/home/danielpepuho/Downloads/wibu.log", "a");
// //     fputs("INFO::", fp);
// //     char timestamp[1000];
// //     time_t t = time(NULL);
// //     struct tm tm = *localtime(&t);
// //     sprintf(timestamp, "%02d%02d%04d-%02d:%02d:%02d:", tm.tm_mday, tm.tm_mon + 1,
// //             tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
// //     fputs(timestamp,fp);
// //     fputs(log, fp);
// //     fputs("::", fp);
// //     fputs(path, fp);
// //     fputs("::", fp);
// //     fclose(fp);
// // }

// // static int xmp_rename(const char *from, const char *to) {
// //     char fpathFrom[1000];
// //     char fpathTo[1000];

// //     if (strcmp(from, "/") == 0) {
// //         from = dirpath;
// //         sprintf(fpathFrom, "%s", from);
// //     } else {
// //         sprintf(fpathFrom, "%s%s", dirpath, from);
// //     }

// //     if (strcmp(to, "/") == 0) {
// //         to = dirpath;
// //         sprintf(fpathTo, "%s", to);
// //     } else {
// //         sprintf(fpathTo, "%s%s", dirpath, to);
// //     }

// //     // variabel untuk rename
// //     int res;
// //     res = rename(fpathFrom, fpathTo);

// //     if (res == -1) return -errno;

// //     logEnc("RENAME", fpathFrom, fpathTo);
// //     return 0;
// // }

// // static int xmp_mkdir(const char *path, mode_t mode) {
// //     char fpath[1000];
// //     if (strcmp(path, "/") == 0) {
// //         path = dirpath;
// //         sprintf(fpath, "%s", path);
// //     } else {
// //         sprintf(fpath, "%s%s", dirpath, path);
// //     }

// //     //variabel untuk mkdir 
// //     int res;
// //     res = mkdir(fpath, mode);

// //     if (res == -1) return -errno;

// //     logEnc2("MKDIR", path);

// //     return 0;
// // }

// // static struct fuse_operations xmp_oper = {
// //     .rename = xmp_rename,
// //     .mkdir = xmp_mkdir,
// // };

// // int main(int argc, char *argv[]) {
// //     umask(0);

// //     return fuse_main(argc, argv, &xmp_oper, NULL);
// // }




























// =======
// >>>>>>> bb40e1239a436928137dc7d50ecda92c7a022443
// // // encode menggunakan rot13
// // void rot13Enc(char str[1000], char newStr[1000]) {
// //     //skip if directory
// //     if (!strcmp(str, ".") || !strcmp(str, "..")) {
// //         strcpy(newStr, str);
// //         return;
// //     };

// //     int i, flag = 0;
// //     i = 0;
// //     while (str[i] != '\0') {
// //         if (str[i] == '.') {
// //             flag = 1;
// //         }
// //         if (flag == 1) {
// //             newStr[i] = str[i];
// //             i++;
// //             continue;
// //         }

// //         if (!((str[i] >= 0 && str[i] < 65) || (str[i] > 90 && str[i] < 97))) {
// //             if (str[i] >= 'A' && str[i] <= 'Z') {
// //                 if (str[i] + 13 > 'Z') {
// //                     newStr[i] = str[i] - 13;
// //                 } else {
// //                     newStr[i] = str[i] + 13;
// //                 }
// //             }
// //             if (str[i] >= 'a' && str[i] <= 'z') {
// //                 if (str[i] + 13 > 'z') {
// //                     newStr[i] = str[i] - 13;
// //                 } else {
// //                     newStr[i] = str[i] + 13;
// //                 }
// //             }
// //         }

// //         if ((str[i] >= 0 && str[i] < 65) || (str[i] > 90 && str[i] < 97 )) {
// //             newStr[i] = str[i];
// //         }

// //         i++;
// //     }
// //     newStr[i] = '\0';
// // }

// // // decode dengan rot13
// // void rot13Dec(char str[1000], char newStr[1000]) {
// //     if (!strcmp(str, ".") || !strcmp(str, "..")) {
// //         strcpy(newStr, str);
// //         return;
// //     };

// //     int i, flag = 0;
// //     i = 0;
// //     while (str[i] != '\0') {
// //         if (str[i] == '.') {
// //             flag = 1;
// //         }
// //         if (flag == 1) {
// //             newStr[i] = str[i];
// //             i++;
// //             continue;
// //         }

// //         if (!((str[i] >= 0 && str[i] < 65) || (str[i] > 90 && str[i] < 97))) {
// //             if (str[i] >= 'A' && str[i] <= 'Z') {
// //                 if (str[i] - 13 < 'A') {
// //                     newStr[i] = str[i] + 13;
// //                 }else {
// //                     newStr[i] = str[i] - 13;
// //                 }
// //             }
// //             if (str[i] >= 'a' && str[i] <= 'z') {
// //                 if (str[i] - 13 < 'a') {
// //                     newStr[i] = str[i] + 13;
// //                 } else {
// //                     newStr[i] = str[i] - 13;
// //                 }
// //             }
// //         }

// //         if ((str[i] <= 0 && str[i] < 65) || (str[i] > 90 && str[i] < 97)) {
// //             newStr[i] = str[i];
// //         }

// //         i++;
// //     }
// //     newStr[i] = '\0';
// // }

// int binaryToDecimal(unsigned long long binary) {
// 	int p = 0, decimal = 0, last_digit;
// 	while(binary) {
// 		last_digit = binary % 10;
// 		decimal += last_digit * pow(2, p++);
// 		binary /= 10;
// 	}

// 	return decimal;
// }

// char *decimalToBinaryReverse(int decimal) {
// 	char *binary = (char*)malloc(100);
// 	int i = 0;
// 	while(decimal) {
// 		binary[i++] = (decimal % 2) + '0';
// 		decimal /= 2;
// 	}
// 	binary[i] = '\0';

// 	return binary;
// }

// char *uppercaseName(char *name_ori) {
// 	char *name = strstr(name_ori, key_three);
// 	if(name == NULL) return name_ori;

// 	int i = 11;
// 	unsigned long long int binary = 0;
// 	while(name[i] != '.' && name[i] != '\0') {
// 		binary *= 10;
// 		if(islower(name[i])) {
// 			name[i] = toupper(name[i]);
// 			binary += 1;
// 		}
// 		i++;
// 	}
// 	char *encrypted_name = (char *) malloc(1000);
// 	sprintf(encrypted_name,"%s.%d", name, binaryToDecimal(binary));
// 	return encrypted_name;
// }

// char *lowercaseName(char *name_ori) {
// 	char *name = strstr(name_ori, key_three);
// 	if(name == NULL) return name_ori;

// 	char *dec_loc, *dec_loc_next = name;
// 	while((dec_loc_next = strstr(dec_loc_next, ".")) != NULL) {
// 		dec_loc = dec_loc_next;
// 		dec_loc_next = &dec_loc_next[1];
// 	}
// 	dec_loc = &dec_loc[1];
// 	int decimal = atoi(dec_loc);
// 	char *binary = decimalToBinaryReverse(decimal);

// 	char *first_dot = strstr(name, ".");

// 	int i = strlen(name) - strlen(first_dot) - 1;

// 	for(int j = 0; j < strlen(binary); j++) {
// 		if(binary[j] == '1') {
// 			name[i] = tolower(name[i]);
// 		}
// 		i--;
// 	}

// 	char *dec_name = (char *) malloc(1000);
// 	dec_name[0] = '\0';
// 	int diff = strlen(name) - strlen(dec_loc) - 1;
// 	strncat(dec_name, name, diff);
// 	dec_name[diff] = '\0';

// 	return dec_name;
// }

// char *decryptPath(const char *path_ori) {
// 	char *path_begin = (char*)path_ori;
// 	char *path_end = path_begin;
// 	char *dec_path = (char*)malloc(1000);
// 	dec_path[0] = '\0';
// 	while(strstr(path_end, key_three) != NULL) {
// 		path_end = strstr(path_end, key_three);
// 		int diff = path_end - path_begin;
// 		strncat(dec_path, path_begin, diff);
// 		path_begin = path_end;
// 		path_end = strstr(path_end, "/");

// 		if(path_end == NULL) path_end = path_begin + strlen(path_begin);

// 		char *name_to_dec = (char*)malloc(strlen(path_begin) - strlen(path_end));
// 		diff = path_end - path_begin;
// 		strncpy(name_to_dec, path_begin, diff);
// 		char *dec_name = lowercaseName(name_to_dec);

// 		strcat(dec_path, dec_name);
// 		path_begin = path_end;
// 		free(name_to_dec);
// 	}
// 	strcat(dec_path, path_end);
// 	return dec_path;
// }

// static  int  xmp_getattr(const char *path, struct stat *stbuf)
// {
//     int res;
//     char fpath[1000];

//     char *dec_path = decryptPath(path);
//     sprintf(fpath, "%s%s",dirpath,dec_path);

//     res = lstat(fpath, stbuf);

//     if (res == -1) return -errno;

//     return 0;
// }

// static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
// {
//     char fpath[1000];

//     char *dec_path = decryptPath(path);
//     sprintf(fpath, "%s%s",dirpath,dec_path);

//     int res = 0;

//     DIR *dp;
//     struct dirent *de;
//     (void) offset;
//     (void) fi;

//     dp = opendir(fpath);

//     if (dp == NULL) return -errno;

//     while ((de = readdir(dp)) != NULL) {
//         struct stat st;

//         memset(&st, 0, sizeof(st));

//         st.st_ino = de->d_ino;
//         st.st_mode = de->d_type << 12;
//     	char *encrypted_name = uppercaseName(de->d_name);
//         res = (filler(buf, encrypted_name, &st, 0));

//         if(res!=0) break;
//     }

//     closedir(dp);

//     return 0;
// }

// static int xmp_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
// {
//     char fpath[1000];

//     char *dec_path = decryptPath(path);
//     sprintf(fpath, "%s%s",dirpath,dec_path);

//     int res = 0;
//     int fd = 0 ;

//     (void) fi;

//     fd = open(fpath, O_RDONLY);

//     if (fd == -1) return -errno;

//     res = pread(fd, buf, size, offset);

//     if (res == -1) res = -errno;

//     close(fd);

//     return res;
// }

// static int xmp_mkdir(const char *path, mode_t mode) {
// 	int res;
// 	char fpath[1000];

// 	char *dec_path = decryptPath(path);
// 	sprintf(fpath, "%s%s",dirpath,dec_path);

// 	res = mkdir(fpath, mode);

// 	if (res == -1) return -errno;
// 	return 0;
// }

// static struct fuse_operations xmp_oper = {
//     .getattr = xmp_getattr,
//     .readdir = xmp_readdir,
//     .read = xmp_read,
//     .mkdir = xmp_mkdir,
// };

// int  main(int  argc, char *argv[])
// {
//     umask(0);

//     return fuse_main(argc, argv, &xmp_oper, NULL);
// }
