#include "../include/utils.h"

int main(int argc, char *argv[]){
    int status;

    if (argc != 3){
        printf("input invalid\n");
        printf("Harus pake ./aplikasi <username> <password> biar betul\n");
        return 1;
    }

    status = login(argv[1], argv[2]);

    if (status == 1){
        printf("Welcome admin yang punya kekuasaan\n");
        menu_admin();
    }
    else if (status == 2){
        printf("welcome orang biasa\n");
        menu_user();
    }

    return 0;
}
