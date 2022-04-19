#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    } 
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    char choice[1024];
    //register
    while (1) {
        char username[1024];
        char password[1024];
        valread = read(sock, buffer, 1024);
        printf("%s", buffer);
        bzero(buffer, 1024);
        bzero(choice, 1024);
        scanf(" %[^\n]s", choice);

        write(sock, choice, strlen(choice));
        if (!(strcmp(choice, "1"))) {
            valread = read(sock, buffer, 1024);
            printf("%s", buffer);
            scanf(" %[^\n]s", username);
            write(sock, username, 1024);

            valread = read(sock, buffer, 1024);
            printf("%s", buffer);
            scanf(" %[^\n]s", password);
            write(sock, password, 1024);
        }
        else if (!(strcmp(choice, "2"))) {
            while (1) {
                char aut[1024] = {0};
                while (strcmp(aut, "") == 0) {
                    bzero(buffer, 1024);
                    valread = read(sock, buffer, 1024);
                    printf("%s", buffer);
                    scanf(" %[^\n]s", username);
                    write(sock, username, 1024);
                    bzero(buffer, 1024);
                    valread = read(sock, buffer, 1024);
                    printf("%s", buffer);
                    scanf(" %[^\n]s", password);
                    write(sock, password, 1024);
                    valread = read(sock, aut, 1024);
                }
                while (!strcmp(aut, "1")) {
                    printf("\nLOGIN BERHASIL\n\n");
                    bzero(buffer, 1024);
                    valread = read(sock, buffer, 1024);
                    printf("%s", buffer);
                    bzero(buffer, 1024);
                    scanf(" %[^\n]s", choice);
                    write(sock, choice, 1024);
                    if (!strcmp(choice, "add")) {
                        char kirim[1024] = {0};
                        valread = read(sock, buffer, 1024);
                        printf("%s", buffer);
                        bzero(buffer, 1024);
                        scanf("%s", kirim);
                        write(sock, kirim, 1024);
                        bzero(buffer, 1024);
                        valread = read(sock, buffer, 1024);
                        printf("%s", buffer);
                        scanf("%s", kirim);
                        write(sock, kirim, 1024);
                        printf("%s", kirim);
                        FILE* file = fopen(kirim, "rb");
                        char data[1024] = {0};
                        while(fgets(data, 1024, file) != NULL) {
                            write(sock, data, strlen(data));
                            bzero(data, 1024);
                        }
                        fclose(file);
                    }
                    else if (!strcmp(choice, "see")) {
                        bzero(buffer, 1024);
                        read(sock, buffer, 1024);
                        printf("%s", buffer);
                        bzero(buffer, 1024);
                    }
                    else if (!strncmp(choice, "download", 8)) {
                        char fileProblem[1024];
                        strcpy(fileProblem, choice);
                        char* token;
                        char* simpan = fileProblem;
                        for (int i = 0; token = strtok_r(simpan, " ", &simpan); i++) {
                            bzero(buffer, 1024);
                            strcpy(buffer, token);
                        }
                        char pathClient[1024] = "/home/danielpepuho/modul3/soal2/Client/";
                        strcat(pathClient, buffer);
                        bzero(buffer, 1024);
                        if (strcmp(buffer, "file tidak ditemukan!!") && strcmp(buffer, "masukan nama file: ")){
                            FILE* file = fopen(pathClient, "w");
                            valread = read(sock, buffer, 1024);
                            fprintf(file, "%s", buffer);
                            fclose(file);
                            printf("file telah diunduh\n\n");
                        }
                        else {
                            printf("%s\n", buffer);
                        }
                    }
                }
            }
        }
    }
    return 0;
}