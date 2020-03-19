
#include <stdio.h>
#include <stlib.h>



//structure pour les ressources
//ressources : fournisseur + demandeurs
enum type {LIVRE=0, BD=1, ORDINATEURS=2, JOURNAL=3,MANGAS=4};

typedef struct ressources_u{
	char dropBy; //déposé par --> sera remplacé par l'ID si non dispo; sinon sera égal à '0'
	char takenBy; //pris par --> sera remplacé par l'ID si non dispo; sinon sera égal à '0'
	enum type;//type de ressources : emprunt, depot
	char ID[64]; //une liste de ressources est associée à un compte précis
	char *date_deb;//date de début d'emprunt
	char *date_fin;//date de fin d'emprunt
	struct ressources_u *next;// pointeur vers la ressource suivante
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

void setType(ressources r, int type){
	strcpy(r->type,type);
}


//fonctions
void suppr_ressource(ressources r){


}


user supprCompte(user u){

}
