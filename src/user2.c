
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure pour compte users. Si compte commun , mettre un int qui dit si oui ou non on est admin.
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
char * get_nom(user u){
        return(u->nom);

 }

char * get_prenom(user u){
        return(u->prenom);

}
char * get_mdp(user u){
        return(u->mdp);
}


char * get_ID(user u){
        return(u->ID);
}


//Setters : permet d'attribuer a des variables des valeurs

void set_nom(user u, char * nom){
        strcpy(u->nom, nom);//copie la valeur d'une chaine de caractere à la position voulue(par le biais de
//pointeur)
}


void set_prenom(user u, char * prenom){
        strcpy(u->prenom, prenom);

}

void set_mdp(user u, char * mdp){
        strcpy(u->mdp, mdp);

}

void set_ID(user u, char * ID){
        strcpy(u->ID, ID);

}
//fonctions :
//1) permet de changer de donnees (mdp, ID , etats des ressources...)
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

