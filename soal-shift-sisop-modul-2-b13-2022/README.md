# soal-shift-sisop-modul-2-B13-2022

## Nomor 1
### source code: [click here!](https://github.com/danielcristho/seesop/blob/master/soal-shift-sisop-modul-2-b13-2022/soal1/soal1/soal1.c)
### Deskripsi soal:
Mas Refadi adalah seorang wibu gemink.  Dan jelas game favoritnya adalah bengshin impek. Terlebih pada game tersebut ada sistem gacha item yang membuat orang-orang selalu ketagihan untuk terus melakukan nya. Tidak terkecuali dengan mas Refadi sendiri. Karena rasa penasaran bagaimana sistem gacha bekerja, maka dia ingin membuat sebuah program untuk men-simulasi sistem history gacha item pada game tersebut. Tetapi karena dia lebih suka nge-wibu dibanding ngoding, maka dia meminta bantuanmu untuk membuatkan program nya. Sebagai seorang programmer handal, bantulah mas Refadi untuk memenuhi keinginan nya itu. 

## Nomor 2
### source code: [click here!](https://github.com/danielcristho/seesop/blob/master/soal-shift-sisop-modul-2-b13-2022/soal2/soal2.c)

### Deskripsi soal:
Japrun bekerja di sebuah perusahaan dibidang review industri perfilman, karena kondisi saat ini sedang pandemi Covid-19, dia mendapatkan sebuah proyek untuk mencari drama korea yang tayang dan sedang ramai di Layanan Streaming Film untuk diberi review. Japrun sudah mendapatkan beberapa foto-foto poster serial dalam bentuk zip untuk diberikan review, tetapi didalam zip tersebut banyak sekali poster drama korea dan dia harus memisahkan poster-poster drama korea tersebut tergantung dengan kategorinya. Japrun merasa kesulitan untuk melakukan pekerjaannya secara manual, kamu sebagai programmer diminta Japrun untuk menyelesaikan pekerjaannya.

### Penjelasan Fungsi Utama
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

