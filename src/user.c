#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>
#include "../include/user.h"
#include "../include/chiffrement.h"
#include "../include/personne.h"
#include "../include/ressources.h"

/*//structure pour compte users. Si compte commun , mettre un int qui dit si oui ou non on est admin.
typedef struct compte_u{
        char nom[32];
        char prenom[32]
        char ID[64];
        char mdp[64];
	char mail[64];
	char tel[15];
        //ressource à afficher : struct ressource_user* ressource; livres empruntes/deposes

}user;

//getters : permet de recuperer les differentes variables
char * getNom(user u){
        return(u->nom);

 }

char * getPrenom(user u){
        return(u->prenom);

}
char * getMdpUser(user u){
        return(u->mdp);
}


char * getID(user u){
        return(u->ID);
}


//Setters : permet d'attribuer a des variables des valeurs

void setNom(user u, char * nom){
        strcpy(u->nom, nom);//copie la valeur d'une chaine de caractere à la position voulue(par le biais de
//pointeur)
}


void setPrenom(user u, char * prenom){
        strcpy(u->prenom, prenom);

}

void setMdpUser(user u, char * mdp){
        strcpy(u->mdp, mdp);

}

void setID(user u, char * ID){
        strcpy(u->ID, ID);

}
//fonctions :
//permet de changer de donnees (mdp, ID , etats des ressources...)
user changer_donnees(user u, int choix){
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
			scanf("%s",&check_newMdp);
			if(strcmp(newMdp,check_newMdp) == 0){ //strcmp :permet de comparer deux chaînes de caractères et de savoir si la première est inférieure, égale ou supérieure à la seconde.
				printf("Votre message a été changé avec succès !\n");
			}else{
				printf("Erreur. Recommencez !\n");
				return changer_donnees(user u, int choix);
			}
		case 2:
			printf("Vous avez choisi de changer le mail associé à votre compte.");
			printf("Entrez le nouveau mail:\n");
			scanf("%s",newMail);
		case 3:
			printf("Vous avez choisi de changer le numéro de téléphone associé à votre compte.");
			printf("Entrez le nouveau numéro:\n");
			scanf("%s",newTel);

	}

}
void suppr_compte(user u){
//permet de supprimer le compte d'un utilisateur après avoir supprimer les ressources
}*/

int get_user(Annuaire annu,Liste ls,Personne p){
        char*mdp;
        mdp=(char*)malloc(sizeof(char)*65);
        printf("Veuillez entrer votre mot de passe :\n");
	scanf("%65s",mdp);
        mdp=chiffrementMdp(mdp);
	int n=strcmp(mdp,p->pwd);
        if (n=0){
          printf("Bienvenue %s %s !\n",get_name(p),get_prenom(p));
          printf(" Que voulez-vous faire ?\n");
          printf(" Rechrcher une ressource: 1\n Modifier vos données personnelles: 2\n Supprimer une ressoure: 3\n");
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

void modif_pers_user(Personne p){
    int i;
    printf("\n\n Que voulez-vous modifier ?\n")
    printf(" Modifier identifiant: 1\n Modifier mot de passe: 2\n Modifier adresse mail: 3\n");
    printf(" Modifier numéro de téléphone: 4\n Quitter: 0\n");
    printf(" Saisissez votre choix : \n");
    scanf("%d",&i);
    switch (i)
    {
    case 0:
        break;
    case 1:
       modif_id(p);
       break;
    case 2:
        modif_pwd(p);
        break;
    case 3:
        modif_mail(p);
        break;
    case 4:
        modif_tel(p);
        break;
    default:
        break;
    }
    int u;
    printf(" Continuer les modifications ?\n OUI=1 ?\t NON=0 ?\n");
    scanf("%d",&u);
    if(u==1){
        modif_pers_user(p);
    }
}
void modif_ress(Ressource r,Personne p){
    int i;
    printf("\n\n Que voulez-vous modifier ?\n")
    printf(" Modifier identifiant: 1\n Modifier mot de passe: 2\n Modifier adresse mail: 3\n");
    printf(" Modifier numéro de téléphone: 4\n Quitter: 0\n");
    printf(" Saisissez votre choix : \n");
    scanf("%d",&i);
    switch (i)
    {
    case 0:
        break;
    case 1:
       modif_id(p);
       break;
    case 2:
        modif_pwd(p);
        break;
    case 3:
        modif_mail(p);
        break;
    case 4:
        modif_tel(p);
        break;
    default:
        break;
    }
    int u;
    printf(" Continuer les modifications ?\n OUI=1 ?\t NON=0 ?\n");
    scanf("%d",&u);
    if(u==1){
        modif_pers_user(p);
    }
}
void choix_user(Annuaire annu,Liste ls,Personne p){
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
            modif_annuaire_user(annu,p);
            break;
          case 3:
                //supprimer une ressource
                break;
          case 4:
                //ajouter une ressource
                break;
          case 5 :
                //modifier une ressource
                break;

        
         
          default :
            int i;
            printf("Choix invalide.Réessayer ?\n OUI=1 ?\t NON=0 ?\n");
            scanf("%d",&i);
            if(i=1){
                 choix_user(annu,ls,p);
            }
            break;
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


