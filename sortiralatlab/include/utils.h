#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>

#define maxSize 80

typedef struct{
    unsigned int id_alat;
    char nama_alat[maxSize];
    char merk_alat[maxSize];
    char model_alat[maxSize];
    unsigned int tahun_produksi_alat;
    unsigned int jumlah_alat;
}alat_lab;

int login(char *username, char *password);
void load_alat(alat_lab *arr, int *n, char *nama_file);
void menu_admin();
void view_list();
void view_list_pinjam();
void edit_list();
void add_alat();
void delete_alat();
void update_alat();
void menu_user();
void pinjam_alat();
void kembalikan_alat();

#endif

