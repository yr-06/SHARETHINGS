#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../include/ressources.h"
#ifndef CLEAR_STDIN
    #define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#endif

//structures:
//Ressource
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


/*----------------------------------------------------------------*/
//Fonctions sur les manipulations de Liste

Liste new_list(){
    Liste l =(Liste)malloc(sizeof(struct s_liste *));
    if(l== NULL){
        fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
        exit(EXIT_FAILURE);
    }
    l->size= 0;
	return l;
}//fonctionne-initialise la structure Liste pour utilisation 
/*----------------------------------------------------------------*/
Bool is_empty_list(Liste l){
	if(l->size== 0)
		return true;

	return false;
}//fonctionne
/*----------------------------------------------------------------*/
int list_size(Liste l){
	if(is_empty_list(l))
		return 0;

	return l->size;
}//fonctionne
/*----------------------------------------------------------------*/
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
}//fonctionne-utile pour phase de tests
/*----------------------------------------------------------------*/
Liste push_bl(Liste l,Ressource r){
	Elementl element;

	element = malloc(sizeof(struct s_elementl));

	if(element == NULL){
        fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}
	element->r=initRessource();
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
}//fonctionne-ajoute un élément en fin de liste
/*----------------------------------------------------------------*/
Liste push_fl(Liste l,Ressource r){
	Elementl element;

	element = malloc(sizeof(struct s_elementl));

	if(element == NULL)
	{
		fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}

	element->r =initRessource();
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
}//fonctionne-ajoute un élément en début de liste
/*----------------------------------------------------------------*/
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
}//fonctionne-supprime un élément en fin de liste
/*----------------------------------------------------------------*/
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
}//fonctionne-supprime un élement en début de liste
/*----------------------------------------------------------------*/
Liste clear_list(Liste l){
	while(!is_empty_list(l))
		l = pop_bl(l);

	return new_list();
}//fonctionne-vide une liste
/*----------------------------------------------------------------*/
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
        l->r=initRessource();
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
}//permet d'ajouter une Ressource à un indice précis de la Liste
/*----------------------------------------------------------------*/
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
}//permet d'enlever une Ressource à un indice précis de la Liste

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
}//vérifie existence d'une ressource

/*Ce sont des fonctions que j'avais écrites depuis un moment déjà et que g utiliser pour les phases de tests à toi de voir si tu les gardes ou pas elles ressemblent bcp à celles que tu as déjà mais elles sont plus complètes

//Ressource à implémenter totalement en dynamique
j'ai utilisé cette structure le champ date_crea n'est qu'une idée que g eu je l'ai pas utilisée mais on en reparlera
struct s_ressource {
    char *type;//type de ressouces: livre, bouteilles,CD,magazines,etc...
    char *nom;//nom de la ressource
    char *ID;//= ID de la ressource
    char *takenBy;// = ID de l'utilisateur qui a pris la ressource.
    char *dropBy;// = ID de l'utilisateur qui a déposé la ressource.
	//char*date_crea;//peut être interresant pour période d'opérations (char* ou int ?)
    char *date_d;//date de debut du pret 
    char *date_f;//date de fin du pret
};

/*char*getDateCrea(Ressource r){
	return r->date_crea;
}
void setDateCrea(Ressource r,char* date_crea){
	strcpy(r->date_crea,date_crea);
}*/

