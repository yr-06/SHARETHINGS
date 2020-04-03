#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void messBienvenue(){
	printf("   ***       BIENVENUE SUR SHARETHINGS       ***   ");
}


void messAurevoir(){
	printf("   ***       A BIENTOT !     *** ");
	exit(0);
}

void messChoix(){
	int choix;
	printf("Bienvenue sur le site ShareThings, votre site préféré pour le dépôt et l'emprunt d'une ressource :)!\n"
        printf(" ~ ~ ~ ~  ~ ~ ~ ~  ~ ~ ~ ~  ~ ~ ~ ~  ~ ~ ~ ~  ~ ~ ~ ~  ~ ~ ~ ~  ~ ~ ~ ~  ~ ~ ~ ~  ~ ~ ~ ~  ~ ~ ~ ~ \n");
	printf("Choix d'options: \n ");
	printf("(1) Se connecter. \n"
	printf("(2) S'inscrire.\n");
	printf("(3) Quitter.\n"); //exit(0) <-- fonction dans stdlib
	scanf("%d", &choix);
	switch(choix){
		case 1:
			printf("Connexion");
			break;
			//fonction qui permettra de se connecter et de déterminer si la personne qui se connecte est 
			//admin ou user grâce à la variable créée dans la structure.
		case 2:
			printf("Inscription");
			break;
			//fonction qui permettra de créer un nouveau compte utilisateur uniquement.
		case 3:
			messAurevoir();
			break;
	}

}

void affichageGen(){
	messBienvenue();
	messChoix();
}
