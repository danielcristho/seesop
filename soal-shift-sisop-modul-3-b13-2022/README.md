## Nomor 1

### Deskripsi soal:
Novak adalah seorang mahasiswa biasa yang terlalu sering berselancar di internet. Pada suatu saat, Ia menemukan sebuah informasi bahwa ada suatu situs yang tidak memiliki pengguna. Ia mendownload berbagai informasi yang ada dari situs tersebut dan menemukan sebuah file dengan tulisan yang tidak jelas. Setelah diperhatikan lagi, kode tersebut berformat base64. Ia lalu meminta kepada anda untuk membuat program untuk memecahkan kode-kode di dalam file yang Ia simpan di drive dengan cara decoding dengan base 64. Agar lebih cepat, Ia sarankan untuk menggunakan thread.

### Penjelasan Fungsi Utama
#### CreateChildProcess()
```yml
pid_t CreateChildProcess() {
 	pid_t child_id = fork();

  	if (child_id < 0) {
    		exit(EXIT_FAILURE); 
  	}
  	
    return child_id;
}
```
- Membuat proses baru dengan fungsi fork() dan masukkan returnnya ke dalam child_id.
- Cek jika child_id kurang dari 0 artinya pembuatan proses baru gagal.
- Jika berhasil, return child_id.

#### Execute(char *argv[], char command[])
```yml
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
```
- Membuat proses child baru dengan CreateChildProcess().
- Child tersebut kemudian execute perintah yang dimasukkan ke dalam variabel command dengan parameter argv.
- Parent Process menunggu hingga child process selesai melakukan tugasnya.

#### CheckThreadError(int iret)

```yml
void CheckThreadError(int iret) {
    if(iret) {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret);
        exit(EXIT_FAILURE);
    }
}
```

- Fungsi ini memeriksa apakah thread yang telah dibuat error atau tidak

#### ExtractFiles(void *arg)

```yml
void *ExtractFiles(void *arg) {
    char **argv_f = (char**) arg;
    char *argv[] = {"unzip", argv_f[0], "-d", argv_f[1], NULL};
    Execute(argv, "/usr/bin/unzip");
}
```

- Mengubah variabel arg yang bertipe pointer void menjadi double pointer char
- Parameter argv_f[0] adalah nama filenya yang ingin diekstrak
- Parameter argv_f[1] adalah output filenya.
- Jalankan fungsi Execute() dengan parameter argv dan "/usr/bin/unzip".

#### ChangeWorkingDirectory(const char *dir)

```yml
void ChangeWorkingDirectory(const char *dir) {
    if ((chdir(dir)) < 0) {
        exit(EXIT_FAILURE);
    }
}
```

- Merubah working directory menjadi parameter dir.
- Jika fungsi gagal, maka exit.

#### ZipFiles(char *pass, char *source)
```yml

void ZipFiles(char *pass, char *source) {
    ChangeWorkingDirectory(source);
    char destination[30] = "../";
    strcat(destination, source);
    char *argv[] = {"zip", "-r", "-P", pass, destination, ".", NULL};
    Execute(argv, "/usr/bin/zip");  
    ChangeWorkingDirectory("../");
}
```

- Ubah working directory ke dalam folder yang ingin dizip
- Dapatkan destinationnya dengan menggabungkan "../" dan source
- Jalankan fungsi Execute() dengan parameter argv dan "/usr/bin/zip".
- Ubah working directory kembali ke parent directory.

#### CreateFolder(char folder_name[])

```yml
    void CreateFolder(char folder_name[]) {
    char *argv[] = {"mkdir", "-p", folder_name, NULL};
    Execute(argv, "/usr/bin/mkdir");
    }
```

- Parameter "-p" agar fungsi agar mengabaikan jika telah ada folder dengan nama yang sama.
- Parameter folder_name adalah nama folder yang ingin dibuat.
- Jalankan fungsi Execute() dengan parameter argv dan "/usr/bin/mkdir".

#### RemoveFile(char file[])
```yml

    void RemoveFile(char file[]) {
        char *argv[] = {"remove", "-r", file, NULL};
        Execute(argv, "/usr/bin/rm");
    }
```

- Parameter "-r" memperbolehkan menghapus directory dan file adalah nama file yang ingin dihapus.
- Jalankan fungsi Execute() dengan parameter argv dan "/usr/bin/rm".

#### MoveFile(char source[], char destination[])
```yml

    void MoveFile(char source[], char destination[]) {
    char *argv[] = {"cp", source, destination, NULL};
    Execute(argv, "/bin/cp"); 

    RemoveFile(source);
    }
```

