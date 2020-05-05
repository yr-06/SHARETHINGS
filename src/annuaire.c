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

struct s_elementa{
    Personne p;
    struct s_elementa *previous;
    struct s_elementa *next;
};

struct s_annuaire {
    int size;
    Elementa head;
    Elementa tail;
};


Annuaire new_annu(){
    Annuaire annu=(Annuaire)malloc(sizeof(struct s_annuaire));
    if(annu==NULL){
        fprintf(stderr,"Erreur : probleme allocation dynamique.\n");
        exit(EXIT_FAILURE);
    }
    annu->size=0;
    return annu;
}//fonctionne
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

    for (i=0;i<j;i++){
        if(strcmp(getIDPers(p),getIDPers(current_a->p))==0){
            return 1;
         }
         /*if(strcmp(getName(p),getName(current_a->p))==0){
             if (strcmp(getPrenom(p),getPrenom(current_a->p))==0){
                    if(strcmp(getNaiss(p),getNaiss(current_a->p))==0){
                      return 2;
                 }
             }
         }*/
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
}//à revoir-->permet d'initialiser le num de compte
/*----------------------------------------------------------------*/
void affichAnnuaire(Annuaire annu){
    if(is_empty_annu(annu)){
        printf("Rien a afficher, l'Annuaire est vide.\n");
		return;
	}
	Elementa current_a= annu->head;
    int i;
    int j=annu->size;
    printf("*** Voici la liste des usagers ***\n");
	for (i=0;i<j;i++){
        printf("N° de compte :%d\n", getNumAccount(current_a->p));
        printf("Nom :%s\n", getName(current_a->p));
        printf("Prenom :%s\n", getPrenom(current_a->p));
        printf("Identifiant :%s\n", getIDPers(current_a->p));
        printf("\n\n");
        current_a=current_a->next;
	}
	return;
}//fonctionne
/*----------------------------------------------------------------*/
Annuaire add_pers(Annuaire annu,Personne pers){
    if(annu->size==0){
        setNumAccount(pers,createNumAccount(annu));
        printf("N° de compte=%d",getNumAccount(pers));
        setIDPers(pers,createIDPers(pers));
        annu=push_ba(annu,pers);
        printf("Le compte a été créé avec succès\n");
        affich_pers(pers);
        print_pers_JSON(pers);
        return annu;
    }
    int n;
    n=pers_existing(annu,pers);
    switch (n)
    {
    case 0 :
        setNumAccount(pers,createNumAccount(annu));
        printf("N° de compte=%d",getNumAccount(pers));
        setIDPers(pers,createIDPers(pers));
        annu=push_ba(annu,pers);
        printf("Le compte a été créé avec succès\n");
        affich_pers(pers);
        print_pers_JSON(pers);
        return annu;
    case 1:
        printf("ERROR-Identifiant déjà utilisé.Veuillez en changer\n");
        CLEAR_STDIN
        exit(EXIT_FAILURE);
        
    /*case 2:
        printf("Cet utilisateur existe déjà");
        return annu;*/
    case 3:
        printf("Cette adresse mail est déjà liée à un compte. Veuillez en choisir une autre\n");
        CLEAR_STDIN
        modif_mail(pers);
        annu=add_pers(annu,pers);
    case 4:
        printf("Ce numéro de téléphone est déjà lié à un compte. Veuillez en utiliser un autre\n");
        CLEAR_STDIN
        modif_tel(pers);
        annu=add_pers(annu,pers);
    default:
        break;
    }
}//fonctionne-permet d'ajouter une Personne n'existant pas encore à l'Annuaire
/*----------------------------------------------------------------*/
Annuaire remove_pers(Annuaire annu, Personne pers){
    int n;
    n=pers_existing(annu,pers);
    if(n==1){
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
Personne search_pers(Annuaire annu, char * c){
    Personne pers=initPers();
     int i;
     int j=annu->size;
     Elementa current_a=annu->head;
     for (i=0;i<j;i++){
         if(strcmp(c,getIDPers(current_a->p))==0){
            pers=current_a->p;
            return pers;
         } if(strcmp(c,getMail(current_a->p))==0){
            pers=current_a->p;
            return pers;
         }
         current_a=current_a->next;
     }
}//fonctionne-permet de rechercher une personne ds un Annuaire à partir de son id ou de son adresse mail
/*----------------------------------------------------------------*/
Annuaire modifAnnuaireAdmin(int i,Annuaire annu,Personne temp){
    assert(0<annu->size);
    
    modif_persAdmin(temp);
    int n=pers_existing(annu,temp);
    switch (n){
        case 0:
            /*char *id;
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
            }*/
            
            printf("Modification effectuée avec succès\n");
            annu=insert_at(i,temp,annu);
            return annu;
        case 1:
            printf("Identifiant déjà utilisé.Veuillez en changer\n");
            annu=modifAnnuaireAdmin(i,annu,temp);
            break;
        case 2:
            printf("Cet utilisateur existe déjà\n");
            printf("Veuillez vous recréer un compte\n");
            annu=createAccount(annu);
            return annu;
        case 3:
            printf("Cette adresse mail est déjà liée à un compte. Veuillez en choisir une autre\n");
            annu=modifAnnuaireAdmin(i,annu,temp);
            break;
        case 4:
            printf("Ce numéro de téléphone est déjà lié à un compte. Veuillez en utiliser un autre\n");
            annu=modifAnnuaireAdmin(i,annu,temp);
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
Annuaire createAccount(Annuaire annu){
    Personne p=create_pers();
    affich_pers(p);
    printf("\nVotre numéro de compte et votre Identifiant vous seront affecés plus tard\n");
    int i;
    printf("\n\nEtes-vous satisfait des données enregistrées ?\nOUI=1\tNON=0\n");
    scanf("%d",&i);
    switch(i){
      case 0:
        CLEAR_STDIN  
        modif_persAdmin(p);
        printf("\nSi vous rencontrez des problèmes avec votre compte veuillez vous réfferer à un administrateur\n");
        annu=add_pers(annu,p);
        return annu;
      case 1:
        annu=add_pers(annu,p);
        return annu;
      default:
        printf("\nERROR--Vous allez être redirigé\n");
        annu=createAccount(annu);
    }
}//pb avec recurrence de setAutor()


Annuaire LoadAnnu(Annuaire annu){
    char line[33];
    FILE*f = fopen("../data/Personne/Annuaire.dat","r");
   
    if(f!= NULL){
        while (!feof(f) && fgets(line,33,f) != NULL){
            puts(line);
           Personne p=LoadPersonne(line);
           affich_pers(p);
           //annu=push_ba(annu,p);
        }
    }else{
        fprintf(stderr, "Erreur :Impossible d'ouvrir le fichier.\n");
		exit(EXIT_FAILURE);
    }
    
    return annu;
}//à revoir


int main(int argc, char *argv[]){
    Annuaire annu=new_annu();
    annu=LoadAnnu(annu);
    affichAnnuaire(annu);
    annu=clear_annu(annu);
    free(annu);

    


    
    /*Annuaire annu =new_annu();
    
    annu=createAccount(annu);
    annu=createAccount(annu);
    annu=createAccount(annu);
    
    char*m;
    m=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer l'identifiant du compte que vous souhaitez modifier:\n");
    fgets(m,33,stdin);
        
    Personne pat=initPers();
    pat=search_pers(annu,m);
    affich_pers(pat);
        
    int i=getIndicePersonne(annu,pat);
    printf("i=%d",i);
    Personne temp=initPers();
    temp=pat;
        
    annu=remove_at(i,annu);
    annu=modifAnnuaireAdmin(i,annu,temp);
   
    
    
    annu=clear_annu(annu);
    free(annu);*/

}
