
#include <stdio.h>
#include <stlib.h>
#include "../include/struct.h"
//Cc,c Ali je comprends tjrs pas le dropBy et le takenBy ?


//structure pour les ressources
//ressources : fournisseur + demandeurs
 struct ressources_u{
	char dropBy; //déposé par --> sera remplacé par l'ID si non dispo; sinon sera égal à '0'
	char takenBy; //pris par --> sera remplacé par l'ID si non dispo; sinon sera égal à '0'
	char * type;//type de ressources : emprunt, depot
	char ID[64]; //une liste de ressources est associée à un compte précis
	char *date_deb;//date de début d'emprunt
	char *date_fin;//date de fin d'emprunt
	struct ressources_u *next;// pointeur vers la ressource suivante afin de rattacher une ressource à son 
//propriétaire
}ressources;




//getters
//recuperer les informations liees a la ressource
char * getID(ressources r){
	return(r->ID);
}

char * getDropBy(ressources r){
	return(r->dropBy);
}

char * getTakenBy(ressources r){
	return(r->takenBy);
}

ressources getNextRessource(ressources r){
	return(r->next);
}


//setters
//associe des valeurs a certaines variables


void setID(ressources r, char * ID){
	strcpy(r->ID,ID);
}

void setType(ressources r, char * type){
	strcpy(r->type,type);
}




//fonctions
ressources suppr_ressource(ressources r){
//supprime les ressources d'une personne

}

char ressource_dispo(ressources r){
//permet de savoir si une ressource est disponible

}
int nb_pret(s_pers p){
//consulter le nombre de pret
}

int nb_emprunt(s_pers p){
//consulter le nombre d'emprunt
}

void rappel_finEmprunt(ressources r){
//va afficher un message de rappel quand ce sera la fin de l'emprunt
}