- Parameter source adalah file yang ingin dipindahkan dan destination adalah tujuannya.
- Jalankan fungsi Execute() dengan parameter argv dan "/bin/cp".
- Hapus source file

#### DownloadFile(char *url, char *output)

```yml

    void DownloadFile(char *url, char *output) {
    char *argv[] = {"wget", url, "-O", output};
    Execute(argv, "/usr/bin/wget");  
    }
```

- Parameter url adalah url file yang ingin didownload
- Jalankan fungsi Execute() dengan parameter argv dan "/usr/bin/wget".

#### CreateTextFile(void *arg)

```yml
    void *CreateTextFile(void *arg) {
    char **argv = (char**) arg;
    char *name = argv[0];
    char *contents = argv[1];

    FILE *file = fopen(name, "w");

    fprintf(file, "%s", contents);

    fclose(file);

}
```

- Mengubah variabel arg yang bertipe pointer void menjadi double pointer char
- Parameter argv[0] adalah nama
- Parameter argv[1] adalah konten file
- Print konten kedalam file

### Penjelasan Jawaban
#### A. Download music.zip dan quote.zip lalu unzip menggunakan thread

```yml
    int main() {
    DownloadFile(url_music, "music.zip");
    DownloadFile(url_quote, "quote.zip");
    ProcessUnzipFiles();
```

- Download file music.zip dan quote.zip menggunakan fungsi DownloadFile()
- Lalu unzip kedua file tersebut dengan fungsi ProcessUnzipFiles()

```yml
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
```

- Buat dua thread yang masing - masing menjalankan fungsi ExtractFiles() untuk music.zip dan quote.zip
- Tunggu kedua thread tersebut sampai selesai dengan pthread_join()

#### B. Decode semua file text yang ada di masing masing folder dengan base 64

```yml
    ProcessDecode();
```

- Kembali ke main dan jalankan ProcessDecode()

```yml
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
```

- Buat dua thread yang masing - masing menjalankan fungsi ScanDirectory() untuk folder music dan quote
- Tunggu kedua thread tersebut sampai selesai dengan pthread_join()

```yml
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
```

- Buka directory dengan opendir
- Baca satu persatu file di dalam directory dan dapatkan nama filenya dan nama text outputnya
- Jalankan fungsi DecodeBase64() dengan parameter nama file dan nama text output

```yml
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
```

- Buat pipe lalu buat child process
- Jika yang sedang menjalankan perintah adalah child, maka duplicate standart output ke file descriptor bagian write, lalu execute base64 dengan parameter nama filenya
- Jika yang menjalankan parent process, maka buka file descriptor dan dapatkan copy isinya ke dalam variabel decoded_text
- Jika berhasil, print teks yang telah didecode ke file text nya. 

#### C. Pindahkan file text yang telah dibuat ke folder hasil

```yml
CreateFolder("hasil");
MoveFile(file_output, "hasil");
closedir(dir);
}

```

- Buat folder hasil lalu pindahkan file output ke dalam folder hasil

#### D. Folder hasil dizip dengan password 'mihinomenest[Nama user]'

```yml
    ProcessZipFiles();
```

- Kembali ke fungsi main dan jalankan fungsi ProcessZipFiles()

```yml
void ProcessZipFiles() {
char *usr;
usr=(char *)malloc(10*sizeof(char));
usr=getlogin();

char pass[30] = "mihinomenest";
strcat(pass, usr);

ZipFiles(pass, "hasil");

RemoveFile("hasil");
}
```

- Dapatkan nama user dengan getlogin()
- Gabungkan "mihinomenest" dengan nama user yang telah didapat tadi
- Lalu jalankan fungsi ZipFiles() dengan parameter password pass dan nama folder "hasil"
- Hapus folder "hasil"

#### E. Unzip hasil.zip lalu buat file no.txt dengan isi 'No' kemudian zip 

```yml
    ProcessAddTextFile();
```

- Kembali ke fungsi main dan jalankan fungsi ProcessAddTextFile

```yml
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
```

- Buat folder "hasil"
- Buat dua thread yang masing masing mengekstrak hasil.zip dan membuat no.txt dengan isi 'No'
- Tunggu hinga kedua thread tersebut selesai dijalankan dengan pthread_join

```yml
    ProcessZipFiles();
}
```

- Kembali ke fungsi main dan jalankan fungsi ProcessZipFiles() lagi.

## Nomor 2

