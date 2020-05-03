#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>
#include "../include/affichgeUser.c"
#include "../include/chiffrement.h"
#include "../include/personne.h"
#include "../include/ressources.h"

#ifndef COLOR
    #define color(param) printf("\033[%sm",param)
#endif

//fonction qui récupère une phrase entière car le scanf ne lit que des caractères collés
char * getString(int size, char * request) {
  char * phrase = (char*)malloc(sizeof(char)*size);
  strcpy(phrase, "");
  char c = ' ';

  printf("%s", request);
  while(strlen(phrase)<size && c != '\n'){
    scanf("%c", &c);
    if(c!='\n'){
      sprintf(phrase, "%s%c", phrase, c);
    }
  }
  return phrase;
}

//fonction qui vide le buffer
void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

//fonction qui modifie les données persos de l'utilisateur
void modifDonneesPers(Personne p){
  	int choix;
	char * newMdp;
	char * checkNewMdp;
	char * newMail;
	char * newTel;
  printf("Vous-vous changer une information personnelle ? \n");
	printf("(1) Changer le mot de passe.\n");
	printf("(2) Changer le mail.\n");
	printf("(3) Changer le numéro de téléphone.\n");
	scanf("%d", &choix);
  viderBuffer();

	switch(choix){
		case 1:
			printf("Entrez votre nouveau mot de passe: \n");
			scanf("%s", newMdp);
			printf("Veuillez confirmer votre mot de passe: \n");
			scanf("%s", checkNewMdp);
			if(strcmp(newMdp,checkNewMdp) == 0){ 
				printf("Votre mot de passe a été changé avec succès !\n");
        setPwd(p, newMdp);
			}else{
				printf("Erreur. Recommencez !\n");
				return modifDonneesPers(p);
			}
			break;
		case 2:
			printf("Entrez le nouveau mail:\n");
			scanf("%s",newMail);
      setMail(p, newMail);
			break;
		case 3:
			printf("Entrez le nouveau numéro:\n");
			scanf("%s",newTel);
      setTel(p, newTel);
			break;

	}

}


//fonction qui permet de modifier une ressource si elle nous appartient 
void modifRessource(Personne p , Ressource r){
  
  color("35;1");
  if(haveRessource(p, r) == 0){
    printf("Cette ressource ne vous appartient pas, vous ne pouvez pas la modifier.\n");

  }
  else{
    int choix;
    printf("Voulez-vous changer une information sur votre ressource ?\n");
    printf("(1) Changer le nom.\n");
    printf("(2) Changer le type.\n");
    printf("(3) Quitter.\n");
    scanf("%d", &choix);
    viderBuffer();
  
    switch(choix) {
      case 1:
        setNom(r, getString(32, "Entrer la modification sur le nom de votre ressource:\n"));
      
        break;
      case 2 :
        setType(r , getString(32, "Entrer la modification sur le type de votre ressource:\n"));
       break;
      case 3 :
        messAurevoir();
        break;
    }
  }
}

//ajoute une ressource à la liste de ressources
void addRessourceAtListe(Personne p, Liste ressources){

  Ressource r = initRessource(ressources);
  printf("Vous souhaitez ajouter une ressource.\n");
  setNom(r, getString(32, "Entrer le nom de votre ressource: \n"));
  setType(r , getString(32, "Entrer le type de votre ressource: \n"));
  setDropBy(r, getID(p));

}


void welcomeUser(Personne p, Liste ressources){
  //systeme qui permet de sélectionner une ressource à modifier
  int choix;
  printf("Bonjour %s", getPrenom(p));
  printf("Que voulez-vous faire ? \n");
  printf("(1) Créer une ressource. \n");
  printf("(2) Gérer les ressources déposées. \n");
  printf("(3) Modifier une information personnelle.\n");
  scanf("%d", &choix);
  viderBuffer();
  switch(choix){
    case 1:
      addRessourceAtListe(p, ressources);
      break;
    case 2:
      modifRessource(p, getRessource(0, ressources));
      break;
    case 3:
      modifDonneesPers(p);
      break;
    default:
      break;

      
  }
}
