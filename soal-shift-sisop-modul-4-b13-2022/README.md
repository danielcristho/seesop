# Soal Shift Sisop Modul 4 B13 2022
### source code: [click here!](https://gitlab.com/hufahamdika/soal-shift-sisop-modul-4-b13-2022/-/blob/main/_anya_b13.c)


## Nomor 1
## Deskripsi Soal:
- Semua direktori dengan awalan “Animeku_” akan terencode dengan ketentuan semua file yang terdapat huruf besar akan ter encode dengan atbash cipher dan huruf kecil akan terencode dengan rot13
- Semua direktori di-rename dengan awalan “Animeku_”, maka direktori tersebut akan menjadi direktori ter-encode dengan ketentuan sama dengan 1a.
- Apabila direktori yang terenkripsi di-rename menjadi tidak ter-encode, maka isi direktori tersebut akan terdecode.


Pada soal ini kami membuat  2 fungsi encode, yaitu fungsi encode menggunakan atbash dan rot13:
```yml

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
```

Kemudian membuat fungsi untuk mencatat setiap log

```yml

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

```

log untuk me-rename dan mkdir akan dicatat di xmp_mkdir dan xmp_rename:
```yml

    logEnc2("MKDIR", path);
    logEnc("RENAME", fpathFrom, fpathTo);
```



## Nomor 3
### Deskripsi Soal:
Ishaq adalah seseorang yang terkenal di kalangan anak informatika seluruh indonesia. Ia memiliki teman yang bernama innu dan anya, lalu ishaq bertemu dengan mereka dan melihat program yang mereka berdua kerjakan sehingga ia tidak mau kalah dengan innu untuk membantu anya dengan menambah fitur yang ada pada programnya dengan ketentuan :

### Penjelasan Fungsi:
#### binaryToDecimal(unsigned long long binary)
```yml
int binaryToDecimal(unsigned long long binary) {
	int p = 0, decimal = 0, last_digit;
	while(binary) {
		last_digit = binary % 10;
		decimal += last_digit * pow(2, p++);
		binary /= 10;
	}

	return decimal;
}
```
- Fungsi untuk merubah bilangan biner ke desimal.
- Mendapatkan angka terakhir dari bilangan biner dengan mod 10.
- Lalu, kalikan bilangan tersebut dengan 2 pangkat (mulai dari 0) dan tambahkan pada bilangan desimal.
- Ulangi sampai bilangan biner mencapai 0.

#### decimalToBinaryReverse(int decimal)
```yml 
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
```
- Fungsi untuk merubah dari bilangan desimal ke bilangan biner terbalik.
- Dapatkan hasil bagi bilangan desimal dengan 2 dan masukkan ke dalam variabel desimal.
- Ulangi hingga desimal mencapai 0.

#### uppercaseName(char *name_ori)
```yml
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
```
- Fungsi untuk merubah nama mencapai kapital.
- Mencari substring “nam_do-saq_" di dalam string name_ori, jika tidak ditemukan maka return.
- Membaca mulai dari setelah string "nam_do-saq_" hingga ditemukan '.' atau '\0'.
- Jika ditemukan huruf kecil maka binary ditambah dengan '1' dan huruf tersebut diubah menjadi kapital. Jika tidak, maka ditambah dengan '0'.
- Jika sudah selesai, maka return nama yang telah dienkripsi.

#### lowercaseName(char *name_ori)
``` yml
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
```
- Fungsi untuk merubah nama menjadi semula.
- Mencari substring “nam_do-saq_" di dalam string name_ori, jika tidak ditemukan maka return.
- Dapatkan address dari '.' terakhir yang menandakan ekstensi bilangan desimal yang ditambahkan di fungsi uppercaseName.
- Dapatkan bilangan biner dengan fungsi decimalToBinaryReverse(decimal).
- Dapatkan posisi indeks '.' pertama.
- Loop dari akhir nama menuju depan nama, jika bilangan biner yang ditunjuk saat itu adalah '1' maka ubah menjadi huruf kecil.
- Jika sudah selesai, maka copy mulai dari awal nama hingga '.' terakhir dan return string tersebut.

#### decryptPath(const char *path_ori)
```yml
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
```
- Fungsi untuk merubah path menjadi semula.
- Mencari substring “nam_do-saq_" di dalam string path_end, jika ditemukan maka assign path_end ke variabel path_end 
- Copy konten string mulai dari path_begin hingga path_end ke dec_path lalu assign path_end ke path_begin.
- Mencari substring “/" di dalam string path_end dan assign addressnya ke path_end.
- Jika tidak ditemukan, dapatkan address indeks terakhir dan assign ke path_end.
- Copy nama direktori yang ingin didekripsi ke dalam name_to_dec.
- Dekripsi nama tersebut lalu tambahkan ke dec_path.
- Jika sudah tidak ditemukan lagi substring "nam_do-saq_", maka copy sisa string dari path_end ke dec_path.

## Anggota Kelompok

| Nama                      | NRP      |
|---------------------------|----------|
|Abidjana Zulfa Hamdika     |5025201197|
|Brian Akbar Wicaksana      |5025201207|
|Gloriyano C. Daniel Pepuho |5025201121|
|Muhammad Ghani Taufiqurr   |5025201110|
