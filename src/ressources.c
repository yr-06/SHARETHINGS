#include <stdio.h>
#include <stlib.h>
#include <string.h>
#include <assert.h>
#include <crypt.h>
#include "../include/ressources.h"


//structures:
//Ressouce
struct s_ressource {
    char *type;//type de ressouces: livre, bouteilles,CD,magazines,etc...
    char nom[32];//nom de la ressource
    char ID[64];//= ID de la ressource
    char *takenBy;// = ID de l'utilisateur qui a pris la ressource.
    char *dropBy;// = ID de l'utilisateur qui a déposé la ressource.
    char *date_d;//date de debut du pret 
    char *date_f;//date de fin du pret
};

//Element d'une liste
struct s_elementl{
    int i;
    Ressource r;
    struct s_elementl *previous;
    struct s_elementl *next;
};

//Liste
struct s_liste {
    int size;
    Elementl head;
    Elementl tail;
};


//getters :
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

char * getTypeRessource(Ressource r){
	return(r->type);
}

char * getNom(Ressource r) {
	return(r->nom);
}
//permet de savoir par qui la ressource est empruntee
char * getRessourceDispo(Ressource r){
        if(isDispo(r) == 1){
           return "La ressource est disponible."
       }
        return getTakenBy(r);//return l'ID de celui qui l'a emprunté.
}

char * getDateDebut(Ressource r){
	return(r->date_d);
}

char * getDateFin(Ressource r){
	return(r->date_f);
}



//Liste/char * get operationsWhen(Ressource r);

//fonction qui permet de récupérer la liste des opérations sur une 
//période donnée



//setters:
void setType(Ressource r, char *type){
	strcpy(r->type, type);
}

void setNom(Ressource r , char * nom){
	strcpy(r->nom, nom);
}

void setID(Ressource r, char * ID){
	strcpy(r->ID, ID);
}

void setTakenBy(Ressource r, char * takenBy){
	strcpy(r->takenBy, takenBy);
}

void setDropBy(Ressource r, char * dropBy){
	strcpy(r->dropBy, dropBy);
}
void setDateDebut(Ressource r, char * date_d){
	strcpy(r->date_d, date_d);
}

void setDateFin(Ressource r, char * date_f){
	strcpy(r->date_f, date_f);
}

//modifyer
void modifType(Ressource r){
    char *type;
    type=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer le type de cette ressource:\n");
    scanf("%33s",type);
   // scanf("%[^\n]%*c",type); 
    setType(r,type);
    free(type);
}
void modifNom(Ressource r){
        char *name;
        name=(char*)malloc(sizeof(char)*33);
        printf("Veuillez entrer un nom pour cette ressource:\n");
        scanf("%33s",name);
        //scanf("%[^\n]%*c",name); 
        setName(r,name);
        free(name);
}
void modifDispo(Ressource r){
        int dis;
        //printf("Veuillez entrer un nom pour cette ressource:\n");
        scanf("%d",dis);
        setDispo(r,dis);
        free(dis);
}
void modifTakenBy(Ressource r){
        char *tkb;
        tkb=(char*)malloc(sizeof(char)*33);
        printf("Veuillez entrer votre identifiant :\n");
        scanf("%33s",tkb);
        setTakenBy(r,tkb);
        free(tkb);
}

//fonctions sur Ressource:
//permet d'initialiser une ressource 
Ressource initRessource(){
	Ressource r = (Ressource)malloc(sizeof(struct s_ressource));
	(r->type) = (char*)malloc(sizeof(char)*33);
	(r->takenBy) = (char*)malloc(sizeof(char)*33);
	(r->dropBy) = (char*)malloc(sizeof(char)*33);
	(r->date_d) = (char*)malloc(sizeof(char)*21);
	(r->date_f) = (char)*malloc(sizeof(char)*21);

	return r;
}//la définir ici permet d'éviter les erreurs


//permet de savoir si une ressource est disponible
int isDispo(Ressource r){
        if(strcmp(getTakenBy(r), "0") == 0) {
                return 1;
        }
        return 0;
}

int haveRessource(Personne p){
	//vérifier si une ressource appartient bien à la personne
}





//Fonctions sur Liste de Ressources:
//permet de supprimer une ressource grace à l'indice dans une liste
void removeRessource(Ressource r,Liste l){
	remove_at(getIndex(r,l), l);
}

void retirerRessource(Ressource r, Personne p){
	if(strcmp(getID(p) , getDropBy(r)) == 0 && isDispo == 1){
		removeRessource(r, getListeEmprunt(p));
	}
}

//ajoute un élément en début de liste
Liste push_bl(Liste l, Ressource){
	Elementl e = (Elementl)malloc(sizeof(struct s_element));
	e->r = r;
	e->previous = l->tail;
	e->next = NULL;
	//cas liste vide
	if(l->size == 0){
		l->head = e;
		l->tail = e;
	}
	else{
		(l->tail)->next = e;
		(l->tail) = e;
	}
	l->size++;
	return l;
}
//ajoute un élément en fin de liste
Liste push_fl(Liste l, Ressource r){
	Elementl e = (Elementl)malloc(sizeof(struct s_elementl));
	e->r = r;
	e->previous = NULL;
	e->next = l->head;
	//cas liste vide
	if(l->size == 0){
		l->head = e;
		l->tail = e;
	}
	else{
		(l->head)->previous = e;
		(l->head) = e;
	}
	l->size++;
	return l;
}

//supprime un élement en début de liste
Liste pop_fl(Liste l){
	if(l->size == 0){
		return l;
	}

	if(l->size > 1){
		l->head = (l->head)->next;
		(l->head)->previous = NULL;
	}
	else{
		l->head = NULL;
		l->tail = NULL;
	}
	l->size--;
	return l;
}

//supprime un élément en fin de liste
Liste pop_bl(Liste l){
	if(l->size == 0){
		return l;
	}
	if(l->size > 1){
		l->tail = (l->tail)->previous;
		(l->tail)->next = NULL;
	}
	else{
		l->head = NULL;
		l->tail = NULL;
	}
	l->size--;
	return l;
}

//permet d'ajouter une ressource à un indice précis dans une liste
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

//permet de supprimer une ressource dans une liste à un indice précis
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




//getters sur les listes:

//fonction qui récupère l'indice d'une ressource dans une liste de ressources.
int getIndex(Ressource r, Liste l){
	int pos = 0;
	Elementl current = l->head;
	for(int i = 0; i<(l->size);i++){
		if(r == current->r){
			pos = i;
		}
		current=current->next;
	}
	return pos;
}

//fonction qui récupère une ressource à partir d'un indice dans une liste de ressources.
Ressource getRessource(int index, Liste l){
	Elementl current = l->head;
	for(int i = 0;i<index; i++){
		current=current->next;
	}
	return current->r;

}
