#include <stdio.h>
#include <assert.h>
#include <crypt.h>
#include "../include/struct.h"

struct s_pers {
    int i;
    char nom[32];
    char prenom[32];
    char *id;
    char *pwd;
    Liste l;
};

struct s_ressources {
    char *type;
    char nom[32];
    statut t;
    char *proprio;
    char *date_d;
    char *date_f;
};

struct s_elementa{
    int i;
    Personne p;
    s_elementa *previous;
    s_elementa *next;
};

struct s_elementl{
    int i;
    Ressource r;
    s_elementl *previous;
    s_elementl *next;
};

struct s_annuaire {
    int size;
    Elementa head;
    Elementa tail;
};

struct s_liste {
    int size;
    Elementl head;
    Elementl tail;
};
enum statut {LIBRE=0; EMPRUNT};

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

//Fonctions sur listes de Personnes

Annuaire push_ba(Annuaire annu,int i, Elementa a){

}

Annuaire push_fa(Annuaire a,Elementa a){

}

Annuaire pop_fa(Annuaire ls){

}

Annuaire pop_ba(Annuaire ls){

}
Annuaire insert_at(int i,Personne pers,Annuaire annu){
    assert(i<lsannu->size)&&(i>=0);
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


