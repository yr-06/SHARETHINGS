
#include <stdio.h>
#include <stlib.h>
#include <assert.h>
#include <crypt.h>
#include "../include/chiffrement.h"
#include "../include/ressources.h"


//le takenBy fait office de boolean mais en chaine de caractères. Tout simplement, si une ressource
//qu'on veut emprunter est disponible, alors la valeur de takenBy vaudra 0 ou ' '.
// Si elle ne l'est pas, ce sera remplacé non pas par 1 mais pas l'identifiant de celui qui l'a pris.
//Cela permet de savoir qui a emprunté la ressource. Ce char nous aide aussi pour la fonction "dispo".
//Pour le dropBy, en effet ca n'avait rien à voir. J'espère que tu comprendras mieux avec les nvx coms. 

//structure pour les ressources
//ressources : fournisseur + demandeurs
 
 struct s_ressource {
    char *type;//type de ressouces: livre, bouteilles,CD,magazines,etc...
    char nom[32];//nom de la ressource
    char *takenBy_nom;
    char *takenBy_prenom;
    statut t;//enum définissant disponibilité de la ressource--> sorte de booléen
    char *nom_proprio;// nom du proprio de la ressource-->permet de comparer avec le nom d'une Personne si besoin
    char *prenom_proprio;//prenom du proprio  de la ressource-->permet de comparer avec le prénom d'une Personne si besoin
    char *date_d;//date de debut du pret 
    char *date_f;//date de fin du pret
    /*si ressource dispo laisser dernière date de pret, ne les modifier que lorsque la ressource est pretée à nouveau */
};

struct s_elementl{
    int i;
    Ressource r;
    s_elementl *previous;
    s_elementl *next;
};//element d'une Liste

struct s_liste {
    int size;
    Elementl head;
    Elementl tail;
};
typedef enum en_statut {LIBRE=0; EMPRUNT} statut;




//getters
//recuperer les informations liees a la ressource
char * getID(Ressource r){
	return(r->ID);
}

char * getDropBy(Ressource r){
	return(r->dropBy);
}

char * getTakenBy(Ressource r){
	return(r->takenBy);
}

Ressource getNextRessource(Ressource r){
	return(r->next);
}


//setters
//associe des valeurs a certaines variables


void setID(Ressource r, char * ID){
	strcpy(r->ID,ID);
}

void setType(Ressource r, char * type){
	strcpy(r->type,type);
}




//fonctions sur ressources
Ressource suppr_ressource(Ressource r){
//supprime les ressources d'une personne

}

char ressource_dispo(Ressource r){
//permet de savoir si une ressource est disponible

}
int nb_pret(s_pers p){
	liste = p->emprunt;
	return(size(liste));
//consulter le nombre de pret
}

int nb_emprunt(Personne p){
//consulter le nombre d'emprunt
}

void rappel_finEmprunt(Ressources r){
//va afficher un message de rappel quand ce sera la fin de l'emprunt
}

//Fonctions sur Liste de Ressources

Liste push_bl(Liste ls,int i, Elementl l){

}

Liste push_fl(Liste ls,Elementl l){

}

Liste pop_fl(Liste ls){

}

Liste pop_bl(Liste ls){

}

Liste insert_at(int i,Ressource ress,Liste ls){
    assert(i<ls->size)&&(i>=0);
    switch(i){
        case 0:
            return (push_fl(ls,ress));
        case((ls->size)-1):
            return (push_bl(ls,ress));
        default :
            Elementl l= (Elementl)malloc(sizeof(struct s_elementl));
            l->r=ress;
            int j=0;
            Elementl current_l=ls->head;
            for(j=0;j<i;j++){
                current_l=current_l->next;
            }
            current_l->previous->next=l;
            l->previous=current_l->previous;
            current_l->previous=l;
            l->next=current_l;
            ls->size++;
            return ls;
    }
}

Liste remove_at(int i,Liste ls){
    assert(i<ls->size)&&(i>=0);
    switch(i){
        case 0:
            return (pop_fl(ls));
        case((ls->size)-1):
            return (pop_bl(ls));
        default :
            int j=0;
            Elementl current_l=ls->head;
            for(j=0;j<i;j++){
                current_l=current_l->next;
            }
            current_l->previous->next=current_l->next;
            current_l->next->previous=current_l;
            free(current_l);
            ls->size--;
            return ls;
    }
    
}