#### BackToHome()
```yml
void BackToHome() {
	char home_dir[30] = "/home/";

	char *usr;
	usr=(char *)malloc(10*sizeof(char));
	usr=getlogin();
	
	strcat(home_dir, usr);
	ChangeWorkingDirectory(home_dir);
}
```
- Membuat variabel home_dir dengan isi "/home/".
- Dapatkan user yang sedang menggunakan OS dengan fungsi getlogin.
- Lalu gabungkan variabel home_dir dengan usernya.
- Kemudian, ganti working directory dengan directory homenya.

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
	child_id = CreateChildProcess();
	
	if (child_id == 0) {
		execv(command, argv);
	}
	while ((wait(&status)) > 0);
}
```
- Membuat proses child baru dengan CreateChildProcess().
- Child tersebut kemudian execute perintah yang dimasukkan ke dalam variabel command dengan parameter argv.
- Parent Process menunggu hingga child process selesai melakukan tugasnya.

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

#### ExtractFiles()
```yml
void ExtractFiles() {
	CreateFolder("shift2");
	
  	char *argv[] = {"unzip", "drakor.zip", "-d", "shift2/drakor", NULL};
  	Execute(argv, "/usr/bin/unzip");  	
}
```
- Buat folder baru dengan nama "shift2"
- Parameter "drakor.zip" adalah zip yang ingin diextract
- Parameter "-d" untuk menyebut tempat output dan "shift2/drakor" adalah tempatnya.
- Jalankan fungsi Execute() dengan parameter argv dan "/usr/bin/unzip".

#### CopyFile(char source[], char destination[])
```yml
void CopyFile(char source[], char destination[]) {
  	char *argv[] = {"cp", source, destination, NULL};
  	Execute(argv, "/bin/cp"); 
}
```
- Parameter source adalah file yang ingin dicopy dan destination adalah tujuannya.
- Jalankan fungsi Execute() dengan parameter argv dan "/bin/cp".

#### RenameFile(char source[], char destination[])
```yml
void RenameFile(char source[], char destination[]) {
  	char *argv[] = {"mv", source, destination, NULL};
  	Execute(argv, "/usr/bin/mv");	
}
```
- Parameter source adalah file yang ingin direname dan destination adalah nama barunya.
- Jalankan fungsi Execute() dengan parameter argv dan "/usr/bin/mv".

#### RemoveFile(char file[])
```yml
void RemoveFile(char file[]) {
    	char *argv[] = {"remove", "-r", file, NULL};
    	Execute(argv, "/usr/bin/rm");
}
```
- Parameter "-r" memperbolehkan menghapus directory dan file adalah nama file yang ingin dihapus.
- Jalankan fungsi Execute() dengan parameter argv dan "/usr/bin/rm".

#### ParseString(char *d, char s[], int *i)
```yml
void ParseString(char *d, char s[], int *i) {
	int j = 0;
	while(s[*i] != ';' && s[*i] != '_' && s[*i] != '.') {
		d[j] = s[*i];
		j++;
		(*i)++;
	}
	d[j] = '\0';
}
```
- Fungsi ParseString berfungsi untuk mendapatkan huruf atau kata yang ada dalam suatu variabel string yang dimulai dari indeks i hingga menemui salah satu dari ';' atau '_' atau '.'.
- Huruf atau kata yang telah di-parse tadi diakhiri dengan '\0' untuk menandakan akhir dari string.

### Penjelasan Jawaban
#### A. Extract drakor.zip dan hapus folder yang tidak penting
```yml
int main() {
	BackToHome();
	ExtractFiles();		
	ChangeWorkingDirectory("shift2/drakor");
	DeleteFolders();
```
- Jalankan fungsi BackToHome() untuk kembali ke "/home/[user]".
- Jalankan fungsi ExtractFiles() untuk mengekstrak file drakor.zip ke dalam "shift2/drakor".
- Jalankan fungsi ChangeWorkingDirectory("shift2/drakor") untuk mengganti working directory menjadi "shift2/drakor".
- Jalankan DeleteFolders() untuk menghapus folder - folder yang tidak penting.

```yml
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
```
- Cek satu persatu file dan folder yang ada di dalam folder drakor.
- Jika ternyata tipe filenya bukan PNG (fs.st_mode-nya bukan 0100664), hapus foldernya.

#### B. Buat folder kategori untuk setiap jenis film
```yml
    CreateCategory();
```
- Kembali ke fungsi main, jalankan fungsi CreateCategory()

```yml
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
```
- Cek satu persatu file yang ada di dalam folder drakor dan jalankan fungsi ProcessPhoto dengan nama file sebagai parameter

```yml
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
```
- Pertama, kita inisialisasi variabel i untuk menunjukkan indeks string dari nama file.
- Kedua, kita pisahkan nama file menjadi title, year, dan category-nya dengan menggunakan fungsi ParseString()
- Ketiga, Jika dalam foto itu terdapat dua poster, maka pemisahan nama file diatas dijalankan lagi karena masih belum menemui '.'.

#### C. Pindahkan file ke dalam kategori yang sesuai dan rename file
```yml
        CopyFile(name, category);
		ChangeWorkingDirectory(category);
		RenameFile(name, title);
		InsertData(year, title);
```
- Copy file nama ke dalam kategori dengan fungsi CopyFile().
- Ganti working directory menjadi kategori.
- Ganti nama filenya menjadi title yang telah di-parse tadi.
- Jalankan fungsi InsertData()

```yml
void InsertData(char year[], char title[]) {
	FILE *file = fopen("temp.txt" , "a");
	
	fprintf(file, "%s %s\n", year, title);
	
	fclose(file);
}
```
- Tujuan dari fungsi ini adalah untuk menyimpan informasi tentang suatu film dari masing - masing kategori
- Informasi yang disimpan adalah tahun rilis dan judulnya.

```yml
        ChangeWorkingDirectory("../");	
	}
	RemoveFile(name);
}
```
- Kembali ke fungsi CreateCategory()
- Ubah working directory menjadi folder parentnya (yaitu drakor) dan jika poster telah dipindah ke masing - masing kategori, hapus filenya

#### D. Gambar dengan dua poster dipindah ke masing - masing kategori
Masalah ini telah diselesaikan di jawaban bagian B dan C.

#### E. Buat file data.txt yang isinya tahun dan judul film yang isinya telah disortir terlebih dahulu
```yml
    ProcessCategoryData();
  	
  	return 0;
}
```
- Kembali ke fungsi main, jalankan fungsi ProcessCategoryData()

```yml
void ProcessCategoryData() {
	struct dirent *dp;
	DIR *dir = opendir("./");
	
	if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL) {
       	if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) 	{
        	ChangeWorkingDirectory(dp->d_name);
        	SortData();
```
- Cek setiap folder kategori.
- Ganti working directory menjadi kategori tersebut.
- Lalu, jalankan fungsi SortData().

```yml
void SortData() { 	
    	FILE *file = fopen("sort.txt" , "w");
    	fclose(file);
    				
    	char *argv[] = {"sort", "-o", "sort.txt", "temp.txt", NULL};
    	Execute(argv, "/usr/bin/sort");

    	RemoveFile("temp.txt");
}
```
- Membuat file sort.txt jika belum ada menggunakan fungsi fopen().
- Isi argv dengan output file (sort.txt) dan input file (temp.txt).
- Jalankan fungsi Execute() dengan parameter argv dan "/usr/bin/sort".
- Karena dalam file temp.txt format nama adalah tahun rilis kemudian nama filmnya, yang diutamakan dalam sortir adalah tahun rilis. Jika tahun rilisnya sama, maka yang dijadikan acuan adalah nama filmnya.
- Hapus file temp.txt

```yml
    StoreData(dp->d_name);
```
- Kembali ke fungsi ProcessCategoryData().
- Jalankan fungsi StoreData dengan parameter nama folder category

```yml
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
```
- Baca setiap baris dari file sort.txt hingga EOF.
- Tahun rilis dan nama film di dalam sort.txt dimasukkan ke variabel year dan title.
- Tulis kategori apa yang sedang dibuka ke dalam file data.txt
- Kemudian, tulis nama dan tahun rilis setiap film dalam kategori tersebut.
- Akhirnya, hapus file sort.txt

```yml
        ChangeWorkingDirectory("../");
        }
    }
   	closedir(dir);
}
```
- Kembali ke fungsi ProcessCategoryData().
- Ubah Working Directory ke parent folder.
- Jalankan deretan perintah tadi hingga setiap folder dalam folder drakor telah dikunjungi.

## Nomor 3
### source code: [click here!](https://github.com/danielcristho/seesop/tree/master/soal-shift-sisop-modul-2-b13-2022/soal3)

### Deskripsi Soal

Conan adalah seorang detektif terkenal. Suatu hari, Conan menerima beberapa laporan tentang hewan di kebun binatang yang tiba-tiba hilang. Karena jenis-jenis hewan yang hilang banyak, maka perlu melakukan klasifikasi hewan apa saja yang hilang. (a) Untuk mempercepat klasifikasi, Conan diminta membuat program untuk membuat 2 directory di “/home/[USER]/modul2/” dengan nama “darat” lalu 3 detik kemudian membuat directory ke 2 dengan nama “air”. (b) Kemudian program diminta dapat melakukan extract “animal.zip” di “/home/[USER]/modul2/”. (c) Tidak hanya itu, hasil extract dipisah menjadi hewan darat dan hewan air sesuai dengan nama filenya. Untuk hewan darat dimasukkan ke folder “/home/[USER]/modul2/darat” dan untuk hewan air dimasukkan ke folder “/home/[USER]/modul2/air”. Rentang pembuatan antara folder darat dengan folder air adalah 3 detik dimana folder darat dibuat terlebih dahulu. Untuk hewan yang tidak ada keterangan air atau darat harus dihapus. (d) Setelah berhasil memisahkan hewan berdasarkan hewan darat atau hewan air. Dikarenakan jumlah burung yang ada di kebun binatang terlalu banyak, maka pihak kebun binatang harus merelakannya sehingga conan harus menghapus semua burung yang ada di directory “/home/[USER]/modul2/darat”. Hewan burung ditandai dengan adanya “bird” pada nama file.
(e) Terakhir, Conan harus membuat file list.txt di folder “/home/[USER]/modul2/air” dan membuat list nama semua hewan yang ada di directory “/home/[USER]/modul2/air” ke “list.txt” dengan format UID_[UID file permission]_Nama File.[jpg/png] dimana UID adalah user dari file tersebut file permission adalah permission dari file tersebut.
Contoh : conan_rwx_hewan.png

### Pembahasan

##### Membuat variabel global:
```yml
// variabel untuk membuat direktori baru
char *dirName[] = {"darat", "air"};

