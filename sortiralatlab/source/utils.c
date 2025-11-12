#include "../include/utils.h"

void load_alat(alat_lab *arr, int *n, char *nama_file){
    FILE *fptr = fopen(nama_file, "r");
    if (fptr == NULL){
        printf("Program Gagal: file %s tidak ditemukan.\n", nama_file);
        *n = 0;
        return;
    }

    *n = 0; 

    while(fscanf(fptr, "%u;%[^;];%[^;];%[^;];%u;%u\n", 
                    &arr[*n].id_alat,
                    arr[*n].nama_alat,
                    arr[*n].merk_alat,
                    arr[*n].model_alat,
                    &arr[*n].tahun_produksi_alat,
                    &arr[*n].jumlah_alat) == 6){

                        (*n)++;

                    }
    
    fclose(fptr);
}

void view_list() {
    alat_lab daftar_alat[maxSize];
    int jumlah_alat = 0;

    load_alat(daftar_alat, &jumlah_alat, "../data/listbarang.txt");

    if (jumlah_alat == 0) {
        printf("Belum ada alat lab yang terdaftar di listbarang.txt\n");
        return; 
    }

    printf("\n======================= DAFTAR ALAT LABORATORIUM =======================\n");
    printf("| %-3s | %-15s | %-15s | %-10s | %-5s | %-5s |\n", 
           "ID", "Nama Alat", "Merek", "Model", "Tahun", "Stok");
    printf("------------------------------------------------------------------------\n");

    for (int i = 0; i < jumlah_alat; i++) {
        printf("| %-3u | %-15s | %-15s | %-10s | %-5u | %-5u |\n",
               daftar_alat[i].id_alat,
               daftar_alat[i].nama_alat,
               daftar_alat[i].merk_alat,
               daftar_alat[i].model_alat,
               daftar_alat[i].tahun_produksi_alat,
               daftar_alat[i].jumlah_alat);
    }
    printf("=========================================================================\n\n");
}

void view_list_pinjam() {
    alat_lab daftar_alat[maxSize];
    int jumlah_alat = 0;

    load_alat(daftar_alat, &jumlah_alat, "../data/listpinjam.txt");

    if (jumlah_alat == 0) {
        printf("\nBelum ada alat lab yang sedang dipinjam.\n");
        return;
    }

    printf("\n======================== DAFTAR ALAT YANG SEDANG DIPINJAM ========================\n");
    printf("| %-3s | %-15s | %-15s | %-10s | %-5s | %-5s |\n", 
           "ID", "Nama Alat", "Merek", "Model", "Tahun", "Stok");
    printf("----------------------------------------------------------------------------------\n");

    for (int i = 0; i < jumlah_alat; i++) {
        printf("| %-3u | %-15s | %-15s | %-10s | %-5u | %-5u |\n",
               daftar_alat[i].id_alat,
               daftar_alat[i].nama_alat,
               daftar_alat[i].merk_alat,
               daftar_alat[i].model_alat,
               daftar_alat[i].tahun_produksi_alat,
               daftar_alat[i].jumlah_alat);
    }
    printf("==================================================================================\n\n");
}