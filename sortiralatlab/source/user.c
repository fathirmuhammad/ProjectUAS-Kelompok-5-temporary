#include "../include/utils.h"

void menu_user() {
    int pilihan;
    do {
        printf("=================== Menu User ===================\n");
        printf("1. Tampilkan List Alat Lab Yang Tersedia\n");
        printf("2. Tampilkan List Alat Lab Yang Sedang Dipinjam\n");
        printf("3. Pinjam Alat Lab\n");
        printf("4. Kembalikan Alat Lab\n");
        printf("5. Keluar\n");
        printf("Pilih Menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                view_list();
                break;
            case 2:
                view_list_pinjam();
                break;
            case 3:
                pinjam_alat();
                break;
            case 4:
                kembalikan_alat(); 
                break;
            case 5: 
                printf("Keluar dari menu user...\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
                break;
        }
    } while (pilihan != 5); // Loop berhenti jika pilihan = 5
}

void pinjam_alat() {
    alat_lab daftar_alat[maxSize];
    int jumlah_alat = 0;
    load_alat(daftar_alat, &jumlah_alat, "../data/listbarang.txt");

    view_list(); 
    if (jumlah_alat == 0) {
        return; 
    }

    unsigned int id_pinjam;
    int kuantitas_pinjam; 
    int index_barang = -1; 

    printf("Masukkan ID Alat yang ingin dipinjam: ");
    scanf("%u", &id_pinjam);

    for (int i = 0; i < jumlah_alat; i++) {
        if (daftar_alat[i].id_alat == id_pinjam) {
            index_barang = i; 
            break;
        }
    }

    if (index_barang == -1) {
        printf("Program Gagal: ID Alat tidak ditemukan.\n");
        return;
    }

    printf("Masukkan jumlah yang ingin dipinjam (Stok tersedia: %u): ", daftar_alat[index_barang].jumlah_alat);
    scanf("%d", &kuantitas_pinjam); 

    if (kuantitas_pinjam <= 0) {
        printf("Program Gagal: Jumlah pinjam tidak valid.\n");
        return;
    }
    if (kuantitas_pinjam > daftar_alat[index_barang].jumlah_alat) {
        printf("Program Gagal: Stok tidak mencukupi!\n");
        return;
    }

  
    alat_lab alat_yg_dipinjam = daftar_alat[index_barang];
    alat_yg_dipinjam.jumlah_alat = kuantitas_pinjam; 

    // mengurangi stok di listbarang.txt
    daftar_alat[index_barang].jumlah_alat -= kuantitas_pinjam; 
    save_alat(daftar_alat, jumlah_alat, "../data/listbarang.txt"); 

    // update stok di listpinjam.txt
    alat_lab daftar_pinjam[maxSize];
    int total_pinjaman = 0; 
    load_alat(daftar_pinjam, &total_pinjaman, "../data/listpinjam.txt");

    int index_pinjam = -1;
    for (int i = 0; i < total_pinjaman; i++) {
        if (daftar_pinjam[i].id_alat == id_pinjam) {
            index_pinjam = i;
            break;
        }
    }

    if (index_pinjam != -1) { 
        daftar_pinjam[index_pinjam].jumlah_alat += kuantitas_pinjam; 
    } else { 
        daftar_pinjam[total_pinjaman] = alat_yg_dipinjam;
        total_pinjaman++; 
    }

    save_alat(daftar_pinjam, total_pinjaman, "../data/listpinjam.txt");

    printf("\nBERHASIL: Anda telah meminjam %d unit %s.\n", kuantitas_pinjam, alat_yg_dipinjam.nama_alat);
}

void kembalikan_alat() {
    alat_lab daftar_pinjam[maxSize];
    int jumlah_pinjam = 0;
    load_alat(daftar_pinjam, &jumlah_pinjam, "../data/listpinjam.txt");

    printf("\n--- Alat yang Sedang Anda Pinjam ---");
    view_list_pinjam(); 
    
    if (jumlah_pinjam == 0) {
        return; 
    }

    unsigned int id_kembali;
    int kuantitas_kembali; // Ganti nama agar jelas
    int index_pinjam = -1;

    printf("Masukkan ID Alat yang ingin dikembalikan: ");
    scanf("%u", &id_kembali);

    for (int i = 0; i < jumlah_pinjam; i++) {
        if (daftar_pinjam[i].id_alat == id_kembali) {
            index_pinjam = i; 
            break;
        }
    }

    if (index_pinjam == -1) {
        printf("Program Gagal: Anda tidak sedang meminjam alat dengan ID tersebut.\n");
        return;
    }

    printf("Masukkan jumlah yang ingin dikembalikan (Anda pinjam: %u): ", daftar_pinjam[index_pinjam].jumlah_alat);
    scanf("%d", &kuantitas_kembali);

    if (kuantitas_kembali <= 0) {
        printf("Program Gagal: Jumlah pengembalian tidak valid.\n");
        return;
    }
    if (kuantitas_kembali > daftar_pinjam[index_pinjam].jumlah_alat) {
        printf("Program Gagal: Anda tidak meminjam sebanyak itu!\n");
        return;
    }


    alat_lab daftar_alat[maxSize];
    int jumlah_alat = 0;
    load_alat(daftar_alat, &jumlah_alat, "../data/listbarang.txt");

    int index_barang = -1; 
    for (int i = 0; i < jumlah_alat; i++) {
        if (daftar_alat[i].id_alat == id_kembali) {
            index_barang = i;
            break;
        }
    }

    if (index_barang != -1) { 
        daftar_alat[index_barang].jumlah_alat += kuantitas_kembali;
        save_alat(daftar_alat, jumlah_alat, "../data/listbarang.txt");
    } else {
        printf("Info: Stok utama untuk barang ini tidak ditemukan, data pinjaman tetap dihapus.\n");
    }

    daftar_pinjam[index_pinjam].jumlah_alat -= kuantitas_kembali;

    if (daftar_pinjam[index_pinjam].jumlah_alat == 0) {
        for (int i = index_pinjam; i < jumlah_pinjam - 1; i++) {
            daftar_pinjam[i] = daftar_pinjam[i + 1];
        }
        jumlah_pinjam--; 
    }
    
    save_alat(daftar_pinjam, jumlah_pinjam, "../data/listpinjam.txt");

    printf("\nBERHASIL: Anda telah mengembalikan %d unit alat.\n", kuantitas_kembali);
}