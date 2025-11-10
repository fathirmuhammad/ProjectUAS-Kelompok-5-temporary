#include "../include/utils.h"


static Alat daftarAlat[maxSize];
static int jumlahAlat = 0;

void simpanKeFile() {
    FILE *file = fopen("../data/alat.txt", "w"); 
    if (file == NULL) {
        printf("Gagal menyimpan ke file!\n");
        return;
    }
    for (int i = 0; i < jumlahAlat; i++) {
        fprintf(file, "%u;%s;%s;%s;%u;%u;%u\n",
                daftarAlat[i].id,
                daftarAlat[i].nama,
                daftarAlat[i].merek,
                daftarAlat[i].model,
                daftarAlat[i].tahunProduksi,
                daftarAlat[i].jumlahUnit,
                daftarAlat[i].tersedia);
    }
    fclose(file);
}

void bacaDariFile() {
    FILE *file = fopen("../data/alat.txt", "r"); 
    if (file == NULL) {
        printf("Gagal membuka file ../data/alat.txt (mungkin file belum ada?)\n");
        return;
    }

    jumlahAlat = 0; 
    
    while (jumlahAlat < maxSize && 
           fscanf(file, "%u;%99[^;];%99[^;];%99[^;];%u;%u;%u\n",
                  &daftarAlat[jumlahAlat].id,
                  daftarAlat[jumlahAlat].nama,
                  daftarAlat[jumlahAlat].merek,
                  daftarAlat[jumlahAlat].model,
                  &daftarAlat[jumlahAlat].tahunProduksi,
                  &daftarAlat[jumlahAlat].jumlahUnit,
                  &daftarAlat[jumlahAlat].tersedia) == 7) {
        jumlahAlat++;
    }

    fclose(file);
}

void semuaAlat() {
    printf("\n=== DAFTAR SEMUA ALAT ===\n");
    printf("ID | Nama | Merek | Model | Tahun | Total | Tersedia\n");
    for (int i = 0; i < jumlahAlat; i++) {
        printf("%2u | %s | %s | %s | %u | %u | %u\n",
               daftarAlat[i].id,
               daftarAlat[i].nama,
               daftarAlat[i].merek,
               daftarAlat[i].model,
               daftarAlat[i].tahunProduksi,
               daftarAlat[i].jumlahUnit,
               daftarAlat[i].tersedia);
    }
}

void tersedia() {
    printf("\n=== ALAT YANG TERSEDIA ===\n");
    printf("ID | Nama | Merek | Model | Tahun | Total | Tersedia\n");

    int ada = 0;
    for (int i = 0; i < jumlahAlat; i++) {
        if (daftarAlat[i].tersedia > 0) {
            printf("%2u | %s | %s | %s | %u | %u | %u\n",
                   daftarAlat[i].id,
                   daftarAlat[i].nama,
                   daftarAlat[i].merek,
                   daftarAlat[i].model,
                   daftarAlat[i].tahunProduksi,
                   daftarAlat[i].jumlahUnit,
                   daftarAlat[i].tersedia);
            ada = 1;
        }
    }
    if (!ada) printf("Tidak ada alat yang tersedia.\n");
}

void pinjamAlat() {
    unsigned int idCari;
    tersedia();
    printf("\nMasukkan ID alat yang ingin dipinjam: ");
    scanf("%u", &idCari);

    int foundIdx = -1;
    for(int i=0; i<jumlahAlat; i++){
        if(daftarAlat[i].id == idCari){
            foundIdx = i;
            break;
        }
    }

    if (foundIdx == -1) {
        printf("ID %u tidak ditemukan!\n", idCari);
        return;
    }

    if (daftarAlat[foundIdx].tersedia > 0) {
        daftarAlat[foundIdx].tersedia--;
        simpanKeFile();
        printf("Anda berhasil meminjam alat: %s\n", daftarAlat[foundIdx].nama);
    } else {
        printf("Alat '%s' tidak tersedia saat ini.\n", daftarAlat[foundIdx].nama);
    }
}

void kembalikanAlat() {
    unsigned int idCari;
    semuaAlat(); // Menampilkan semua alat agar user tahu ID nya
    printf("\nMasukkan ID alat yang ingin dikembalikan: ");
    scanf("%u", &idCari);

    int foundIdx = -1;
    for(int i=0; i<jumlahAlat; i++){
        if(daftarAlat[i].id == idCari){
            foundIdx = i;
            break;
        }
    }

    if (foundIdx == -1) {
        printf("ID %u tidak ditemukan!\n", idCari);
        return;
    }

    if (daftarAlat[foundIdx].tersedia < daftarAlat[foundIdx].jumlahUnit) {
        daftarAlat[foundIdx].tersedia++;
        simpanKeFile();
        printf("Alat '%s' telah dikembalikan.\n", daftarAlat[foundIdx].nama);
    } else {
        printf("Semua unit alat '%s' sudah lengkap.\n", daftarAlat[foundIdx].nama);
    }
}


void menu_user() {
    int pilihan;
    bacaDariFile(); // Baca file saat menu user dimulai

    do {
        printf("\n===== Menu User =====\n");
        printf("1. Lihat Semua Alat\n");
        printf("2. Lihat Alat Tersedia\n");
        printf("3. Pinjam Alat\n");
        printf("4. Kembalikan Alat\n");
        printf("5. Keluar ke Login Utama\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        
        // Membersihkan buffer
        while(getchar() != '\n'); 

        switch (pilihan) {
            case 1: semuaAlat(); break;
            case 2: tersedia(); break;
            case 3: pinjamAlat(); break;
            case 4: kembalikanAlat(); break;
            case 5: printf("Keluar dari menu user...\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 5);
}