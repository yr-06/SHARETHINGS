#include <stdio.h>
#include <assert.h>
#include <crypt.h>
#include "../include/personne.h"
#include "../include/ressources.h"
/*Faire des setters et des getters +completer code des fonctions vides-->demander aux filles ou à PY*/

struct s_pers {
    int i;//numéro de compte (correspondra aussi à son indice dans Annuaire)
    autor a;//enum qui definit autorisation ou non d'entrer ds le menu admin
    char nom[32];//nom de la personne
    char prenom[32];//prenom de la personne
    char *id;//identifiant de son compte
    char *pwd;//mot de passe lié au compte
    char mail[64];//mail de la personne
    char tel[15];//numero de telephone de la personne
    Liste emprunt;//Liste de Ressources empruntées actuellement par la personne
    //Liste possession;--> liste des ressources dont la personne est proprio --> necessaire?
};

struct s_elementa{
    int i;
    Personne p;
    s_elementa *previous;
    s_elementa *next;
};//element d'un Annuaire


struct s_annuaire {
    int size;
    Elementa head;
    Elementa tail;
};

typedef enum autorisation [USER=0,ADMIN=1] autor;
//Fonctions sur listes de Personnes= type Annuaire




int nb_pret(Personne p){
	return(p->emprunt->size);
//consulter le nombre de pret
}

Annuaire push_ba(Annuaire annu,int i, Elementa a){

}

Annuaire push_fa(Annuaire a,Elementa a){

}

Annuaire pop_fa(Annuaire ls){

}

Annuaire pop_ba(Annuaire ls){

}

Annuaire insert_at(int i,Personne pers,Annuaire annu){
    assert(i<annu->size)&&(i>=0);
    switch(i){
        case 0:
            return (push_f(annu,pers));
        case((annu->size)-1):
            return (push_b(annu,pers));
        default :
            Elementa a= (Elementa)malloc(sizeof(struct s_elementa));
            a->p=pers;
            int j=0;
            Elementa current_a=annu->head;
            for(j=0;j<i;j++){
                current_a=current_a->next;
            }
            current_a->previous->next=a;
            a->previous=current_a->previous;
            current_a->previous=a;
            a->next=current_a;
            a->pers->i=i;
            annu->size++;
            return annu;
    }
}

Annuaire remove_at(int i,Annuaire annu){
    assert(i<lsannu->size)&&(i>=0);
    switch(i){
        case 0:
            return (pop_f(annu));
        case((annu->size)-1):
            return (pop_b(annu));
        default :
            int j=0;
            Elementa current_a=annu->head;
            for(j=0;j<i;j++){
                current_a=current_a->next;
            }
            current_a->previous->next=current_a->next;
            current_a->next->previous=current_a;
            free(current_a);
            annu->size--;
            return annu;
    }
}


