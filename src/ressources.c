#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../include/ressources.h"
#ifndef CLEAR_STDIN
    #define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#endif

typedef int Bool ;  //définition du type booléen,

#define false  0 /* affectation des valeurs conventionnelles*/

#define true  1


//structures:
//Ressource
struct s_ressource {
    char *type;//type de ressouces: livre, bouteilles,CD,magazines,etc...
    char nom[32];//nom de la ressource
    char *ID;//= ID de la ressource
    char *takenBy;// = ID de l'utilisateur qui a pris la ressource.
    char *dropBy;// = ID de l'utilisateur qui a déposé la ressource.
    char *date_d;//date de debut du pret 
    char *date_f;//date de fin du pret
};

//Element d'une liste
struct s_elementl{
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
char * getID_r(Ressource r){
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
           return "La ressource est disponible.";
       }
        return getTakenBy(r);//return l'ID de celui qui l'a emprunté.
}

//permet de savoir si une ressoure nous appartient ou pas 
char * getRessourceHave(Personne p , Ressource r){
  if(haveRessource(p, r)== 1){
    return "Cette ressource vous appartient. Vous pouvez la modifier.";
  }
  return "Cette ressource ne vous appartient pas. Vous ne pouvez pas la modifier";
}


char * getDateDeb(Ressource r){
	return(r->date_d);
}

char * getDateFin(Ressource r){
	return(r->date_f);
}


//setters:
void setType(Ressource r, char *type){
	strcpy(r->type, type);
}

void setNom(Ressource r , char * nom){
	strcpy(r->nom, nom);
}

void setID_r(Ressource r, char * ID){
	strcpy(r->ID, ID);
}

void setTakenBy(Ressource r, char * takenBy){
	strcpy(r->takenBy, takenBy);
}

void setDropBy(Ressource r, char * dropBy){
	strcpy(r->dropBy, dropBy);
}
void setDateDeb(Ressource r, char * date_d){
	strcpy(r->date_d, date_d);
}

void setDateFin(Ressource r, char * date_f){
	strcpy(r->date_f, date_f);
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
	r->ID = generateID(ressources);
	push_bl(ressources, r);
	return r;
}//la définir ici permet d'éviter les erreurs

//fonctions sur ressource:
//permet de savoir si une ressource est disponible avec un int
int isDispo(Ressource r){
        if(strcmp(getTakenBy(r), "") == 0) {
                return 1;
        }
        return 0;
}
//permet de savoir si une ressource nous appartient avec un int
int haveRessource(Personne p, Ressource r){
  if(strcmp(getID(p), getDropBy(r)) == 0){
    return 1;
  }
  return 0;
}

//fonction qui génère un ID pour une  ressource en char*
char * generateID(Liste ressources){
  srand(time(NULL)); // initialisation de rand
  int i; 
  char* newabc = (char*)calloc(8, sizeof(char));
  for (i = 0; i < 8; ++i) {
    newabc[i] = 'a' + (rand() % 26);
  }

 if(getRessource_ID(newabc,ressources)!= NULL){
    return generateID(ressources);
  }
  return newabc;
}

//permet de supprimer une ressource grace à l'indice dans une liste
void removeRessource(Ressource r,Liste l){
	remove_at(getIndex(r,l), l);
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
	if(index>=list_size(l) || index <0){
    		return NULL;
        }
	for(int i = 0;i<index; i++){
		current=current->next;
	}
	return current->r;
}


//fonction qui permet de récuperer une ressource avec un ID
Ressource getRessource_ID (char * ID, Liste l){
  Elementl current = l->head;
  for(int i =0; i<list_size(l); i++){
    if(strcmp(getID_r(current->r), ID) == 0){
      return current->r;
    } 
    current = current ->next;
  }
  return NULL;
}

