#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

void *conn_handler( void *);
void *regis(void *);

int main(int argc, char *argv[]) {
    FILE* fp = fopen("users.txt", "a");
    fclose(fp);

    int socket_desc, new_socket, c, *new_sock;
    struct sockaddr_in server , client;
    char *message;

    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 800 );

    //bind
    if (bind(socket_desc,(struct sockaddr *) &server, sizeof(server)) < 0 ) {
        puts("bind failed");
        return 1;
    }
    puts("bind done");

    //Listen
    listen(socket_desc, 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections..");
    c = sizeof(struct sockaddr_in);
    while((new_socket = accept(socket_desc, (struct sockaddr * )&client, (socklen_t*)&c) )) {
        puts("Connection accepted");

        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = new_socket;

        if( pthread_create( &sniffer_thread , NULL ,  conn_handler , (void*) new_sock) < 0) {
            perror("could not create thread");
            return 1;
        }

        //now join the thread, so that we dont terminate before the thread
        pthread_join (sniffer_thread, NULL);
        puts("Handler assigned");
    }

    if (new_socket<0) {
        perror("accept failed");
        return 1;
    }
    return 0; 
}

/*
handle connection to client
*/
void *conn_handler(void *socket_desc) {
    //Get the socket desc
    int sock = *(int*)socket_desc;
    int valread;

    char menu[1024] = {0};
    char buffer[1024] = {0};
    char username[1024] = {0};
    char password[1024] = {0};
    char choice[1024] = {0};
    while (1) {
        sprintf(menu, "\nMenu\n1. Register\n2.Login\nChoice : \e[s\n\e[u");
        write(sock, menu, 1024);
        bzero(menu, 1024);

        valread = read(sock, choice, 1024);
        if (valread < 1) return 0;

        //jika client memilih register
        if (!(strcmp(choice, "1"))) {
            FILE* fp = fopen("users.txt", "a");
            //input username
            sprintf(menu, "Username : \e[s\n\e[u");
            write(sock, menu, 1024);
            bzero(menu, 1024);
            valread = read(sock, username, 1024);
            if (valread < 1) return 0;

            //input password
            sprintf(menu, "Password : \e[s\n\e[u");
            write(sock, menu, 1024);
            bzero(menu, 1024);
            valread = read(sock, password, 1024);
            if (valread < 1) return 0;

            fprintf(fp, "%s:%s\n", username, password);
            fclose(fp);
        }
        else if (!(strcmp(choice, "2"))) {
            char* aut = "0";
            FILE* fp = fopen("users.txt", "r");
            while (aut == "0") {
                bzero(menu, 1024);
                sprintf(menu, "Username : \e[s\n\e[u");
                int ler = write(sock, menu, 1024);
                bzero(menu, 1024);
                valread = read(sock, username, 1024);
                if (valread < 1) return 0;

                sprintf(menu, "Password : \e\[s\n\e[u");
                write(sock, menu, 1024);
                bzero(menu, 1024);
                valread = read(sock, password, 1024);

                while (fgets(buffer, 1024, fp) != NULL && aut == "0") {
                    char f_username[1024], f_password[1024];
                    char *token = strtok(buffer, ":");
                    strcpy(f_username, token);
                    token = strtok(NULL, "\n");
                    strcpy(f_password, token);

                    if (strcmp(username, f_username) == 0 && strcmp(password, f_password)==0) {
                        aut = "1";
                        write(sock, aut,1024);
                    }
                }
            }
            while (aut == "1") {
            bzero(menu, 1024);
            sprintf(menu, "LOGIN MENU\nadd\nsee\nsubmit\nCHOICE  :   \e[s\n\e[u");
            write(sock, menu, 1024);
            valread = read(sock, choice, 1024);
            if (valread < 1) return 0;

            if (!strcmp(choice, "add")) {
                FILE* fp_1 = fopen("problem.tsv", "a");
                char author[1024] = {0};
                char title[1024] = {0};
                char filepath_desc[1024] = {0};
                char filepath_int[1024] = {0};
                char filepath_out[1024] = {0};

                sprintf(author, "Author : \e[s\n\e[u");
                write(sock, author, 1024);
                bzero(author, 1024);
                valread = read(sock, author, 1024);
                if (valread < 1) return 0;

                sprintf(title, "Problems    : \e[s\n\e[u");
                write(sock, title, 1024);
                bzero(title, 1024);
                valread = read(sock, title, 1024);
                if (valread < 1) return 0;
                
                //transfer file
                sprintf(filepath_desc, "Filepath description    : \e[s\n\e[u");
                write(sock, filepath_desc,1024);
                bzero(filepath_desc, 1024);
                valread = read(sock, filepath_desc, 1024);
                if (valread < 1) return 0;
                mkdir("FILES", 0777);
                char path[1024];
                sprintf(path, "../Client/");
                FILE* file_create = fopen(path, "w");

                }
            }
        }
    }
}