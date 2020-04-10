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

/*
-tester fonctions
-modifier .h
-faire une fonction pour transférer pret--> fair une option dans choix_user
*/

//fonctions :
//permet de changer de donnees (mdp, ID , etats des ressources...)
//rajouter une option pour quitter
void changer_donnees(Personne p, int choix){
	char newMdp[32];
	char checkNewMdp[32];
	char newMail[64];
	char newTel[15];
	printf("Pour changer de mot de passe, tapez 1\n");
	printf("Pour changer le mail associé à votre compte, tapez 2\n");
	printf("Pour changer le numéro associé à votre compte, tapez 3\n");
	scanf("%d", &choix);
	switch(choix){
		case 1:
			printf("Vous avez choisi de changer de mot de passe.\n");
			printf("Entrez votre nouveau mot de passe: \n");
			scanf("%s",&newMdp);
			printf("Veuillez confirmer votre mot de passe: \n");
			scanf("%s",&checkNewMdp);
			if(strcmp(newMdp,checkNewMdp) == 0){ //strcmp :permet de comparer deux chaînes de caractères et de savoir si la première est inférieure, égale ou supérieure à la seconde.
				printf("Votre mot de passe a été changé avec succès !\n");
			}else{
				printf("Erreur. Recommencez !\n");
				return changer_donnees(p, choix);
			}
			break;
		case 2:
			printf("Vous avez choisi de changer le mail associé à votre compte.");
			printf("Entrez le nouveau mail:\n");
			scanf("%s",newMail);
			break;
		case 3:
			printf("Vous avez choisi de changer le numéro de téléphone associé à votre compte.");
			printf("Entrez le nouveau numéro:\n");
			scanf("%s",newTel);
			break;

	}

}


void suppr_compte(user u){
//permet de supprimer le compte d'un utilisateur après avoir supprimer les ressources
}
//remarque : j'aimerai tester cette fonction mais je ne sais pas très bien comment marche les FILE, 
//est-ce que pour tester je peux enlever ce paramètre ? 


/*int get_user(Annuaire annu,Liste ls,Personne p,FILE*f){
        char mdp[64];
        printf("Veuillez entrer votre mot de passe :\n");
	scanf("%s", mdp);
        mdp=chiffrementMdp(mdp);
	int n=strcmp(mdp,p->pwd);
        if (n=0){
          printf("Bienvenue %s %s !\n",get_name(p),get_prenom(p));
          printf(" Que voulez-vous faire ?\n");
          printf(" Rechercher une ressource: 1\n Modifier vos données personnelles: 2\n Supprimer une ressoure: 3\n");
          printf(" Ajouter une ressource: 4\n Emprunter une ressource: 5\n Modifier une ressource: 6\n Quitter: 0\n");       
          choix_user(annu,ls,p);
          return 0;
	}
	int i;
        printf("Mot de passe incorrect. Réessayez?\n")
        printf("OUI= 1 ?\t NON=0 ?\n");
        scanf("%d",&i);
        if(i=1){
                get_user(annu,ls,p);
        }
}
//remarque : modifier une ressource me parait vachement bizarre... Peut être pour un administrateur mais pour un user?
//ce serait pour qu'il puisse déposer sa ressource peut être? 
//ou alors seulement si elle nous appartient!
*/

//recupere une phrase entiere car le scanf sinon ne lit qu'un seul caractère sans espace
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

 

