#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_BUKU 100

typedef struct {
    char kode[50];      // Kode buku (unique)
    char judul[100];    // Judul buku
    char penulis[100];  // Nama penulis
    char penerbit[100]; // Nama penerbit
    int stock;          // Jumlah stok buku
} Buku;

void inputData(Buku *buku) {
    printf("Masukkan kode buku: ");
    fgets(buku->kode, sizeof(buku->kode), stdin);
    strtok(buku->kode, "\n");

    printf("Masukkan judul buku: ");
    fgets(buku->judul, sizeof(buku->judul), stdin);
    strtok(buku->judul, "\n");

    printf("Masukkan nama penulis: ");
    fgets(buku->penulis, sizeof(buku->penulis), stdin);
    strtok(buku->penulis, "\n");

    printf("Masukkan nama penerbit: ");
    fgets(buku->penerbit, sizeof(buku->penerbit), stdin);
    strtok(buku->penerbit, "\n");

    printf("Masukkan jumlah stok: ");
    scanf("%d", &buku->stock);
    getchar(); // Menghapus newline dari buffer
}

void display(const Buku *buku) {
    printf("Kode Buku: %s\n", buku->kode);
    printf("Judul Buku: %s\n", buku->judul);
    printf("Penulis: %s\n", buku->penulis);
    printf("Penerbit: %s\n", buku->penerbit);
    printf("Jumlah Stok: %d\n", buku->stock);
    printf("---------------------------\n");
}

void tambahBuku(Buku buku[], int *jumlahBuku) {
    if (*jumlahBuku >= MAX_BUKU) {
        printf("Stok buku sudah penuh!\n");
        return;
    }
    inputData(&buku[*jumlahBuku]);
    (*jumlahBuku)++;
    printf("Buku berhasil ditambahkan!\n");
}

void hapusBuku(Buku buku[], int *jumlahBuku) {
    char kode[50];
    printf("Masukkan kode buku yang ingin dihapus: ");
    fgets(kode, sizeof(kode), stdin);
    strtok(kode, "\n");

    for (int i = 0; i < *jumlahBuku; i++) {
        if (strcmp(buku[i].kode, kode) == 0) {
            for (int j = i; j < *jumlahBuku - 1; j++) {
                buku[j] = buku[j + 1];
            }
            (*jumlahBuku)--;
            printf("Buku berhasil dihapus!\n");
            return;
        }
    }
    printf("Buku dengan kode tersebut tidak ditemukan!\n");
}

void tampilkanBuku(const Buku buku[], int jumlahBuku) {
    if (jumlahBuku == 0) {
        printf("Tidak ada buku yang tersedia.\n");
        return;
    }

    for (int i = 0; i < jumlahBuku; i++) {
        display(&buku[i]);
    }
}

void cariBuku(const Buku buku[], int jumlahBuku) {
    char judul[100];
    printf("Masukkan judul buku yang ingin dicari: ");
    fgets(judul, sizeof(judul), stdin);
    strtok(judul, "\n");

    for (int i = 0; i < jumlahBuku; i++) {
        if (strstr(buku[i].judul, judul) != NULL) {
            display(&buku[i]);
            return;
        }
    }

    if (strstr("pot", judul) != NULL) {
        printf("Menampilkan buku terkait Harry Potter:\n");
        for (int i = 0; i < jumlahBuku; i++) {
            if (strstr(buku[i].judul, "Harry Potter") != NULL) {
                display(&buku[i]);
            }
        }
        return;
    }

    printf("Buku dengan judul tersebut tidak ditemukan!\n");
}

void cariBukuAwalan(const Buku buku[], int jumlahBuku) {
    char huruf;
    printf("Masukkan huruf judul buku: ");
    scanf(" %c", &huruf);
    getchar();

    int ditemukan = 0;
    for (int i = 0; i < jumlahBuku; i++) {
        if (toupper(buku[i].judul[0]) == toupper(huruf)) {
            display(&buku[i]);
            ditemukan = 1;
        }
    }

    if (!ditemukan) {
        printf("Tidak ada buku dengan judul yang dimulai dengan huruf '%c'.\n", huruf);
    }
}

void cariBukuHarryPotter(const Buku buku[], int jumlahBuku) {
    char keyword[] = "harrypotter";
    int ditemukan = 0;

    for (int i = 0; i < jumlahBuku; i++) {
        char bukuJudulLower[100];
        int j = 0;

        for (j = 0; buku[i].judul[j]; j++) {
            bukuJudulLower[j] = tolower(buku[i].judul[j]);
        }
        bukuJudulLower[j] = '\0'; 

        char keywordLower[100];
        for (int k = 0; keyword[k]; k++) {
            keywordLower[k] = tolower(keyword[k]);
        }
        keywordLower[strlen(keyword)] = '\0'; 

        if (strstr(bukuJudulLower, keywordLower)) {
            display(&buku[i]);
            ditemukan = 1;
        }
    }

    if (!ditemukan) {
        printf("Tidak ada buku dengan kata 'harrypotter' dalam judul.\n");
    }
}

int main() {
    Buku buku[MAX_BUKU];
    int jumlahBuku = 0;
    int pilihan;

    do {
        printf("\n=== MENU PERPUSTAKAAN ===\n");
        printf("1. Tambah Buku\n");
        printf("2. Hapus Buku\n");
        printf("3. Tampilkan Data Buku\n");
        printf("4. Cari Buku\n");
        printf("5. Cari Buku Berdasarkan Awalan Huruf\n");
        printf("6. cariBukuHarryPotter\n");
        printf("7. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar(); 

        switch (pilihan) {
            case 1:
                tambahBuku(buku, &jumlahBuku);
                break;
            case 2:
                hapusBuku(buku, &jumlahBuku);
                break;
            case 3:
                tampilkanBuku(buku, jumlahBuku);
                break;
            case 4:
                cariBuku(buku, jumlahBuku);
                break;
            case 5:
                cariBukuAwalan(buku, jumlahBuku);
                break;
            case 6:
                cariBukuHarryPotter(buku, jumlahBuku);
                break;

            case 7:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (pilihan != 7);

    return 0;
}


























