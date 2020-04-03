
#include <stdio.h>
#include <stlib.h>
#include <string.h>
#include <assert.h>
#include <crypt.h>
#include "../include/chiffrement.h"
#include "../include/ressources.h"


//le takenBy fait office de boolean mais en chaine de caractères. Tout simplement, si une ressource
//qu'on veut emprunter est disponible, alors la valeur de takenBy vaudra 0 ou ' '.
// Si elle ne l'est pas, ce sera remplacé non pas par 1 mais pas l'identifiant de celui qui l'a pris.
//Cela permet de savoir qui a emprunté la ressource. Ce char nous aide aussi pour la fonction "dispo".
//Pour le dropBy, en effet ca n'avait rien à voir. J'espère que tu comprendras mieux avec les nvx coms. 
//structures:

//Ressouce
 struct s_ressource {
    char type[32];//type de ressouces: livre, bouteilles,CD,magazines,etc...
    char nom[32];//nom de la ressource
    int a;//int qui definit si ressource est dispo ou non
    char ID[64];//= ID de la ressource
    char takenBy[32];// = ID de l'utilisateur qui a pris la ressource.
    char dropBy[32];// = ID de l'utilisateur qui a déposé la ressource.
    char date_d[15];//date de debut du pret 
    char date_f[15];//date de fin du pret
};

//Element d'une liste
struct s_elementl{
    int i;
    Ressource r;
    s_elementl *previous;
    s_elementl *next;
};
//Liste
struct s_liste {
    int size;
    Elementl head;
    Elementl tail;
};
 
//getters :
//recuperer les informations liees a la ressource
char*getType(Ressource r){
    return(r->type);
}

char * getNom(Ressource r) {
	return(r->nom);
}

int getDispo(Ressource r){
    return(r->a);
}

char * getID(Ressource r){
	return(r->ID);
}

char * getTakenBy(Ressource r){
	return(r->takenBy);
}

char * getDropBy(Ressource r){
	return(r->dropBy);
}

char * getDateDebut(Ressource r){
	return(r->date_d);
}

char * getDateFin(Ressource r){
	return(r->date_f);
}

/*Ressource getNextRessource(Ressource r){
	return(r->next);
}

//permet de savoir par qui la ressource est empruntee
char * getRessourceDispo(Ressource r){
        if(isDispo(r) == 1){
           return "La ressource est disponible."
       }
        return getTakenBy(r);//return l'ID de celui qui l'a emprunté.
}*/

