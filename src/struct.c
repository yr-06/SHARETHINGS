#include <stdio.h>
#include <assert.h>
#include <crypt.h>
#include "../include/struct.h"

/*CC c Ali, G enfin compris ce que voulait dire Clement et Remi en parlant de type compte commun aux 2 menus: c le type Personne en faites. A chaque personne correspond des informations permettant de ce connecter et donc un compte. Donc en faite c plus simple comme ça c juste que j'avais pas compris quand tu me l'avais expliquée.
Donc en effet y a pas besoin de creer de type à part pour les comptes administrateurs et utilisateurs. On gère juste les Personnes c plus simples. Et en plus c ce que demande Philippe ds le sujet, il veut absolument qu'on ait au moins un type Personne et un type Ressource. En vrai pour le moment ça change pas grand chose, c'est juste au niveau de main.c qu'il faudra modifier mais ça je m'en occupe à la fin, c'est pas le plus urgent. Pour le moment il faut absolument qu'on se mette d'accord sur les structures qu'on utilise parce que c'est la base du projet et n peut pas travailler avec des tructures différentes toi et moi ou on cours à la cata !!! Ce que g fait c que j'ai include mon struct.h ds ton ressource.c, dc il faudrait modifier tes fonctions par rapport à ce qui se trouve ds struct.c et struct.h. C plus simple car on a juste à se référer au cours de Philippe par la suite et ça ns simplifie la tâche pour les fonctions de gestion de compte (dc de Personne) et de Ressources. Je t'ai mis à disposition des explications sur Insta si tu es perdue, c l'explication de ce qu'on avait prévue au départ avec l'aide de Clement. Y a des fonctions qui faut encore que je complète mais grossomodo tu trouves ça ds le cours de Philippe.Tu m'appelles si tu as des questions ou si tu t'en sors pas ;)Bisous (je v m'entraîner dc je serais de nv sur le projet vers 15h~16 certainement)*/

struct s_pers {
    int i;//numéro de compte (correspondra aussi à son indice dans Annuaire)
    char nom[32];//nom de la personne
    char prenom[32];//prenom de la personne
    char *id;//identifiant de son compte
    char *pwd;//mot de passe lié au compte
    char mail[64];//mail de la personne
	char tel[15];//numero de telephone de la personne
    Liste emprunt;//Liste de Ressources empruntées actuellement par la personne
    //Liste possession;--> liste des ressources dont la personne est proprio --> necessaire?
};

struct s_ressource {
    char *type;//type de ressouces: livre, bouteilles,CD,magazines,etc...
    char nom[32];//nom de la ressource
    statut t;//enum définissant disponibilité de la ressource--> sorte de booléen
    char *nom_proprio;// nom du proprio de la ressource-->permet de comparer avec le nom d'une Personne si besoin
    char *prenom_proprio;//prenom du proprio  de la ressource-->permet de comparer avec le prénom d'une Personne si besoin
    char *date_d;//date de debut du pret 
    char *date_f;//date de fin du pret
    /*si ressource dispo laisser dernière date de pret, ne les modifier que lorsque la ressource est pretée à nouveau */
};

struct s_elementa{
    int i;
    Personne p;
    s_elementa *previous;
    s_elementa *next;
};//element d'un Annuaire

struct s_elementl{
    int i;
    Ressource r;
    s_elementl *previous;
    s_elementl *next;
};//element d'une Liste

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
typedef enum en_statut {LIBRE=0; EMPRUNT} statut;

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

//Fonctions sur listes de Personnes= type Annuaire

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


