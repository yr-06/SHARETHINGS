#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <crypt.h>
#include <unistd.h>
#include <string.h>
#include "../include/personne.h"
#include "../include/chiffrement.h"
#include "../include/annuaire.h"
#include "../include/ressources.h"
#include "../include/parson.h"
#include "../include/affichageAdmin.h"
#ifndef CLEAR_STDIN
    #define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#endif
#ifndef COLOR
    #define color(param) printf("\033[%sm",param)
#endif

/* Paramètre  Couleur
30 Noir |31 Rouge | 32 Vert | 33 Jaune | 34 Bleu | 35 Magenta | 36 Cyan | 37 Blanc
 
"1" active la haute intensité des caractères.
*/

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
        color("31;01");
		printf("Rien a supprimer, l'Annuaire est deja vide.\n");
        color("37");
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
}//fonctionne--->good color

/*----------------------------------------------------------------*/

Annuaire pop_fa(Annuaire annu){
	if(is_empty_annu(annu)){
        color("31;01");
		printf("Rien a supprimer, l'Annuaire est deja vide.\n");
        color("37");
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
}//fonctionne--->good color

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
    }if(i==t||i==annu->size){
       
       return (push_ba(annu,p));
    }else{
       
        Elementa a= (Elementa)malloc(sizeof(struct s_elementa));
        
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
	return -1;
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
}//fonctionne-permet de vérifier si les données de la personne P ne sont pas déjà présentes dans l'Annuaire

