#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ressources.h"
#include "../include/welcome.h"
#include "../include/personne.h"

#ifndef COLOR
    #define color(param) printf("\033[%sm",param)
#endif


void messBienvenue(){                                                   
  color("34;1");
  printf("   ***       BIENVENUE SUR SHARETHINGS       ***   \n");  
}                                                                                                                                              void messAurevoir(){
  printf("   ***       A BIENTOT !     *** ");                          exit(0);
}                                                                        

void connexionPersonne(){
  char email[32];
  char pwd[64];
  printf("Pour vous connecter : \n ");
  printf("Veuillez entrer votre email : \n");
  scanf("%s", email);//pas besoin de "&" dans le scanf lorsque c'est un char constant.
  printf("Puis votre mot de passe : \n");
  scanf("%s", pwd);
}


void inscriptionPersonnne(){
  //initialisation de l'ID plus tard à expliquer.
  Personne p = (Personne)malloc(sizeof(struct s_pers));
  printf("Vous avez choisi de vous inscrire.");
  printf("(Très bon choix ;) )\n");
  printf("Nom: ");
  scanf("%s", p->nom);
  printf("Prénom: ");
  scanf("%s", p->prenom);
  printf("Date de naissance : ");
  scanf("%s", p->date_naiss);
  printf("Email: ");
  scanf("%s", p->mail);
  printf("Mot de passe: ");
  scanf("%s",p->pwd);
  printf("Numéro de téléphone: ");
  scanf("%s",p->tel);
}


void messChoix(){
  int choix;
  printf("Bienvenue sur le site ShareThings, votre site préféré de dépôt et d'emprunt de ressources ! \n");
  printf("Choix d'options : \n");
  printf("(1) Se connecter. \n");
  printf("(2) S'inscrire. \n");
  printf("(3) Quitter\n");
  scanf("%d", &choix);
  switch(choix){
    case 1:
      connexionPersonne();
      break;
    case 2:
      inscriptionPersonnne();
      break;
    case 3:
      messAurevoir();
      break;
  }
}

void affichageGen(){
  messBienvenue();
  messChoix();
}

