#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>
#include "../include/admi.h"
#include "../include/chiffrement.h"
#include "../include/personne.h"
#include "../include/ressources.h"
//Initialise mot de passe

// gestion des menus
typedef enum connexion{
    GET_CONNECT;
    CREATE_PERS;
    CONNECT_ADMIN;
    CONNECT_USER;
}Connexion;

 void gestmenu(FILE *f,FILE*g, Annuaire annu, Personne p){
    Connexion c=0;
    printf("Bienvenue dans le menu de notre base de données !\n");
    printf("Que souhaitez-vous faire ?\n Se connecter=0\t Creer un compte=1\n");
    scanf("%d",&c);
    switch (c)
    {
    case GET_CONNECT:
        char*s;
        s=(char*)malloc(sizeof(char)*33);
        printf("Veuillez entrer votre identifiant (tapez):\n");
        scanf("%33s",s);
        p=search_pers(annu,s);
        if(pers_existing(p)==1){
            Connexion i;
            printf("Voulez-vous vous connecter en tant qu'admnisitrateur ?\n OUI=3 ?\t NON=4 ?\n");
            scanf("%d",&i);
            switch (i)
            {
            case CONNECT_ADMIN:
                 get_adm(f,g,annu,p);
            
            case  CONNECT_USER:
                get_user(annu,p);
            default:
                printf("ERROR--Vous allez être redirigé\n\n");
                gestmenu(f,annu,p);
        }

int main ( int argc, char *argv []){
    FILE *f=NULL;
    FILE *g=NULL;
    FILE *h=NULL;
    f=fopen("mtp_amin.txt", "a+");
    g=fopen("Users.json", "a+");
    h=fopen("Ressources.json","a+");
    gestmenu(f,g);

}