/*----------------------------------------------------------------*/
int createNumAccount(Annuaire annu){
    assert(annu->size>=0);
    if(annu->size==0){
        int n=1000;
        return n;
    }else{
        Elementa current_a=annu->head;
        int n=getNumAccount(current_a->p);
        while(current_a->next!=NULL){
            if(getNumAccount(current_a->p)<getNumAccount(current_a->next->p)){
                    n=getNumAccount(current_a->next->p);
            }
            current_a=current_a->next;
        }
        return n+1;
    }
}//fonctionne-->permet d'initialiser le num de compte
/*----------------------------------------------------------------*/
void affichAnnuaire(Annuaire annu){
    if(is_empty_annu(annu)){
        color("31;01");
        printf("Rien a afficher, l'Annuaire est vide.\n");
        color("37");
		return;
	}
	Elementa current_a= annu->head;
    int i;
    int j=annu->size;
    color("34;01");
    printf("\n   ***       Voici la liste des usagers       ***   \n");
    color("37");
	for (i=0;i<j;i++){
        printf("N° de compte :%d\n", getNumAccount(current_a->p));
        printf("Nom :%s\n", getName(current_a->p));
        printf("Prenom :%s\n", getPrenom(current_a->p));
        printf("Identifiant :%s\n", getIDPers(current_a->p));
        printf("\n\n");
        current_a=current_a->next;
	}
	color("34;01");
    printf("\n------------   FIN   -------------------\n");
    color("37");
	return;
}//fonctionne-->good color
/*----------------------------------------------------------------*/
Annuaire add_pers(Annuaire annu,Personne pers){
    if(annu->size==0){
        CLEAR_STDIN
        setNumAccount(pers,createNumAccount(annu));
        setIDPers(pers,createIDPers(pers));
        color("32;01");
        printf("Le compte a été créé avec succès\n");
        color("37");
        affich_pers(pers);
        print_pers_JSON(pers);
        addPersAnnu_JSON(pers);
        return push_ba(annu,pers);
    }
    int n;
    n=pers_existing(annu,pers);
    switch (n)
    {
    case 0 :
        CLEAR_STDIN
        setNumAccount(pers,createNumAccount(annu));
        setIDPers(pers,createIDPers(pers));
        color("32;01");
        printf("Le compte a été créé avec succès\n");
        color("37");
        affich_pers(pers);
        print_pers_JSON(pers);
        addPersAnnu_JSON(pers);
        
        annu=push_ba(annu,pers);
        break;
    case 1:
        CLEAR_STDIN
        color("31;01");
        printf("ERROR-Identifiant déjà utilisé.\n");
        color("37");
        CLEAR_STDIN
        exit(EXIT_FAILURE);
	break;
    case 3:
        CLEAR_STDIN
        color("31;1");
        printf("Cette adresse mail est déjà liée à un compte. Veuillez en choisir une autre\n");
        color("37");
        modif_mail(pers);
        
        annu=add_pers(annu,pers);
        break;
    case 4:
        CLEAR_STDIN
        color("31;1");
        printf("Ce numéro de téléphone est déjà lié à un compte. Veuillez en utiliser un autre\n");
        color("37");
        modif_tel(pers);
       
        annu=add_pers(annu,pers);
	break;
    default:
        break;
    }
	return annu;
}//fonctionne-permet d'ajouter une Personne n'existant pas encore à l'Annuaire-->good color
/*----------------------------------------------------------------*/
Annuaire remove_pers(Annuaire annu, Personne pers){
    int n;
    n=pers_existing(annu,pers);
    if(n==1){
    int i;
    i=getIndicePersonne(annu,pers);
    suppr_pers_JSON(getIDPers(pers));
    annu=remove_at(i,annu);
    updateAnnu_JSON(annu);
    color("32;01");
    printf("Ce compte a été supprimé avec succès\n");
    color("37");
    return annu;
    }else{
        color("31;01");
        printf("Ce compte n'existe pas dans l'annuaire il ne peut donc pas être supprimé\n");
        color("37");
        return annu;
    }
    
}//fonctionne-permet de supprimer une Personne de l'Annuaire-->good color
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
     return NULL;
}//fonctionne-permet de rechercher une personne ds un Annuaire à partir de son id ou de son adresse mail
/*----------------------------------------------------------------*/
Annuaire modifAnnuaireAdmin(int i,Annuaire annu,Personne temp){
    assert(0<annu->size);
    modif_persAdmin(temp);
    int n=pers_existing(annu,temp);
    switch (n){
        case 0:
            CLEAR_STDIN
            color("32;01");
            printf("Modification effectuée avec succès\n");
            color("37");
            affich_pers(temp);
            print_pers_JSON(temp);
            return insert_at(i,temp,annu);
        case 3:
            CLEAR_STDIN
            color("31;1");
            printf("Cette adresse mail est déjà liée à un compte. Veuillez en choisir une autre\n");
            color("37");
            return modifAnnuaireAdmin(i,annu,temp);
        case 4:
            CLEAR_STDIN
            color("31;1");
            printf("Ce numéro de téléphone est déjà lié à un compte. Veuillez en utiliser un autre\n");
            color("37");
            return modifAnnuaireAdmin(i,annu,temp);
        default:
            CLEAR_STDIN
            color("31;1");
            printf("\n----ERROR---\n");
            color("37");
            exit(EXIT_FAILURE);

            break;
        }
}//fonctionne-->good color
/*----------------------------------------------------------------*/
Annuaire modifAnnuaireUser(int i,Annuaire annu,Personne temp){
    assert(0<annu->size);
    
    modif_persUser(temp);
    int n=pers_existing(annu,temp);
    switch (n){
        case 0:
            CLEAR_STDIN
            color("32;01");
            printf("Modification effectuée avec succès\n");
            color("37");
            affich_pers(temp);
            print_pers_JSON(temp);
            
            return insert_at(i,temp,annu);

        case 3:
            CLEAR_STDIN
            color("31;1");
            printf("Cette adresse mail est déjà liée à un compte. Veuillez en choisir une autre\n");
            color("37");
            return modifAnnuaireUser(i,annu,temp);
        case 4:
            CLEAR_STDIN
            color("31;1");
            printf("Ce numéro de téléphone est déjà lié à un compte. Veuillez en utiliser un autre\n");
            color("37");
            return modifAnnuaireUser(i,annu,temp);
            
        default:
            CLEAR_STDIN
            color("31;1");
            printf("\n----ERROR---\n");
            color("37");
            exit(EXIT_FAILURE);
            break;
        }
}//fonctionne-->good color
/*----------------------------------------------------------------*/

