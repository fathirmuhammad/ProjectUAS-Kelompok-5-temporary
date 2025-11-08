typedef struct {
    unsigned int id;
    char name[50];
    char merek[30];
    char model[30];
    unsigned int tahun_produksi;
    unsigned int jumlah_unit;
} Alat;

int filekosong (const char*utils){
    
    FILE *fp = fopen ("utils.txt", "r");
    if (fp == NULL){
        return 1;
    }
}

 