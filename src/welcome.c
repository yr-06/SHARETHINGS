#include <stdio.h>
#include <stdlib.h>                        
#include <string.h>
#include <unistd.h>
#include "../include/ressources.h"
#include "../include/welcome.h"
#include "../include/affichageUser.h"
#include "../include/affichageAdmin.h"
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
  color("37");
}

void messAurevoir(){
  color("34;1");
  
  printf("         A BIENTOT !       \n ");   
  printf("___________________________\n");     
  color("37");              
  exit(0);
}                                                                        

//fonction de connexion
void connexionPersonne(Liste ressources, Annuaire annu){
  char * email_id;
  char * pwd;

  email_id =(char*)malloc(sizeof(char)*33);
  pwd = (char*)malloc(sizeof(char)*65);
  color("37;1");
  printf("Pour vous connecter : \n ");
  printf("Entrez votre email ou votre identifiant de compte: \n");
  fgets(email_id,33,stdin);
  //scanf("%s", email_id);
  viderBuffer();
  printf("Entrez votre mot de passe: \n");
  fgets(pwd,65,stdin);
  //scanf("%s", pwd);
  viderBuffer();
  Personne p = search_pers(annu, email_id);
  if(p == NULL){
    int i;
    color("31;1");
    printf("Il n'existe pas de compte associé à cet email ou identifiant. Réessayez ?\nOUI=1 ?\tNON=0?\n");
    color("37");
    scanf("%d",&i);
    if(i==1){
      free(email_id);
      free(pwd);
      connexionPersonne(ressources, annu);
    }else{
      return;
    }
  }
  if(strcmp(getPwd(p),chiffrementMdp(pwd)) != 0){
    int d;
    color("31;1");
    printf("Mot de passe incorrect. Réessayez ?\nOUI=1 ?\tNON=0?\n");
    color("37");
    scanf("%d",&d);
    if(d==1){
      free(email_id);
      free(pwd);
      connexionPersonne(ressources, annu);
    }else{
      return;
    }
  }
  if(getAutor(p) == 1){
    welcomeAdmin(annu,ressources,p);
  } else{
    welcomeUser(p,ressources);
  }
}

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
  color("37");
  scanf("%d", &choix);
  switch(choix){
    case 1:
      connexionPersonne(ressources, annu);
      messChoix(ressources,annu);
      break;
    case 2:
      color("36");
      printf("Excellent choix !\n");
      printf("Vous allez maintenant créer votre compte, veuillez suivre les étapes à l'écran\n");
      color("37");
      annu=createAccount(annu);
      return messChoix(ressources,annu);
    case 3:
      messAurevoir();
      break;
    default:
      color("31;1");
      printf("Choix invalide.Réessayer ?\n OUI=1 ?\t NON=0 ?\n");
      color("31;1");
      int i;
      scanf("%d",&i);
      if(i==1){
        messChoix(ressources,annu);
      }else{
        return;
      }
  }
  
}

void affichageGen(Liste ressources,Annuaire annu){
  messBienvenue();
  messChoix(ressources, annu);
}
