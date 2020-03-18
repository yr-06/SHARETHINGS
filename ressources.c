
#include <stdio.h>
#include <stlib.h>



//structure pour les ressources
//ressources : fournisseur + demandeurs
enum type {
typedef struct ressources_u{
	int dispo;//0 si ressource pas disponible; 1 si ressource disponible
	enum type;//type de ressources : emprunt, depot
	char ID[64]; //une liste de ressources est associée à un compte précis
	char *date_deb;//date de début d'emprunt
	user u;//compte associé à remplir
	char *date_fin;//date de fin d'emprunt
	struct ressources_u *next;// pointeur vers la ressource suivante
}ressources;


void suppr_ressource(ressources r){


}

int nb_pret(ressources r){

}

int nb_emprunt(ressources r){

}

int nb_depot(ressources r){

}

user supprCompte(user u){

}
