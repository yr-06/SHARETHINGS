#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>
#include "../include/admi.h"
#include "../include/chiffrement.h"
#include "../include/annuaire.h"

#ifndef CLEAR_STDIN
    #define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#endif

// gestion des menus
 void gestmenu(FILE *f,FILE*g,FILE*h,Annuaire annu,Liste ls,Personne p){
    CLEAR_STDIN
    int c;
    char*s;
    printf("Bienvenue dans le menu de notre base de données !\n");
    printf("Que souhaitez-vous faire ?\n Se connecter=0\t Creer un compte=1\t Quitter=2\n");
    scanf("%d",&c);
    switch (c)
    {
    case 0:
        s=(char*)malloc(sizeof(char)*33);
        printf("Veuillez entrer votre identifiant ou votre e-mail:\n");
        fgets(s,33,stdin);
        p=search_pers(annu,s);
        if(pers_existing(p)==1){
            printf("Voulez-vous vous connecter en tant qu'admnisitrateur ?\n OUI=1 ?\t NON=0 ?\n");
            scanf("%d",&i);
            switch (i)
            {
            case 0:
                get_user(annu,p);
                break;
            case 1:
                get_adm(f,g,h,annu,ls,p);
                break;
            default:
                printf("ERROR--Vous allez être redirigé\n\n");
                gestmenu(f,g,h,annu,ls,p);
                break;
            }
        }
        break;
    case 1:
        printf("Excellent choix !\n");
        printf("Vous allez maintenant créer votre compte, veuillez suivre les étapes à l'écran\n");
        annu=createAccount(annu,f);
        gestmenu(f,g,h,annu,ls,p);
        break;
    case 2:
        printf("Au revoir !\n");
        return;
        
    default:
        
       
        break;
    }

}
 

int main ( int argc, char *argv []){
    Personne p=initPers();
    Annuaire annu=new_annu();
    Liste ls=new_list();
    ls=LoadListe(ls);
    annu=LoadAnnu(annu);
    
    
    //gestmenu(f,g,h,annu,ls,p);
    return 0;

}


       
