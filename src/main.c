#include <stdio.h>
#include "struct.h"
//Initialise mot de passe

// gestion des menus
void gestmenu(FILE *f,FILE *g)){
    int m;
    printf("Bienvenue !\n");
    printf("Menu administrateur=1, Menu usager=2\n");
    printf("Veuillez choisir votre option d'identification :");
    scanf("%d",&m);
    if (m=1){
        get_adm(f);
    }
    if (m=2){
        get_user(g);
    }
}

int main ( int argc, char *argv []){
    FILE *f=NULL;
    FILE *g=NULL;
    f=fopen("mtp_amin.txt", "a+");
    g=fopen("id_users.txt", "a+");
    gestmenu(f,g);

}