Personne getPersonne_int(int i,Annuaire annu){
    Elementa current_a = annu->head;
    if(i>=annu->size || i <0){
        return NULL;
    }
    for(int j = 0;j<i; j++){
        current_a=current_a->next;
    }
	return current_a->p;
}
Annuaire createAccount(Annuaire annu){
    Personne p=create_pers();
    affich_pers(p);
    color("33;1");
    printf("\nVotre numéro de compte et Identifiant définitifs vous seront affectés plus tard\n");
    color("31;1");
    printf("\n !!! Veuillez noter votre identifiant,il vous est indipensable pour bénéficier pleinement de nos services !!!\n");
    color("37");
    int i;
    color("35;01");
    printf("\n\nEtes-vous satisfait des données enregistrées ?\nOUI=1\tNON=0\n");
    color("37");
    scanf("%d",&i);
    switch(i){
      case 0:
        CLEAR_STDIN  
        modif_persAdmin(p);
        color("33;1");
        printf("\nSi vous rencontrez des problèmes avec votre compte veuillez vous réfferer à un administrateur\n");
        color("37");
        annu=add_pers(annu,p); 
      case 1:
        CLEAR_STDIN
        color("33;1");
        printf("\nSi vous rencontrez des problèmes avec votre compte veuillez vous réfferer à un administrateur\n");
        color("37");
        annu=add_pers(annu,p); 
      default:
        CLEAR_STDIN
        color("31;1");
        printf("\nERROR--Vous allez être redirigé\n");
        color("37");
        free(p);
        annu=createAccount(annu);
    }
	return annu;
}//fonctionne-->good c

//fonctions pour le JSON
Annuaire LoadAnnu_JSON(Annuaire annu){
    char line[160];
 
    FILE*f = fopen("./data/Personne/Annuaire.dat","r");
    if(f!= NULL){
	rewind(f);
        while (!feof(f)){
            if(fgets(line,160,f)!=NULL){
                Personne p=LoadPersonne_JSON(strtok(line,","));
                annu=push_ba(annu,p);
           }else{
               continue;
            }
        }
    }else{
        fprintf(stderr, "Erreur :Impossible d'ouvrir le fichier.\n");
		exit(EXIT_FAILURE);
    }
    return annu;
}//fonctionne

void updateAnnu_JSON(Annuaire annu){
	FILE * file = fopen("./data/Personne/Annuaire.dat","w+");
    //fseek(file, 0, SEEK_SET);
    rewind(file);
    Elementa current_a=annu->head;
    int i;
    for(i=0;i<annu->size;i++){
        addPersAnnu_JSON(current_a->p);
        current_a=current_a->next;
    }
    fclose(file);
}//fonctionne


Ressource selectionRessource(Personne p, Liste l, Annuaire a){
  int choix;
  Elementl current = getHead(l);
  printf("Selectionnez une des ressources suivantes. \n");
  printf("(-1) Revenir en arrière.\n");
  for(int i = 0; i < list_size(l); i++){
    printf("( %d) %s\n",i,getNom(getCurrentRessource(current)));
    current = getNext(current);
  }
  scanf("%d", &choix);
  if(choix == -1){
    choix_admin(a,l,p);
    return NULL;
  }
  Ressource r = getRessource(choix, l);
  if(r == NULL){
    color("31;1");
    printf("Numéro incorrect. Réessayez!");
    color("37");
    return selectionRessource(p, l, a);
  }
  return r;
}

Personne selectionPersonne(Personne p, Liste l, Annuaire a){

  int choix;
  Elementa current = a->head;
  printf("Selectionnez une des ressources suivantes. \n");
  printf("(-1) Revenir en arrière.\n");
  for(int i = 0; i < annuaire_size(a); i++){
    printf("( %d) %s,%s\n",i,getName(current->p),getPrenom(current->p));
    current = current ->next;
  }
  scanf("%d", &choix);
  if(choix == -1){
      choix_admin(a,l,p);
    return NULL;
  }
  Personne t = getPersonne_int(choix,a); // METTRE TA FONCTION QUI PERMET DE RECUPERER UNE PERSONNE A PARTIR D'UN INDEX DANS UN ANNUAIRE
  if(t == NULL){ // SI NOMBRE INCORRECT, REGARDE NOS FONCTIONS getRessource à la limite
    color("31;1");
    printf("Numéro incorrect. Réessayez!");
    color("37");
    return selectionPersonne(p, l, a);
  }else{
    color("31;1");
    printf("Numéro incorrect. Réessayez!");
    color("37");
    return selectionPersonne(p, l, a);
  }
  return t;
}
void transfererRessource(Personne p, Liste l, Annuaire a){
  Ressource r = selectionRessource(p , l, a);
  printf("Vous allez transferer la ressource %s de type %s.\n", getNom(r),getType(r));
  Personne t = selectionPersonne(p, l, a);
  printf("Vous donnez la ressource à %s %s.\n", getName(t),getPrenom(t));
  setTakenBy(r, getIDPers(t));
  return;
}
