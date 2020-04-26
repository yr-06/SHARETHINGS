#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <crypt.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "../include/personne.h"
#include "../include/ressources.h"
#include "../include/chiffrement.h"
#include "../include/annuaire.h"
#include "../include/parson.h"

#ifndef CLEAR_STDIN
    #define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#endif

struct s_annuaire {
    int size;
    Elementa head;
    Elementa tail;
};


Annuaire new_annu(void){
    Annuaire annu=(Annuaire)malloc(sizeof(struct s_annuaire));
    if(annu==NULL){
        fprintf(stderr,"Erreur : probleme allocation dynamique.\n");
        exit(EXIT_FAILURE);
    }
    annu->size=0;
    return annu;
}
/*----------------------------------------------------------------*/

Bool is_empty_annu(Annuaire annu){
	if(annu->size== 0){
        return true;
    }
    return false;
}//fonctionne

/*----------------------------------------------------------------*/

int annuaire_size(Annuaire annu){
	if(is_empty_annu(annu))
		return 0;

	return annu->size;
}//fonctionne

/*----------------------------------------------------------------*/

void print_annu(Annuaire annu,FILE*f){
    if(is_empty_annu(annu)){
        printf("Rien a afficher, la Liste est vide.\n");
		return;
	}
	Elementa temp = annu->head;
    int j=annu->size;
    int i;
    for (i=0;i<j;i++){
        fseek(f,0,SEEK_END);
        print_pers_JSON(temp->p,f);
		temp = temp->next;
	}
	return;
}//fonctionne->utile lors des tests de fonctions

/*----------------------------------------------------------------*/

Annuaire push_ba(Annuaire annu,Personne p){
	Elementa element;

	element = malloc(sizeof(struct s_elementa));

	if(element == NULL){
        fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}

	element->p =initPers();
	element->p= p;
	element->next = NULL;
	element->previous = NULL;

	if(is_empty_annu(annu)){
		annu->head = element;
		annu->tail = element;
	}
	else{
		annu->tail->next = element;
		element->previous = annu->tail;
		annu->tail = element;
	}

	annu->size++;

	return annu;
}//fonctionne

/*----------------------------------------------------------------*/

Annuaire push_fa(Annuaire annu,Personne p){
	Elementa element;

	element = malloc(sizeof(struct s_elementa));

	if(element == NULL)
	{
		fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}

    element->p =initPers();
	element->p= p;
	element->next = NULL;
	element->previous= NULL;

	if(is_empty_annu(annu)){
		annu->head= element;
		annu->tail= element;
	}
	else{
		annu->head->previous=element;
		element->next = annu->head;
		annu->head= element;
	}

	annu->size++;

	return annu;
}//fonctionne

/*----------------------------------------------------------------*/

Annuaire pop_ba(Annuaire annu){
	if(is_empty_annu(annu)){
		printf("Rien a supprimer, l'Annuaire est deja vide.\n");
		return new_annu();
	}

	if(annu->head == annu->tail){
		free(annu);
		annu=new_annu();
        return annu;
	}

	Elementa temp = annu->tail;

	annu->tail=annu->tail->previous;
	annu->tail->next = NULL;
	temp->next = NULL;
	temp->previous= NULL;

	free(temp->p);
    free(temp);
	temp = NULL;

    annu->size--;

	return annu;
}//fonctionne

/*----------------------------------------------------------------*/

Annuaire pop_fa(Annuaire annu){
	if(is_empty_annu(annu)){
		printf("Rien a supprimer, l'Annuaire est deja vide.\n");
		return new_annu();
	}

	if(annu->head == annu->tail){
		free(annu);
		annu= new_annu();
        return annu;
	}

	Elementa temp = annu->head;

	annu->head=annu->head->next;
	annu->head->previous = NULL;
	temp->next = NULL;
	temp->previous = NULL;
    
    free(temp->p);
	free(temp);
	temp = NULL;

	annu->size--;

	return annu;
}//fonctionne

/*----------------------------------------------------------------*/

Annuaire clear_annu(Annuaire annu){
	while(!is_empty_annu(annu))
		annu= pop_ba(annu);

	return new_annu();
}//fonctionne
/*----------------------------------------------------------------*/
Annuaire insert_at(int i,Personne p,Annuaire annu){
    assert((i<=annu->size)&&(i>=0));
    int t=(annu->size)-1;
    if(i==0){
        return (push_fa(annu,p));
    }
   if(i==t){
       return (push_ba(annu,p));
    }else{
        Elementa a= (Elementa)malloc(sizeof(struct s_elementa));
        a->p=initPers();
        a->p=p;
        int j=0;
        Elementa current_a=annu->head;
        for(j=0;j<i;j++){
            current_a=current_a->next;
        }
        current_a->previous->next=a;
        a->previous=current_a->previous;
        current_a->previous=a;
        a->next=current_a;
        annu->size++;
        return annu;
    }
}//fonctionne-permet d'ajouter un Elementa à un indice précis de l'Annuaire