### Deskripsi Soal
Bluemary adalah seorang Top Global 1 di salah satu platform online judge. Suatu hari Ia ingin membuat online judge nya sendiri, namun dikarenakan Ia sibuk untuk mempertahankan top global nya, maka Ia meminta kamu untuk membantunya dalam membuat online judge sederhana. Online judge sederhana akan dibuat dengan sistem client-server dengan beberapa kriteria sebagai berikut:

- server.c

Pada fungsi main kita akan membuat file "users.txt", dimana file ini menyimpan username dan passowrd yang diinputkan oleh client. Selanjutnya akan membuat socket baru dengan nama socket_desc, jika gagal maka akan menampilkan output "Could not create socket"

```yml
int main(int argc, char *argv[]) {
    FILE* fp = fopen("users.txt", "a");
    fclose(fp);

    int socket_desc, new_socket, c, *new_sock;
    struct sockaddr_in server , client;
    char *message;

    //equenced, reliable, two-way, connection-based, byte-streams -> SOCK_STREAM (what an IP person would call TCP)
    //AF_INET is an address family that is used to designate the type of addresses that your socket can communicate with (in this case, Internet Protocol v4 addresses).
    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }
```

Fungsi untuk dapat melakukan bind dan listen pada server. Jika bind berhasil dilakukan akan muncul output ‘bind done’ apabila gagal maka akan di print ‘bind failed’.

```yml
//bind
    if (bind(socket_desc,(struct sockaddr *) &server, sizeof(server)) < 0 ) {
        puts("bind failed");
        return 1;
    }
    puts("bind done");

    //Listen
    listen(socket_desc, 3);
```

Selanjutnya adalah fungsi untuk menerima incoming connection. Pada kondisi while untuk melakukan multi koneksi yang dilanjutkan dengan membuat accept koneksi dari client.

```yml
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
```

Join pada thread sehingga tidak akan di terminate sebelum thread. Jika gagal akan print ‘accept failed’.

```yml
//now join the thread, so that we dont terminate before the thread
        pthread_join (sniffer_thread, NULL);
        puts("Handler assigned");
    }

    if (new_socket<0) {
        perror("accept failed");
        return 1;
    }
    return 0;
```

Fungsi connection_handler untuk menangani conection pada setiap client

```yml
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
```

Membuat kondisi, untuk menampilakan pilihan menu di client

```yml
while (1) {
        sprintf(menu, "\nMenu\n1.Register\n2.Login\nChoice : \e[s\e[u");
        write(sock, menu, 1024);
        bzero(menu, 1024);
        valread = read(sock, choice, 1024);
        if (valread < 1) return 0;
```

Jika client memilih 1 maka terlebih dahulu akan melakukan proses register.

```yml
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
```

Jika client memilih 2 maka akan melakukan proses login

```yml
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

```

Jika berhasil  register atau login, maka akan ditampilkan pilihan menu yang bisa dipilih oleh client(add,see,submit&download).

```yml
while (aut == "1") {
            bzero(menu, 1024);
            sprintf(menu, "LOGIN MENU\nadd\nsee\ndownload\nsubmit\nCHOICE:   \e[s\e[u");
            write(sock, menu, 1024);
            valread = read(sock, choice, 1024);
            if (valread < 1) return 0;
```

<<<<<<< HEAD
Selanjutnya jika memilih "add" maka akan membuka file "problem.tsv" dan meminta inputan dari client berupa judul problem, Filepath description, Filepath Input, Filepath Output.

```yml
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
```
- client.c

Fungsi untuk mulai menjalankan program

```yml
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
```

Fungsi untuk memproses input login dan register pada client.

```yml
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
```

Jika username dan password yang diinputkan sesuai maka, client bisa menjlakan perinntah 'add'

```yml
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
```

Juga perintah 'see' untuk melihat isi dari file 'problem.tsv'

```yml
else if (!strcmp(choice, "see")) {
                        bzero(buffer, 1024);
                        read(sock, buffer, 1024);
                        printf("%s", buffer);
                        bzero(buffer, 1024);
```

## No 2

### Kendala

- saya belum memahami penggunaan socket antara client-server.

## No 3

### Kendala


- Ilmu saya masih kurang yang menyebabkan pengerjaan semakin melambat
- saya belum mengerti bagaimana cara unzip dan zip tanpa menggunakan fork dan exec
- pengetahuan mengenai socket client-server masih sangat minim

## Anggota Kelompok

| Nama                      | NRP      |
|---------------------------|----------|
|Abidjana Zulfa Hamdika     |5025201197|
|Brian Akbar Wicaksana      |5025201207|
|Gloriyano C. Daniel Pepuho |5025201121|
|Muhammad Ghani Taufiqurr   |5025201110|