/*//modifyer
void modifType(Ressource r){
    char *type;
    char *newType;
    type=(char*)malloc(sizeof(char)*33);
    type=getType(r);

    newType=(char*)malloc(sizeof(char)*33);
    
    printf("Veuillez entrer un nouveau type:\n");
    fgets(newType,33,stdin);
    
    if(strcmp(type,newType)==0){
        printf("Veuillez entrer un type différent de celui déjà enregistré\n");
        free(newType);
        free(type);
        modifType(r);
    }else{
        free(r->type);
        (r->type)=(char*)malloc(sizeof(char)*33);
        setType(r,newType);
    }    
}//fonctionne

void modifNom(Ressource r){
    char *name;
    char *newName;
    name=(char*)malloc(sizeof(char)*65);
    name=getNom(r);
        
    newName=(char*)malloc(sizeof(char)*65);
        
    printf("\nVeuillez entrer un nouveau nom pour cette ressource:\n");
    fgets(newName,65,stdin);
     
    if(strcmp(name,newName)==0){
        printf("Veuillez entrer un nom différent de celui déjà enregistré\n");
        free(newName);
        free(name);
        modifNom(r);
    }else{
        free(r->nom);
        (r->nom)=(char*)malloc(sizeof(char)*65);
        setName(r,newName);
    }    
}//fonctionne

void modifDate_Deb(Ressource r){
    char *dated;
    char *newDated;
    dated=(char*)malloc(sizeof(char)*21);
    dated=getDateDebut(r);
    
    newDated=(char*)malloc(sizeof(char)*21);
   
    printf("Veuillez entrer une nouvelle date de début de prêt au format JJ-MM-AAAA:\n");
    fgets(newDated,21,stdin);
    
    if(strcmp(dated,newDated)==0){
        printf("Veuillez entrer un date différente de celle déjà enregistrée\n");
        free(newDated);
        free(dated);
        modifDate_Deb(r);
    }else{
        free(r->date_d);
        (r->date_d)=(char*)malloc(sizeof(char)*21);
        setDateDebut(r,newDated);
    }    
}//fonctionne

void modifDate_Fin(Ressource r){
    char *dated;
    char *datef;
    char *newDatef;
    dated=(char*)malloc(sizeof(char)*21);
    datef=(char*)malloc(sizeof(char)*21);
    
    dated=getDateDebut(r);
    datef=getDateFin(r);
    
    newDatef=(char*)malloc(sizeof(char)*21);
   
    printf("Veuillez entrer une nouvelle date de fin de prêt au format JJ-MM-AAAA:\n");
    fgets(newDatef,21,stdin);
    
    if(strcmp(datef,newDatef)==0){
        printf("Veuillez entrer une date différente de celle déjà enregistrée\n");
        free(newDatef);
        free(datef);
        free(dated);
        modifDate_Fin(r);
    }if(strcmp(newDatef,dated)==0){
        printf("Veuillez entrer une date différente de celle de début de prêt\n");
        free(newDatef);
        free(datef);
        free(dated);
        modifDate_Fin(r);
    }else{
        free(r->date_f);
        (r->date_f)=(char*)malloc(sizeof(char)*21);
        setDateFin(r,newDatef);
    }    
    
}//fonctionne
void modif_ress(Ressource r){
    int i;
    printf("\n\n Que voulez-vous modifier ?\n");
    printf(" Modifier type: 1\n Modifier nom: 2\n");
    printf(" Quitter: 0\n");
    printf(" \nSaisissez votre choix : \n");
    scanf("%d",&i);
    switch (i)
    {
    case 0:
        break;
    case 1:
        CLEAR_STDIN
        modifType(r);
        break;
    case 2:
        CLEAR_STDIN
        modifNom(r);
        break;
    default:
        break;
    }
    int u;
    printf(" Continuer les modifications ?\n OUI=1 ?\t NON=0 ?\n");
    scanf("%d",&u);
    if(u==1){
        modif_ress(r);
    }
}//fonctionne

Ressource initRessource(){
	Ressource r = (Ressource)malloc(sizeof(struct s_ressource));
  (r->type) = (char*)malloc(sizeof(char)*33);
  (r->nom)=(char*)malloc(sizeof(char)*65);
	(r->takenBy) = (char*)malloc(sizeof(char)*33);
  (r->ID)=(char*)malloc(sizeof(char)*33);
	(r->dropBy) = (char*)malloc(sizeof(char)*33);
	//(r->date_crea)=(char*)malloc(sizeof(char)*21);
	(r->date_d) = (char*)malloc(sizeof(char)*21);
	(r->date_f) = (char*)malloc(sizeof(char)*21);
	return r;
}//fonctionne

Ressource create_ress(){
    Ressource r=initRessource();
    
    char *type;
    type=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer le type de cette ressource:\n");
    fgets(type,33,stdin);
    setType(r,type);
   

    char *name;
    name=(char*)malloc(sizeof(char)*65);
    printf("Veuillez entrer un nom pour cette ressource:\n");
    fgets(name,65,stdin);
    setName(r,name);
    

    char *id;
    id=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer un identifiant pour cette ressource:\n");
    fgets(id,33,stdin); 
    setID(r,id);
   

    char *dropb;
    dropb=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre identifiant :\n");
    fgets(dropb,33,stdin);
    setDropBy(r,dropb);
    setTakenBy(r,"0");
    

    char *dated;
    dated=(char*)malloc(sizeof(char)*21);
    printf("Veuillez entrer la date du jour si vous créez cette ressource au format JJ-MM-AAAA :\n");
    fgets(dated,21,stdin);
    setDateDebut(r,dated);
		setDateFin(r,dated);
		//setDateCrea(r,dated);
   return r;

}//permet d'initialiser les champs de la structure Ressource

void affich_ress(Ressource r){
    printf("\nVoici le récapitulatif des données liées à cette ressource:\n");
    printf("Type :%s\n", getType(r));
    printf("Nom :%s\n", getNom(r));
    printf("ID:%s\n", getID(r));
    printf("Propriétaire :%s\n",getDropBy(r));
		//printf("Créée le:%s\n",getDateCrea(r));
    printf("\n");
   
    if(isDispo(r)==0){
        printf("Statut : Emprunté\n");
        printf("Emprunté par :%s\n", getTakenBy(r));
        printf("Date de début du pret:%s\n", getDateDebut(r));
        printf("Date de fin du pret:%s\n", getDateFin(r));
    }else{
         printf("Statut : Disponible\n\n");
    }
}//fonctionne
*/

/*C le main que j'ai utilisé pour tester je te laisse pour que tu te familiarises avec les fonctions sur les Listes

int main(int argc, char *argv[]){
    Liste ls=new_list();
    Ressource r=create_ress();
    Ressource s=create_ress();
    Ressource t=create_ress();
    
    ls=push_bl(ls,r);
    ls=push_bl(ls,s);
    ls=push_fl(ls,t);
    printf("---------------------------LISTE 1---------------------\n");
    print_list(ls);
    modif_ress(r);
    
    printf("---------------------------LISTE 2---------------------\n");
    print_list(ls);
    
    ls=pop_bl(ls);
    ls=pop_fl(ls);
    printf("---------------------------LISTE 3---------------------\n");
    print_list(ls);
   
    ls=clear_list(ls);
    print_list(ls);
    
    free(ls);
    ls=NULL;
} */