/*----------------------------------------------------------------*/
Annuaire remove_at(int i,Annuaire annu){
    assert((i<annu->size)&&(i>=0));
    int t=(annu->size)-1;
    if(i==0){
        return (pop_fa(annu));
    }
    if(i==t){
        return (pop_ba(annu));
    }else{
         int j=0;
            Elementa current_a=annu->head;
            for(j=0;j<i;j++){
                current_a=current_a->next;
            }
            current_a->previous->next=current_a->next;
            current_a->next->previous=current_a->previous;
            free(current_a->p);
            free(current_a);
            annu->size--;
            return annu;
        
    }
}//fonctionne-permet d'enlever un Elementa à un indice précis de l'Annuaire
/*----------------------------------------------------------------*/

//Fonctions sur listes de Personnes= type Annuaire à tester
int getIndicePersonne(Annuaire annu, Personne pers){
     int i;
     int j=annu->size;
     Elementa current_a=annu->head;
     for (i=0;i<j;i++){
         if(strcmp(getIDPers(pers),getIDPers(current_a->p))==0){
             return i;
         }
         current_a=current_a->next;
     }
}//fonctionne-indice d'une personne ds l'Annuaire
/*----------------------------------------------------------------*/
int pers_existing(Annuaire annu, Personne p){
    assert(0<annu->size);
    Elementa current_a=annu->head;
    int j=annu->size;
    int i;
    char*date_p;
    date_p=(char*)malloc(sizeof(char)*21);
    strftime(date_p,21,"%d/%m/%Y",getNaiss(p));
    for (i=0;i<j;i++){
        if(strcmp(getIDPers(p),getIDPers(current_a->p))==0){
            return 1;
         }
         if(strcmp(getName(p),getName(current_a->p))==0){
             if (strcmp(getPrenom(p),getPrenom(current_a->p))==0){
                 char*date_n;
                 date_n=(char*)malloc(sizeof(char)*21);
                 strftime(date_n,21,"%d/%m/%Y",getNaiss(current_a->p));
                    if(strcmp(date_p,date_n)==0){
                      return 2;
                 }
             }
         }
         if(strcmp(getMail(p),getMail(current_a->p))==0){
             return 3;
         }
         if(strcmp(getTel(p),getTel(current_a->p))==0){
             return 4;
         }
         current_a=current_a->next;
    }
    return 0;
}//fonctionne-permet de vérifier si les données de la personne P ne sont pas déjà présentes