void modifRessource(Ressource r){
  //ne pas oublier de faire une condition pour vérifier si la ressource nous appartient bien
  color("35;1");
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


void choix_user(Annuaire annu,Liste ls,Personne p,FILE*f){
      int d;
      printf("Saisissez votre choix : \n");
      scanf("%d",&d);
      switch(d){
          case 0:
              printf("Vous allez être redirigé\n");
              break;
          case 1:
                char*m;
                m=(char*)malloc(sizeof(char)*33);
                printf("Veuillez entrer le type de ressources recherchées :\n");
                scanf("%33s",m);
                search_ress_type(ls,m);
                break;

          case 2:
            affich_pers(p);
            annu=modif_annuaire_user(annu,p);
            break;
          case 3:
            char*s;
            s=(char*)malloc(sizeof(char)*33);
            printf("Veuillez entrer l'identifiant de la ressource que vous souhaitez supprimer:\n");
            scanf("%33s",s);
            Ressource r=search_ress(ls,s);
            if(strcmp(getDropby(r),p->id)==0 && getDispo(r)==0){
                printf("Cette ressource va être supprimé\n");
                ls=remove_ress(ls,r);
            }else{
                printf("Vous ne pouvez pas supprimer cette ressource\ncar vous ne la posséder pas ou qu'elle est momentanément indisponible\n");
            }
            break;
          case 4:
                Ressource c=create_ress();
                ls=add_ress(ls,c);
                break;
          case 5 :
                char*z;
                z=(char*)malloc(sizeof(char)*33);
                printf("Veuillez entrer l'identifiant de la ressource que vous souhaitez emprunter:\n");
                scanf("%33s",z);
                Ressource rit=search_ress(ls,z);
                p=emprunt_ress(ls,p,rit);
                break;
          case 6 : 
            char*s;
            s=(char*)malloc(sizeof(char)*33);
            printf("Veuillez entrer l'identifiant de la ressource que vous souhaitez modifier:\n");
            scanf("%33s",s);
            Ressource rat=search_ress(ls,s);
            if(strcmp(getDropby(r),p->id)== getDispo(rat)==0){
                 ls=modif_liste(ls,rat);
            }else{
                printf("Vous ne pouvez pas modifier cette ressource\ncar vous ne la posséder pas ou qu'elle est momentanément indisponible\n")
            }
            break; 
          default :
            int i;
            printf("Choix invalide.Réessayer ?\n OUI=1 ?\t NON=0 ?\n");
            scanf("%d",&i);
            if(i=1){
                 choix_user(annu,ls,p,f);
            }
            break;
    }
    int u;
    printf("Exécuter une autre action ?\n OUI=1 ?\t NON=0 ?\n");
    scanf("%d",&u);
    if(u==1){
        choix_user(annu,ls,p,f);
    }
}


Annuaire modif_annuaire_user(Annuaire annu,Personne p,){
     int j=annu->size;
     Elementa current_a=annu->head;
     for (i=0;i<j;i++){
         if(strcmp(id,current_a->p->id)==0){
            modif_pers_user(current->a->p);
            int n=pers_existing (annu,current->a->p);
            switch (n){
                case 0:    
                    printf("Modification effectuée avec succès\n");
                    affich_pers(current->a->p);
                    return annu;

                case 1:
                    printf("Identifiant déjà utilisé.Veuillez en changer\n");
                    modif_pers_user(current->a->p);
                    break;
        
                case 3:
                    printf("Cette adresse mail est déjà liée à un compte. Veuillez en choisir une autre\n");
                    modif_pers_user(current->a->p);
                    break;
                case 4:
                    printf("Ce numéro de téléphone est déjà lié à un compte. Veuillez en utiliser un autre\n");
                    modif_pers_user(current->a->p);
                    break;
                default:
                    break;
                }
            }
            
         }
         current_a=current_a->next;
}


Liste modif_liste(Liste ls,Ressource r){
        int i;
        int j=ls->size;
        Elementl current_l=ls->head;
        for (i=0;i<j;i++){
         if(strcmp(r->ID,current_l->r->ID)==0){
            modif_ress(current_l->r);
            int n=ress_existing (ls,current_l->r);
             switch (n){
                    case 0:
                        printf("Modification effectuée avec succès\n");
                        affich_ress(current_l->r);
                        return ls;
                    case 1:
                        printf("Identifiant déjà utilisé.Veuillez en changer\n");
                        modif_ress(current_l->r);
                        break;
                    case 2:
                        print("Cette ressource existe déjà\n");
                        affich_ress(current_l->r);
                        modif_ress(current_l->r);
                        break;
                    default:
                        break;
                }
         current_l=current_l->next;
     }

}

Personne emprunt_ress(Liste ls, Personne p,Ressource r){
    if(getDispo(r)==0 && strcmp(r->DropBy,p->id)){
        setTakenBy(r,p->id);
        modifDateDeb(r);
        modifDateFin(r);
        setDispo(r,1);
        p->emprunt=add_ress(p->emprunt,r);
        printf("Votre emprunt a été enregistré avec succès\n");
        printf("Vous avez actuellement %d emprunt\n",nb_emprunt(p));
    }
    printf("Vous ne pouvez pas emprunter cette ressource\n");
    return p;
}

