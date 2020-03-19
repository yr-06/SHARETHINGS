#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>
#include "../include/admi.h"
#include "../include/struct.h"
void get_adm(FILE *f){
    if(f=null){
        initialize(f);
    }
    char *s;
    char *c;
    int n;
    printf("Veuillez entrer le mot de passe administrateur :\n");
    scanf("%s",&s);
    s=crypt(s,);
    c=crypt(c,);
    fscanf(f,"%s",&c);
    int n=strcmp(s,c);
    if (n=0){
        printf("Bienvenue dans le menu administrateur\n");
        printf("Que voulez-vous faire ?\n");
        printf("Ajouter un usager: 1\n Modifier les données d'un usager: 2\n Supprimer un usager: 3\n");
        printf("Afficher la liste des usagers:4\n Quitter: 0\n");
        choix();
    }
    printf("Mot de passe incorrect. Réessayez?\n")
    printf("OUI= 1, NON=0\n");
    printf("votre choix ")
    scanf("%d",&n);
    if(n=1){
         get_admf(f);
    }
}
void init_mtp(FILE *f){
    printf("Veuillez initialiser le mot de passe administrateur:\n"
    
    scanf("%s",&s);
    fprintf(f,
}

void add_ress(){};
void modif_ress(){}; 
void add_pers(){};
void modif_pers(){}; 
void supp_pers(){};
void affichPers(){};
void choix(){
      int d;
      printf("Saisissez votre choix: ");
      scanf("%d",d);
      switch(d){
          case 0:
              printf("Vous allez être redirigé\n");
              break;
          case 1:
              add_pers();
              break;

          case 2:
              modif_pers();
              break;
          
          case 3:
              supp_pers();
              break;
          
          case 4:
              affichPers();
              break;
          
          default :
              printf("Choix invalide");
              choix();
              break;
    }
}