//permet de pouvoir sélectionner une ressource qui nous appartient
void gererDropRessource(Personne p, Liste l){
  color("34;1");
  int choix;
  Elementl current = l->head;
  printf("Selectionnez un des numéros suivants. \n");
  printf("(-1) Revenir en arrière.\n");
  for(int i =0; i<list_size(l); i++){
    if(haveRessource(p,current->r) == 1){
      printf("( %d) %s\n",i,getNom(current->r));
    } 
    current = current ->next;
  }
  scanf("%d", &choix);
  if(choix == -1){
    welcomeUser(p, l);
    return;
  }
  Ressource r = getRessource(choix, l);
  if(r == NULL || haveRessource(p, r) == 0){
    printf("Numéro incorrect. Réessayez!");
    gererDropRessource(p, l);
    return;
  }
  modifRessource(p, r,l);
}

//fonction pour emprunter une ressource
void takeRessource(Personne p, Liste l){
  color("34;1");
  int choix;
  Elementl current = l->head;
  printf("Selectionnez un des numéros suivants. \n");
  printf("(-1) Revenir en arrière.\n");
  for(int i =0; i<list_size(l); i++){
    if(isDispo(current-> r) == 1){
      printf("( %d) %s\n",i,getNom(current->r));
    } 
    current = current ->next;
  }
  scanf("%d", &choix);
  if(choix == -1){
    welcomeUser(p, l);
    return;
  }
  Ressource r = getRessource(choix, l);
  if(r == NULL || isDispo(r) == 0){
    printf("Numéro incorrect. Réessayez!");
    takeRessource(p, l);
    return;
  }
  printf("Vous venez d'emprunter le livre %s pour 2 semaines. \n", getNom(r));
  setTakenBy(r, getID(p));
  welcomeUser(p, l);
}


//fonctions sur les listes : 
//fonction initialisation liste
Liste new_list(){
  Liste l =(Liste)malloc(sizeof(struct s_liste));
  if(l== NULL){
    fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
    exit(EXIT_FAILURE);
  }
  l->size= 0;
	return l;
}

//permet de savoir si une liste est vide
Bool is_empty_list(Liste l){
	if(l->size== 0)
		return true;

	return false;
}

//permet de savoir la taille d'une liste
int list_size(Liste l){
	if(is_empty_list(l))
		return 0;

	return l->size;
}

//affiche les infos liées à une ressource
void affich_ress(Ressource r){
    printf("\nVoici le récapitulatif des données liées à cette ressource:\n");
    printf("Type :%s\n", getType(r));
    printf("Nom :%s\n", getNom(r));
    printf("ID:%s\n", getID_r(r));
    printf("Propriétaire :%s\n",getDropBy(r));
		//printf("Créée le:%s\n",getDateCrea(r));
    printf("\n");
   
    if(isDispo(r)==0){
        printf("Statut : Emprunté\n");
        printf("Emprunté par :%s\n", getTakenBy(r));
        printf("Date de début du pret:%s\n", getDateDeb(r));
        printf("Date de fin du pret:%s\n", getDateFin(r));
    }else{
         printf("Statut : Disponible\n\n");
    }
}

//permet d'afficher une liste
void print_list(Liste l){
  if(is_empty_list(l)){
      printf("Rien a afficher, la Liste est vide.\n");
	  return;
	}
	Elementl temp = l->head;
	while(temp != NULL){
      affich_ress(temp->r);
	  temp = temp->next;
	}
	printf("\n");
}

//ajouter un élèment en bout de liste: 
Liste push_bl(Liste l,Ressource r){
	Elementl element = malloc(sizeof(struct s_elementl));
  if(element == NULL){
      fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
	  exit(EXIT_FAILURE);
	}
	
	element->r=r;
	element->next=NULL;
	element->previous = NULL;

	if(is_empty_list(l)){
		l->head= element;
		l->tail= element;
	}
	else{
		l->tail->next = element;
		element->previous = l->tail;
		l->tail= element;
	}
  l->size++;
  return l;
}

