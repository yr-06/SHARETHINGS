#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>
#include "../include/admi.h"
#include "../include/chiffrement.h"
#include "../include/personne.h"
#include "../include/annuaire.h"
#include "../include/ressources.h"
#ifndef CLEAR_STDIN
    #define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#endif

// gestion des menus
 void gestmenu(FILE *f,FILE*g, Annuaire annu,Liste ls,Personne p){
    int c;
    char*s;
    printf("Bienvenue dans le menu de notre base de données !\n");
    printf("Que souhaitez-vous faire ?\n Se connecter=0\t Creer un compte=1\n");
    scanf("%d",&c);
    switch (c)
    {
    case 0:
        s=(char*)malloc(sizeof(char)*33);
        printf("Veuillez entrer votre identifiant :\n");
        fgets(s,33,stdin);
        p=search_pers(annu,s);
        if(pers_existing(p)==1){
            printf("Voulez-vous vous connecter en tant qu'admnisitrateur ?\n OUI=1 ?\t NON=0 ?\n");
            scanf("%d",&i);
            switch (i)
            {
            case 1:
                 get_adm(f,g,annu,p);
            
            case 0:
                get_user(annu,p);
            default:
                printf("ERROR--Vous allez être redirigé\n\n");
                gestmenu(f,annu,ls,p);
        }else{

        }
        break;
    case 1:
        printf("Excellent choix !\n");
        printf("Vous allez maintenant créer votre compte, veuillez suivre les étapes sur l'écran\n");
        annu=createAccount(annu,f);
        gestmenu(f,g,annu,p);
        break;
    default:
        gestmenu(f,g,annu,p);
        break;
    }
 }

int main ( int argc, char *argv []){
    FILE *g=NULL;
    FILE *h=NULL;
    FILE *f=fopen("Mtdp_admin.txt", "r");
    g=fopen("Annuaire.json", "w");
    h=fopen("Liste.json","w");
    Personne p=initPers();
    Annuaire annu=new_annu();
    Liste ls=new_list();
    gestmenu(f,g,annu,ls,p);

}


       