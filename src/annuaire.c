#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <crypt.h>
#include <unistd.h>
#include <string.h>
#include "../include/ressources.h"
#include "../include/chiffrement.h"
#include "../include/personne.h"
#include "../include/annuaire.h"
struct s_annuaire {
    int size;
    Elementa head;
    Elementa tail;
};

Annuaire new_annu(){
    Annuaire annu =(Annuaire) malloc(sizeof(struct s_annuaire));
    if(annu== NULL){
        fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
        exit(EXIT_FAILURE);
    }
    annu->size = 0;
	return annu;
}//fonctionne
/*----------------------------------------------------------------*/

Bool is_empty_annu(Annuaire annu){
	if(annu->size== 0)
		return true;

	return false;
}//fonctionne

/*----------------------------------------------------------------*/

int annuaire_size(Annuaire annu){
	if(is_empty_annu(annu))
		return 0;

	return annu->size;
}//fonctionne

/*----------------------------------------------------------------*/

void print_annu(Annuaire annu){
    if(is_empty_annu(annu)){
        printf("Rien a afficher, la Liste est vide.\n");
		return;
	}
	Elementa temp = annu->head;
	while(temp != NULL){
        affich_pers(temp->p);
		temp = temp->next;
	}
	printf("\n");
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
         if(strcmp(getID(pers),getID(current_a->p))==0){
             return i;
         }
         current_a=current_a->next;
     }
}//fonctionne-indice d'une personne ds l'Annuaire
/*----------------------------------------------------------------*/
int pers_existing(Annuaire annu, Personne p){
    Elementa current_a=annu->head;
    int j=annu->size;
    int i;
    for (i=0;i<j;i++){
        if(strcmp(getID(p),getID(current_a->p))==0){
            return 1;
         }
         if(strcmp(getName(p),getName(current_a->p))==0){
             if (strcmp(getPrenom(p),getPrenom(current_a->p))==0){
                    if(strcmp(getNaiss(p),getNaiss(current_a->p))==0){
                      return 2;
                 }
             }
         }
         if(strcmp(getMail(p),getMail(current_a->p))==0){
             return 3;
         }
         if(strcmp(getMail(p),getMail(current_a->p))==0){
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
    }else{
        int num=getNumAccount(annu->tail->p);
        i=num++;
    }
    return i;
}//permet d'initialiser le num de compte
/*----------------------------------------------------------------*/

void affichAnnuaire(Annuaire annu,FILE*f){
    if(is_empty_annu(annu)){
        printf("Rien a afficher, la Liste est vide.\n");
		return;
	}
	Elementa current_a= annu->head;
    
    fprintf(f,"N° de compte\tNom\tPrenom\t");
    fprintf(f,"Date de naissance\tIdentifiant\n\n");
	 int i;
     int j=annu->size;
	for (i=0;i<j;i++){
        fprintf(f,"%d\t%s\t%s\t",getNumAccount(current_a->p),getName(current_a->p),getPrenom(current_a->p));
        fprintf(f,"%s\t%s\n",getNaiss(current_a->p),getID(current_a->p));
        fseek(f,0,SEEK_END);
        current_a=current_a->next;
	}
	printf("\n");
}//fonctionne (affichage ds fichier pas satisfaisant)
/*----------------------------------------------------------------*/
Annuaire add_pers(Annuaire annu,Personne pers){
    int n;
    n=pers_existing(annu,pers);
    switch (n)
    {
    case 0 :
        printf("Le compte a été créé avec succès\n");
        if(annu->size==0){
            int num=createNumAccount(annu);
            setNumAccount(pers,num);
            affich_pers(pers);
            annu= insert_at(0,pers,annu);
        }else{
            int i=annu->size-1;
            int num=createNumAccount(annu);
            setNumAccount(pers,num);
            affich_pers(pers);
            annu= insert_at(i,pers,annu);
        }
        return annu;
    case 1:
        printf("Identifiant déjà utilisé.Veuillez en changer\n");
        modif_id(pers);
        add_pers(annu,pers);
    case 2:
        printf("Cet utilisateur existe déjà");
        return annu;
    case 3:
        printf("Cette adresse mail est déjà liée à un compte. Veuillez en choisir une autre\n");
        modif_mail(pers);
        add_pers(annu,pers);
    case 4:
        printf("Ce numéro de téléphone est déjà lié à un compte. Veuillez en utiliser un autre\n");
        modif_tel(pers);
        add_pers(annu,pers);
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
        printf("Ce compte n'existe pas ds l'annuaire il ne peut donc pas en être supprimer\n");
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
         if(strcmp(id,getID(current_a->p))==0){
            pers=current_a->p;
         }
         current_a=current_a->next;
     }
     return pers;
}//fonctionne-permet de rechercher une personne ds un Annuaire à partir de son id 
/*----------------------------------------------------------------*/
Annuaire modifAnnuaireAdmin(Annuaire annu,Personne p){
     int j=annu->size;
     int i;
     Elementa current_a=annu->head;
     for (i=0;i<j;i++){
         if(strcmp(getID(p),getID(current_a->p))==0){
            modif_pers(current_a->p);
            int n=pers_existing (annu,current_a->p);
            switch (n){
                case 0:
                    printf("Modification effectuée avec succès\n");
                    affich_pers(current_a->p);
                    return annu;
                case 1:
                    printf("Identifiant déjà utilisé.Veuillez en changer\n");
                    modif_pers(current_a->p);
                    break;
                case 2:
                    printf("Cet utilisateur existe déjà\n");
                    affich_pers(current_a->p);
                    modif_pers(current_a->p);
                    //return annu;
                case 3:
                    printf("Cette adresse mail est déjà liée à un compte. Veuillez en choisir une autre\n");
                    modif_pers(current_a->p);
                    break;
                case 4:
                    printf("Ce numéro de téléphone est déjà lié à un compte. Veuillez en utiliser un autre\n");
                    modif_pers(current_a->p);
                    break;
                default:
                        break;
                }
            }
         current_a=current_a->next;
     }

}//à peaufiner
/*----------------------------------------------------------------*/
Annuaire modifAnnuaireUser(Annuaire annu,Personne p){
     int j=annu->size;
     int i;
     Elementa current_a=annu->head;
     for (i=0;i<j;i++){
         if(strcmp(getID(p),getID(current_a->p))==0){
            modif_pers(current_a->p);
            int n=pers_existing (annu,current_a->p);
            switch (n){
                case 0:
                    printf("Modification effectuée avec succès\n");
                    affich_pers(current_a->p);
                    return annu;
                case 1:
                    printf("Identifiant déjà utilisé.Veuillez en changer\n");
                    modif_pers(current_a->p);
                    break;
                case 2:
                    printf("Cet utilisateur existe déjà\n");
                    affich_pers(current_a->p);
                    modif_pers(current_a->p);
                    //return annu;
                case 3:
                    printf("Cette adresse mail est déjà liée à un compte. Veuillez en choisir une autre\n");
                    modif_pers(current_a->p);
                    break;
                case 4:
                    printf("Ce numéro de téléphone est déjà lié à un compte. Veuillez en utiliser un autre\n");
                    modif_pers(current_a->p);
                    break;
                default:
                        break;
                }
            }
         current_a=current_a->next;
     }

}//à peaufiner
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
        printf("\nERROR--Vous allez être redirigé\n");
        createAccount(annu,f,g);
    }
}//fonctionne