//ajoute un élèment en début de liste
Liste push_fl(Liste l,Ressource r){
	Elementl element = malloc(sizeof(struct s_elementl));
	if(element == NULL){
		fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}

	element->r =r;
	element->next = NULL;
	element->previous = NULL;

	if(is_empty_list(l)){   
        l->head = element;
		l->tail= element;
	}
	else{
		l->head->previous = element;
		element->next = l->head;
		l->head=element;
	}
  l->size++;
	return l;
}

//supprime un élèment en bout de liste
Liste pop_bl(Liste l){
	if(is_empty_list(l)){
		printf("Rien a supprimer, la Liste est deja vide.\n");
		return new_list();
	}

	if(l->head == l->tail){
		free(l);
        l=new_list();
        return l;
	}

	Elementl temp = l->tail;

	l->tail=l->tail->previous;
	l->tail->next = NULL;
	temp->next = NULL;
	temp->previous= NULL;
    
    free(temp->r);
    free(temp);
	temp = NULL;

	l->size--;

	return l;
}

//supprimer un élèment en début de liste
Liste pop_fl(Liste l){
	if(is_empty_list(l)){
		printf("Rien a supprimer, la Liste est deja vide.\n");
		return new_list();
	}

	if(l->head == l->tail){
		free(l);
		l =new_list();
		return l;
	}

	Elementl temp = l->head;
	l->head = l->head->next;
	l->head->previous = NULL;
	temp->next = NULL;
	temp->previous= NULL;

	free(temp);
	temp = NULL;

	l->size--;

	return l;
}

//permet de vider une liste
Liste clear_list(Liste l){
	while(!is_empty_list(l))
		l = pop_bl(l);

	return new_list();
}

//insère une ressource à un indice précis de la liste
Liste insert_at_l(int i,Ressource r, Liste ls){
    assert((i<=ls->size)&&(i>=0));
    int t=(ls->size)-1;
    if(i==0){
        return (push_fl(ls,r));
    }
   if(i==t){
       return (push_bl(ls,r));
    }else{
        Elementl l=(Elementl)malloc(sizeof(struct s_elementl));
        l->r=initRessource(ls);
        l->r=r;
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

//supprime à un indice précis de la liste
Liste remove_at_l(int i,Liste ls){
    assert((i<ls->size)&&(i>=0));
    int t=(ls->size)-1;
    if(i==0){
        return (pop_fl(ls));
    }
    if(i==t){
        return (pop_bl(ls));
    }else{
         int j=0;
            Elementl current_l=ls->head;
            for(j=0;j<i;j++){
                current_l=current_l->next;
            }
            current_l->previous->next=current_l->next;
            current_l->next->previous=current_l->previous;
            free(current_l);
            ls->size--;
            return ls;
    }
}

//permet de savoir si une ressource existe
int ress_existing(Liste ls, Ressource r){
    Elementl current_l=ls->head;
    int j=ls->size;
    int i;
    for (i=0;i<j;i++){
        if(strcmp(getID(r),getID(current_l->r))==0){
            return 1;
         }
         if(strcmp(getType(r),getType(current_l->r))==0){
             if (strcmp(getNom(r),getNom(current_l->r))==0){
                    if(strcmp(getDropBy(r),getDropBy(current_l->r))==0){
                      return 2;
                 }
             }
         }
        
         current_l=current_l->next;
    }
    return 0;
}

//permet de pouvoir sélectionner une ressource qui nous appartient
void gererDropRessource(Personne p, Liste l){
  int choix;
  Elementl current = l->head;
  for(int i =0; i<list_size(l); i++){
    if(strcmp(getID_r(current->r), getID(p)) == 0){
      printf("(%d) %s",i,getNom(current->r));
    } 
    current = current ->next;
  }
  scanf("%d", &choix);
  Ressource r = getRessource(choix, l);
  if(r == NULL || strcmp(getDropBy(r), getID(p)) == 1){
    printf("Numéro incorrect. Réessayez!");
    gererDropRessource(p, l);
    return;
  }
  modifRessource(p, r);
}
