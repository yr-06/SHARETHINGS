#include <stdio.h>
#include <stdlib.h>                        
#include <string.h>
#include <unistd.h>
#include "../include/ressources.h"
#include "../include/welcome.h"
#include "../include/affichageUser.h"
#include "../include/personne.h"
#include "../include/annuaire.h"
#include "../include/chiffrement.h"


#ifndef CLEAR_STDIN
    #define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#endif

#ifndef COLOR
    #define color(param) printf("\033[%sm",param)
#endif


void messBienvenue(){                                                   
  color("34;1");
printf("_______________________________\n");
printf("                               \n");
printf("       SHARETHINGS             \n");
printf("                               \n");
printf("_______________________________\n");
}






void messAurevoir(){
  color("34;1");
  
  printf("         A BIENTOT !       \n ");   
  printf("___________________________\n");                   
  exit(0);
}                                                                        

//fonction de connexion
void connexionPersonne(Liste ressources, Annuaire annu){
  char * email_id;
  char * pwd;

  email_id =(char*)malloc(sizeof(char)*16);
  pwd = (char*)malloc(sizeof(char)*16);
  color("37;1");
  printf("Pour vous connecter : \n ");
  printf("Entrez votre email ou votre identifiant de compte: \n");
  scanf("%s", email_id);
  viderBuffer();
  printf("Entrez votre mot de passe: \n");
  scanf("%s", pwd);
  viderBuffer();
  Personne p = search_pers(annu, email_id);
  if(p == NULL){
    printf("Il n'existe pas de compte associé à cet email ou identifiant. Réessayez ! \n");
    connexionPersonne(ressources, annu);
    return;
  }
  if(strcmp(getPwd(p), pwd) != 0){
    color("31;1");
    printf("Mot de passe incorrect. Réessayez !\n");
    connexionPersonne(ressources, annu);
    return;
  }
  if(getAutor(p) == 1){
    printf("Bienvenue dans le menu administrateur.\n");
  } else{
    welcomeUser(p, ressources);
  }
}

/*void inscriptionPersonnne(){
}*/


void messChoix(Liste ressources, Annuaire annu){
  color("34:1");
  int choix;
  printf("\nBienvenue sur le site ShareThings, votre site préféré de dépôt et d'emprunt de ressources ! \n");
  printf("Choix d'options : \n");
  color("37;1");
  printf("\n");
  printf("(1) Se connecter. \n");
  printf("(2) S'inscrire. \n");
  printf("(3) Quitter\n");
  printf("\n");
  color("34;1");
  printf("Entrez votre choix: ");
  scanf("%d", &choix);
  switch(choix){
    case 1:
      connexionPersonne(ressources, annu);
      break;
    case 2:
      printf("inscription");
      //inscriptionPersonnne();
      break;
    case 3:
      messAurevoir();
      break;
  }
}

void affichageGen(Liste ressources,Annuaire annu){
  messBienvenue();
  messChoix(ressources, annu);
}
