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

void *conn_handler(void*);
void *regis(void*);

int main(int argc, char *argv[]) {
    FILE* fp = fopen("users.txt", "a");
    fclose(fp);

    int socket_desc, new_socket, c, *new_sock;
    struct sockaddr_in server , client;
    char *message;

    //equenced, reliable, two-way, connection-based, byte-streams: SOCK_STREAM (what an IP person would call TCP)
    //AF_INET is an address family that is used to designate the type of addresses that your socket can communicate with (in this case, Internet Protocol v4 addresses).
    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }


    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8080 );

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

/*handle connection to client*/
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
        sprintf(menu, "\nMenu\n1.Register\n2.Login\nChoice : \e[s\e[u");
        write(sock, menu, 1024);
        bzero(menu, 1024);

        valread = read(sock, choice, 1024);
        if (valread < 1) return 0;

        //jika client memilih register
        if (!(strcmp(choice, "1"))) {
            FILE* fp = fopen("users.txt", "a");
            //input username
            sprintf(menu, "Username : \e[\e[u");
            write(sock, menu, 1024);
            bzero(menu, 1024);
            valread = read(sock, username, 1024);
            if (valread < 1) return 0;

            //input password
            sprintf(menu, "Password : \e[s\e[u");
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
                sprintf(menu, "Username : \e[s\e[u");
                int ler = write(sock, menu, 1024);
                bzero(menu, 1024);
                valread = read(sock, username, 1024);
                if (valread < 1) return 0;

                sprintf(menu, "Password : \e[s\e[u");
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
            sprintf(menu, "LOGIN MENU\nadd\nsee\ndownload\nsubmit\nCHOICE:   \e[s\e[u");
            write(sock, menu, 1024);
            valread = read(sock, choice, 1024);
            if (valread < 1) return 0;

            //add
            if (!strcmp(choice, "add")) {
                FILE* fp_1 = fopen("problem.tsv", "a");
                char title[1024] = {0};
                char filepath_desc[1024] = {0};
                char filepath_int[1024] = {0};
                char filepath_out[1024] = {0};

                sprintf(title, "Problems : \e[s\e[u");
                write(sock, title, 1024);
                bzero(title, 1024);
                valread = read(sock, title, 1024);
                if (valread < 1) return 0;

                sprintf(filepath_desc, "Filepath description : \e[s\e[u");
                write(sock, filepath_desc,1024);
                bzero(filepath_desc, 1024);
                valread = read(sock, filepath_desc, 1024);
                if (valread < 1) return 0;

                sprintf(filepath_int, "Filepath Input : \e[s\e[u");
                write(sock, filepath_int,1024);
                bzero(filepath_int, 1024);
                valread = read(sock, filepath_int, 1024);
                if(valread < 1) return 0;

                sprintf(filepath_out, "Filepath Output : \e[s\e[u");
                write(sock, filepath_out,1024);
                bzero(filepath_out, 1024);
                valread = read(sock, filepath_out, 1024);
                if(valread < 1) return 0;

                // create folder&transfer file
                mkdir("FILES", 0777);
                char pathServer[1024];
                sprintf(pathServer, "/home/danielpepuho/Desktop/Github/sisop/soal-shift-sisop-modul-3-b13-2022/soal2/Client/FILES/");
                strcat(pathServer, filepath_desc);
                FILE* file_create = fopen(pathServer, "w");

                bzero(buffer, 1024);
                valread = read(sock, buffer, 1024);
                if (valread < 1) return 0;
                fprintf(file_create, "%s", buffer);

                fclose(file_create);  

                bzero(buffer, 1024);
                sprintf(buffer, "\nFile Terikirim\n");
                write(sock, buffer, 1024);

                fprintf(fp_1, "%s\t%s\t%s\t%s\n", title, filepath_desc,filepath_int, filepath_out, pathServer);
                fclose(fp_1);
            }
                //see database
                else if (!strcmp(choice, "see")) {
                    FILE* fcek = fopen("problem.tsv", "r");
                    char line[1024] = {0}, namaProblem[1024] = {0}, author[1024] = {0},
                        p_path[1024] = {0}, pathTemp[1024] = {0};
                    int bukanawal = 0;
                    strcpy(buffer, "");

                    while (fgets(line, 1024, fcek)) {
                        strcat(buffer, "\n\n");

                        char* token;
                        char samlekom1[1024];
                        strcpy(samlekom1, line);
                        char* kumsalam = samlekom1;
                        for (int i = 0; token = strtok_r(kumsalam, "\t", kumsalam); i++) {
                            if (i == 0)
                                strcpy(namaProblem, token);
                            else if (i == 1)
                                strcpy(author, token);
                        }
                        strcpy(pathTemp, p_path);

                        char samlekom2[1024];
                        strcpy(samlekom2, pathTemp);
                        kumsalam = samlekom2;
                        for (int i =0; token = strtok_r(kumsalam, "/", &kumsalam); i++) {
                            strcpy(namaProblem, token);
                        }

                        //print list
                        strcat(buffer, "Nama Problem :");
                        strcat(buffer, namaProblem);
                        strcat(buffer, "\nAuthor :");
                        strcat(buffer, author);

                        bukanawal++;
                    }
                    write(sock, buffer, 1024);
                    bzero(buffer, 1024);
                }
                else if (!strncmp(choice, "download", 8)) {
                    bzero(buffer, 1024);
                    char temp[1024], fileProblem[1024];
                    strcpy(temp, choice);
                    char* save = temp;
                    char* token;
                    for (int i = 0; token = strtok_r(save, "", &save); i++) {
                        bzero(fileProblem, 1024);
                        strcpy(fileProblem, token);
                    }       
                    int found = 0;
                    printf("Judul-problem: %s\n", fileProblem);

                    if (!strcmp(fileProblem, "")) {
                        strcpy(buffer, "masukan nama-problem: ");
                        write(sock, buffer, 1024);
                        bzero(buffer, 1024);
                    }
                    else{
                        char pathServer[1024] = "/Desktop/Github/sisop/soal-shift-sisop-modul-3-b13-2022/soal2/Server/FILES/";
                        strcat(pathServer, fileProblem);
                        printf("pathserver: %s\n", pathServer);
                        FILE* file = fopen("tes.txt", "r");
                        char line[1024];

                        while(fgets(line, 1024, file)) {
                            char temp[1024] = {0}, data[1024] = {0};
                            strcpy(temp, line);
                            char* t;
                            char* simpan = temp;
                            for (int i = 0; t = strtok_r(simpan, "\t", &simpan); i++) {

                                strncpy(data, t, strlen(t) - 1);
                            }
                            printf("data: %s\n", data);
                            if (!strcmp(pathServer, data))
							{
								found = 1;
								break;
							}
                        }


                        if(found) {
                            FILE* ffile = fopen(pathServer, "rb");
                            char dats[1024] = {0};

                            while (fgets(dats, 1024, ffile) != NULL) {
                                write(sock, dats, strlen(dats));
                                bzero(dats, 1024);
                            }
                            fclose(ffile);
                        }
                        else {
                            strcpy(buffer, "file tidak ditemukan");
                            write(sock, buffer, 1024);
                            bzero(buffer, 1024);
                        }
                    }
                }
            }

            fclose(fp);
        }
    }
    free(socket_desc);
    return 0;
}