//setters:
void setType(Ressource r,char*type){
    strcpy(r->type,type);
}
void setName(Ressource r,char*name){
    strcpy(r->nom,name);
}
void setDispo(Ressource r, int d){
    r->a=d;
}
void setID(Ressource r,char*id){
    strcpy(r->ID,id);
}
void setTakenBy(Ressource r, char * takenBy){
	strcpy(r->takenBy, takenBy);
}
void setDropBy(Ressource r, char * dropBy){
	strcpy(r->dropBy,);
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

void modifDate_Deb(Ressource r){
    char *date;
    date=(char*)malloc(sizeof(char)*16);
    printf("Veuillez entrer une date de début de prêt:\n");
    scanf("%16s",date);
    setDateDebut(r,date);
    free(date);
}

void modifDate_Fin(Ressource r){
    char *date;
    date=(char*)malloc(sizeof(char)*16);
    printf("Veuillez entrer une date de fin de prêt:\n");
    scanf("%16s",date);
    setDateFin(r,date);
    free(date);
}

/*char ressource_dispo(Ressource r){
//permet de savoir si une ressource est disponible
 return c
}
int nb_emprunt(Personne p){
//consulter le nombre d'emprunt
    return i;
}
void rappel_finEmprunt(Ressources r){
//va afficher un message de rappel quand ce sera la fin de l'emprunt
}
*/

//Fonction sur les Listes
Liste create_liste(){
    Liste ls=(ls)malloc(sizeof(struct s_liste ));
    ls->size=0;
    ls->head=(Elementl)malloc(sizeof(struct s_elementl));
    ls->tail=(Elementl)malloc(sizeof(struct s_elementl));
    ls->head->r=(Ressource)malloc(sizeof(struct s_ressource));
    ls->head->i=0;
    ls->head->previous=NULL;
    ls->head->next=ls->tail;
    ls->tail->previous=ls->head;
    ls->tail->next=NULL;
    return ls;
}

/*
Liste push_bl(Liste ls,int i, Elementl l){
 return ls;
}//push un element ds le next de l'element à l'indice i (est utilisé pour insert_at)

Liste push_fl(Liste ls,Elementl l){
    return ls;

}//push un element ds le previous de l'element à l'indice i (est utilisé pour insert_at)


Liste pop_fl(Liste ls){
    return ls;
}//pop un element ds le previous de l'element à l'indice i (est utilisé pour remove_at)

Liste pop_bl(Liste ls){
    return ls;
}//pop un element ds le next de l'element à l'indice i (est utilisé pour remove_at)
*/

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



//Fonction sur les manipulations de Ressources
Ressource create_ress(){
    Ressource r=(Ressource)malloc(sizeof(struct s_ressource));

    char *type;
    type=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer le type de cette ressource:\n");
    scanf("%33s",type);
    setType(r,type);
    free(type);

    char *name;
    name=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer un nom pour cette ressource:\n");
    scanf("%33s",name);
    setName(r,name);
    free(name);

    char *id;
    id=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer un identifiant pour cette ressource:\n");
    scanf("%33s",id);
    setName(r,id);
    free(id);

    setDispo(r,0);

    char *tkb;
    tkb=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre identifiant :\n");
    scanf("%33s",tkb);
    setTakenBy(r,tkb);
    setDropBy(r,tkb);
    free(tkb);

    char *dated;
    dated=(char*)malloc(sizeof(char)*16);
    printf("Veuillez entrer une date de début de prêt JJ-MM-AAAA:\n");
    printf("(Entrez la date du jour si vous créez cette ressource )\n");
    scanf("%16s",dated);
    setDateDebut(r,dated);
    free(dated);

    char *datef;
    datef=(char*)malloc(sizeof(char)*16);
    printf("Veuillez entrer une date de fin de prêt au format JJ-MM-AAAA:\n");
    printf("(Entrez la date du jour si vous créez cette ressource )\n");
    scanf("%16s",datef);
    setDateFin(r,datef);
    free(datef);

}//permet d'initialiser les champs de la structure Ressource
void affich_ress(Ressource r){
    printf("\nVoici le récapitulatif des données liées à cette ressource:\n");
    printf("Type :%s\n", getType(r));
    printf("Nom :%s\n", getName(r));
    printf("ID:%s\n", getID(r));
    printf("Propriétaire :%s\n",getDropBy(r));
    printf("\n");
   
    if(getDispo(r)==1){
        printf("Statut : Emprunté\n");
        printf("Emprunté par :%s\n", getTakenBy(r));
        printf("Date de début du pret:%s\n", getDateDebut(r));
        printf("Date de fin du pret:%s\n", getDateFin(r));
    }else{
         printf("Statut : Occupé\n");
    }
    printf("\n");
}
void affich_list_ress(Liste ls,FILE*f){
     int i;
     int j=ls->size;
     Elementl current_l=ls->head;
     for (i=0;i<j;i++){
        fprintf(f,"Type :%s\t", getType(current_l->r))
        fprintf(f,"Nom :%s\t", get_name(current_l->r));
        fprintf(f,"Identifiant :%s\n", get_id(current_a->p));
        fprintf(f,"Prenom :%s\t", get_prenom(current_a->p));
        fprintf(f,"Date de naissance :%s\t",get_naiss(current_a->p));
        current_a=current_a->next;
    } 
}

Liste add_ress(Liste ls,Ressource ress){
    int n=ress_existing(ls,ress);
    switch (n)
    {
    case 0 :
        print("Le compte a été créé avec succès\n");
        int i=ls->size-1;
        affich_ress(ress);
        ls= insert_at(i,ress,ls);
        return ls;
    case 1:
        printf("Identifiant déjà utilisé.Veuillez en changer\n");
        modifID(ress);
        add_ress(ls,ress);
    case 2:
        print("Cette ressource existe déjà");
        modifNom(ress);
        add_ress(ls,ress);
        break;
    default:
        break;
    }
}//permet d'ajouter une Ressource n'existant pas encore à la Liste
Liste remove_ress(Liste ls, Ressource ress){
    int i= getIndex(ls, ress);
    ls=remove_at(ls,ress);
    return ls;
}//permet de supprimer une Ressource de la Liste

Ressource search_ress(Liste ls, char * id){
    Ressource ress=(Ressource)malloc(sizeof(struct s_ressource));
     int i;
     int j=annu->size;
     Elementl current_l=ls->head;
     for (i=0;i<j;i++){
         if(strcmp(id,current_a->p->id)==0){
            ress=current_l->r;
         }
         current_a=current_a->next;
     }
     return pers;
}//permet de rechercher une personne ds une Liste à partir de son id 

//fonction qui récupère l'indice d'une ressource dans une liste de ressources.
int getIndex(Liste l,Ressource r){
	int pos;
	Elementl current = l->head;
	for(int i = 0; i<(l->size);i++){
		if(strcmp(r->ID,current->r->ID)){
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
}//-> fonction casse-gueule car l'index n'est pas fixe

void search_ress_type(Liste ls,char*type){
    Elementl current_l=ls->head;
    int i;
    int j=ls->size;
    for (i = 0; i<j; i++){
        if(strcmp(type,current_l->r->type)==0){
            printf("Type\t Nom\t Identifiant\t Takenby\n\n");
            printf("%s\t %s\t %s\t %s\n",getType(current_l->r),getNom(current_l->r),getID(current_l->r),getTakenBy(current_l->r));
        }
        current_l=current_l->next;
    }
}//affiche les toutes les Ressources de la Liste du type choisi

int ress_existing (Liste ls, Ressource r){
    Elementl current_l=ls->head;
    int j=ls->size;
    int i;
    for (i=0;i<j;i++){
        if(strcmp(r->ID,current_l->r->ID)==0){
            return 1;
         }
         if(strcmp(r->type,current_l->r->type)==0){
             if (strcmp(r->nom,current_l->r->nom)==0){
                 return 2;
             }
         }
         current_l=current_l->next;
    }
    return 0;
}//permet de vérifier si les données de la ressources saisies correspondent à une ressource déjà existante