// variabel untuk mendefinisikan file unduhan dari drive
char *zipFile[] = {"animal.zip"};

// variabel untuk mendefinisikan url dari file yg akan di download
char *url[] = {"https://drive.google.com/uc?export=download&id=1YkmBhpfCQ3DBxeFmregqmwBs6Q2cy4BI"};

// variabel untuk mendefinisikan file name
char *fileName[] = {"animal"};

```

#### A. Membuat dua direktori baru

```yml
void makeDir() {
    pid_t tuna = fork();
    int statustuna;

    if(tuna < 0 ) exit(EXIT_FAILURE);

        if(tuna == 0) {
            pid_t tiger = fork();
            int statustiger;

            if(tiger < 0) exit(EXIT_FAILURE);

            if(tiger == 0) {
                char *argv[]={"mkdir", "-p",dirName[0], dirName[1], NULL};
                execv("/usr/bin/mkdir", argv);
            }
            else {
                while((wait(&statustiger)) > 0);
                pid_t child1 = fork();
                int status1;

                if(child1 < 0) exit(EXIT_FAILURE);

                if(child1 == 0){
                    pid_t child2 = fork();
                    int status2;

                    if(child2 < 0) exit(EXIT_FAILURE);
```

#### B. Download file dari Drive menggunakan wget, setelah didownload maka akan di ekstark menggunakan unzip

- [link file](https://drive.google.com/uc?export=download&id=1YkmBhpfCQ3DBxeFmregqmwBs6Q2cy4BI)

```yml
 
                    if(child2 == 0) { //download & unzip animal.zip
                        pid_t child3 = fork();
                        int status3;

                        if(child3 < 0) exit(EXIT_FAILURE);

                        if(child3 == 0) {
                            char *argv[] = {"wget", "--no-check-certificate", url[0], "-O",zipFile[0], NULL};
                            execv("/bin/wget", argv);
                        }
                            else{
                                while((wait(&status3)) > 0);
                                char *argv[] = {"unzip","-qq", zipFile[0], NULL};
                                execv("/bin/unzip", argv);
                        }
                        
                    }
```




## Anggota Kelompok

| Nama                      | NRP      |
|---------------------------|----------|
|Abidjana Zulfa Hamdika     |5025201197|
|Brian Akbar Wicaksana      |5025201207|
|Gloriyano C. Daniel Pepuho |5025201121|
|Muhammad Ghani Taufiqurr   |5025201110|
