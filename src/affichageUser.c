#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/ressources.h"
#include "../include/welcome.h"
#include "../include/affichageUser.h"
#include "../include/personne.h"
#include "../include/date.h"


#ifndef COLOR
    #define color(param) printf("\033[%sm",param)
#endif
/*verifier enchaînement des couleurs +intégrer JSON et fonctions modifAnnuaireUser */

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

void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

//donne les infos sur les ressources empruntées
void infoTakeRessource(Personne p, Ressource r, Liste ressources){
  affich_ress(r);
  color("32;1");
  printf("Vous devez rendre %s le ", getNom(r));
  affichTime(getDateFin(r));
  printf("\n");
  int choix;
  color("37;1");
  printf("(0) Revenir en arrière. \n");
  printf("(1) Rendre la ressource empruntée. \n");
  scanf("%d", &choix);
  viderBuffer();
  switch(choix){
    case 0:
      welcomeUser(p, ressources);
      break;
    case 1:
      setTakenBy(r, "");
      welcomeUser(p, ressources);
      break;
    default:
      infoTakeRessource(p,r,ressources);
      break;
  }

}
 
//fonction qui permet de modifier une ressource si elle nous appartient 
void modifRessource(Personne p , Ressource r, Liste l){
  
  if(haveRessource(p, r) == 0){
    color("31;1");
    printf("Cette ressource ne vous appartient pas, vous ne pouvez pas la modifier.\n");
    color("37");

  }
  else{
    int choix;
    affich_ress(r);
    color("36;1");
    printf("Voulez-vous changer une information sur votre ressource ?\n");
    color("37;1");
    printf("(1) Changer le nom.\n");
    printf("(2) Changer le type.\n");
    printf("(3) Supprimer la ressource. \n");
    printf("(4) Revenir en arrière.\n");
    
    scanf("%d", &choix);
    viderBuffer();
  
    switch(choix) {
      case 1:
        setNom(r, getString(32, "Entrer la modification sur le nom de votre ressource:\n"));
        print_ress_JSON(r);
        break;
      case 2:
        setType(r , getString(32, "Entrer la modification sur le type de votre ressource:\n"));
        print_ress_JSON(r);
       break;
      case 3:
        suppr_ress_JSON(getID_r(r));
        removeRessource(r, l);
        updateListe_JSON(l);
      case 4:
        break;
    
    }
    
    gererDropRessource(p, l);
  }
}



void modifDonneesPers(Personne p, Liste ressources){
  int choix;
	char * newMdp;
	char * checkNewMdp;
	char * newMail;
	char * newTel;
  newMail = (char*)malloc(sizeof(char)*33);
  newTel = (char*)malloc(sizeof(char)*33);
  newMdp = (char*)malloc(sizeof(char)*33);
  checkNewMdp = (char*)malloc(sizeof(char)*65);;

  affich_pers(p);
  color("36;1");
  printf("\n Vous-vous changer une information personnelle ? \n");
  color("37;1");
  printf("(0) Revenir en arrière.\n");
	printf("(1) Changer le mot de passe.\n");
	printf("(2) Changer le mail.\n");
	printf("(3) Changer le numéro de téléphone.\n");
	scanf("%d", &choix);
  viderBuffer();

  switch(choix){
    case 0:
      welcomeUser(p, ressources);
      break;
		case 1:
//             modif_pwd(p);
			printf("Entrez votre nouveau mot de passe: \n");
			scanf("%s", newMdp);
			printf("Veuillez confirmer votre mot de passe: \n");
			scanf("%s", checkNewMdp);
			if(strcmp(newMdp,checkNewMdp) == 0){ 
        color("32,1");
				printf("Votre mot de passe a été changé avec succès !\n");
        setPwd(p, newMdp);
			}else{
        color("31;1");
				printf("Erreur. Recommencez !\n");
        color("37;1");
				return modifDonneesPers(p,ressources);
			}
      welcomeUser(p, ressources);
			break;
		case 2:
//            modif_mail(p);
			printf("Entrez le nouveau mail:\n");
			scanf("%s",newMail);
      setMail(p, newMail);
      welcomeUser(p, ressources);
			break;
		case 3:
//             modif_tel;
			printf("Entrez le nouveau numéro:\n");
			scanf("%s",newTel);
      setTel(p, newTel);
      welcomeUser(p, ressources);
			break;

	}

}



void addRessourceAtListe(Personne p, Liste ressources){

  Ressource r = initRessource(ressources);
  color("36;1");
  printf("Vous souhaitez ajouter une ressource.\n");
  color("37;1");
  setNom(r, getString(32, "Entrer le nom de votre ressource: \n"));
  setType(r , getString(32, "Entrer le type de votre ressource: \n"));
  setTakenBy(r,"");
  setDropBy(r, getIDPers(p));
  setCreateDate(r, getActualTime());
  
  
  print_ress_JSON(r);
  addRessListe_JSON(r);
  
  color("32;1");
  printf("Vous avez bien ajouté la ressource %s .\n", getNom(r));
  
  welcomeUser(p, ressources);
  
}

void welcomeUser(Personne p, Liste ressources){
  int choix;
  printf("\n");
  color("36;1");
  printf("Bonjour %s", getPrenom(p));
  printf("Que voulez-vous faire ? \n");
  color("37;1");
  printf("(1) Créer une ressource. \n");
  printf("(2) Gérer les ressources déposées. \n");
  printf("(3) Emprunter une ressource. \n");
  printf("(4) Gérer les ressources empruntées. \n");
  printf("(5) Rechercher une ressource.\n");
  printf("(6) Modifier une information personnelle.\n");
  printf("(7) Voir les actions à un temps donné.\n");
  printf("(8) Quitter.\n");
  scanf("%d", &choix);
  viderBuffer();
  switch(choix){
    case 1:
      addRessourceAtListe(p, ressources);
      break;
    case 2:
      gererDropRessource(p,ressources);
      break;
    case 3:
      takeRessource(p, ressources);
      break;
    case 4:
      gererTakeRessource(p, ressources);
      break;
    case 5:
      searchRessource(p,ressources);
      break;
    case 6:
        modifDonneesPers(p,ressources);
        break;
    case 7:
        afficherActions(p, ressources);
        break;
    case 8:
      messAurevoir();
      break;
    default:
      break;
  }
}