/*----------------------------------------------------------------*/
int createNumAccount(Annuaire annu){
    assert(annu->size>=0);
    int i;
    if(annu->size==0){
         i=1000;
        return i;
    }else{
        int num=getNumAccount(annu->tail->p);
        i=num+1;
        return i;
    }
}//permet d'initialiser le num de compte
/*----------------------------------------------------------------*/
void affichAnnuaire(Annuaire annu){
    if(is_empty_annu(annu)){
        printf("Rien a afficher, l'Annuaire est vide.\n");
		return;
	}
	Elementa current_a= annu->head;
    int i;
    int j=annu->size;
	for (i=0;i<j;i++){
        printf("N° de compte :%d\n", getNumAccount(p));
        printf("Nom :%s\n", getName(p));
        printf("Prenom :%s\n", getPrenom(p));
        printf("Date de naissance :%s\n",getNaiss(p));
        printf("Identifiant :%s\n", getID(p));
        printf("\n");
        current_a=current_a->next;
	}
	return;
}//fonctionne
/*----------------------------------------------------------------*/
Annuaire add_pers(Annuaire annu,FILE*f,Personne pers){

    if(annu->size==0){
        printf("Le compte a été créé avec succès\n");
        int num=createNumAccount(annu);
        setNumAccount(pers,num);
        affich_pers(pers);
        annu=push_ba(annu,pers);
        print_pers_JSON(pers,f);
        return annu;
    }
    int n;
    n=pers_existing(annu,pers);
    switch (n)
    {
    case 0 :
        printf("Le compte a été créé avec succès\n");
        int num=createNumAccount(annu);
        setNumAccount(pers,num);
        affich_pers(pers);
        annu=push_ba(annu,pers);
        print_pers_JSON(pers,f);
        return annu;
    case 1:
        printf("Identifiant déjà utilisé.Veuillez en changer\n");
        CLEAR_STDIN
        modif_id(pers);
        add_pers(annu,f,pers);
    case 2:
        printf("Cet utilisateur existe déjà");
        return annu;
    case 3:
        printf("Cette adresse mail est déjà liée à un compte. Veuillez en choisir une autre\n");
        CLEAR_STDIN
        modif_mail(pers);
        add_pers(annu,f,pers);
    case 4:
        printf("Ce numéro de téléphone est déjà lié à un compte. Veuillez en utiliser un autre\n");
        CLEAR_STDIN
        modif_tel(pers);
        add_pers(annu,f,pers);
    default:
        break;
    }
}//fonctionne-permet d'ajouter une Personne n'existant pas encore à l'Annuaire
/*----------------------------------------------------------------*/
Annuaire remove_pers(Annuaire annu, Personne pers){
    int n;
    n=pers_existing(annu,pers);
    if(n!=0){
    int i;
    i=getIndicePersonne(annu,pers);
    annu=remove_at(i,annu);
    return annu;
    }else{
        printf("Ce compte n'existe pas dans l'annuaire il ne peut donc pas être supprimé\n");
        return annu;
    }
    
}//fonctionne-permet de supprimer une Personne de l'Annuaire
/*----------------------------------------------------------------*/
Personne search_pers(Annuaire annu, char * id){
    Personne pers=initPers();
     int i;
     int j=annu->size;
     Elementa current_a=annu->head;
     for (i=0;i<j;i++){
         if(strcmp(id,getIDPers(current_a->p))==0){
            pers=current_a->p;
         }
         current_a=current_a->next;
     }
     return pers;
}//fonctionne-permet de rechercher une personne ds un Annuaire à partir de son id 
/*----------------------------------------------------------------*/
Annuaire modifAnnuaireAdmin(int i,Annuaire annu,Personne temp, FILE*f){
    assert(0<annu->size);
    
    modif_persAdmin(temp,f);
    int n=pers_existing(annu,temp);
    switch (n){
        case 0:
            char *id;
            char *tkb;
            id=(char*)malloc(sizeof(char)*33);
            tkb=(char*)malloc(sizeof(char)*33);
            
            id=getIDPers(temp);
            tkb=getTakenBy(temp->emprunt->head->r);
            
            if(getNbPret(temp)>0 && (strcmp(id,tkb)!=0){
                int i ;
                Elementl current_l=temp->emprunt->head;
                for (i=0;i<getNbPret(temp);i++){
                     char *c;
                     c=(char*)malloc(sizeof(char)*33);
                     c=getTakenBy(current_l->r->takenBy);
                    if(strcmp(id,c)!=0){
                       free(current_l->r->takenBy)
                       (current_l->r->takenBy)=(char*)malloc(sizeof(char)*33);
                       setTakenBy(current_l->r->takenBy,id);
                       free(c);
                       CLEAR_STDIN
                    }
                    current_l=current_l->next;
                }
            }
            
            printf("Modification effectuée avec succès\n");
            annu=insert_at(i,temp,annu);
            return annu;
        case 1:
            printf("Identifiant déjà utilisé.Veuillez en changer\n");
            modif_annuaireAdmin(i,annu,temp,f);
            break;
        case 2:
            printf("Cet utilisateur existe déjà\n");
            printf("Veuillez vous recréer un compte\n");
            annu=createAccount(f);
            return annu;
        case 3:
            printf("Cette adresse mail est déjà liée à un compte. Veuillez en choisir une autre\n");
            modif_annuaireAdmin(i,annu,temp,f);
            break;
        case 4:
            printf("Ce numéro de téléphone est déjà lié à un compte. Veuillez en utiliser un autre\n");
            modif_annuaireAdmin(i,annu,temp,f);
            break;
        default:
            break;
        }
}//à tester
/*----------------------------------------------------------------*/
Annuaire modifAnnuaireUser(int i,Annuaire annu,Personne temp){
    assert(0<annu->size);
    
    modif_persUser(temp);
    int n=pers_existing(annu,temp);
    switch (n){
        case 0:
            printf("Modification effectuée avec succès\n");
            annu=insert_at(i,temp,annu);
            return annu;

        case 3:
            printf("Cette adresse mail est déjà liée à un compte. Veuillez en choisir une autre\n");
            modifAnnuaireUser(i,annu,temp);
            break;
        case 4:
            printf("Ce numéro de téléphone est déjà lié à un compte. Veuillez en utiliser un autre\n");
            modifAnnuaireUser(i,annu,temp);
            break;
        default:
            break;
        }
}//à tester
/*----------------------------------------------------------------*/
Annuaire createAccount(Annuaire annu,FILE*f,FILE*g){
    Personne p=create_pers(f);
    affich_pers(p);
    int i;
    printf("\n\nEtes-vous satisfait des données enregistrées ?\nOUI=1\tNON=0\n");
    scanf("%d",&i);
    switch(i){
      case 0:
        CLEAR_STDIN  
        modif_persAdmin(p,f);
        printf("\nSi vous rencontrez des problèmes avec votre compte veuillez vous réfferer à un administrateur\n");
        affich_pers(p);
        annu=add_pers(annu,g,p);
        return annu;
      case 1:
        annu=add_pers(annu,g,p);
        return annu;
      default:
        printf("\nERROR\n");
        printf("Vous allez être redirigé\n");
        createAccount(annu,f,g);
    }
}//pb avec recurrence de setAutor()

/*int main(int argc, char *argv[]){
    FILE *f=fopen("../data/Mtdp_admin.txt", "r");
    FILE *g=fopen("../data/Annuaire.json","w+");
    Annuaire annu =new_annu();
    /*Personne p=create_pers(f);
    modif_persAdmin(p,f);
    affich_pers(p);
    
    annu=createAccount(annu,f,g);
    annu=createAccount(annu,f,g);
    annu=createAccount(annu,f,g);
    annu=createAccount(annu,f,g);
    
    
    
    annu=clear_annu(annu);
    free(annu);
}*/
