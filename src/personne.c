#include <stdio.h>
#include <assert.h>
#include <crypt.h>
#include "../include/personne.h"
#include "../include/ressources.h"
#include "../include/chiffrement.h"
/*completer code des fonctions vides-->demander aux filles ou à PY*/

struct s_pers {
    int num_account;//numéro de compte (correspondra aussi à son indice dans Annuaire)
    autor a;//enum qui definit autorisation ou non d'entrer ds le menu admin
    char nom[32];//nom de la personne
    char prenom[32];//prenom de la personne
    char *id;//identifiant de son compte
    char *pwd;//mot de passe lié au compte
    char mail[64];//mail de la personne
    char tel[15];//numero de telephone de la personne
    Liste emprunt;//Liste de Ressources empruntées actuellement par la personne
    //Liste possession;--> liste des ressources dont la personne est proprio --> necessaire?
};

struct s_elementa{
    int i;
    Personne p;
    s_elementa *previous;
    s_elementa *next;
};//element d'un Annuaire


struct s_annuaire {
    int size;
    Elementa head;
    Elementa tail;
};

typedef enum autorisation [USER=0,ADMIN=1] autor;

//getters

char*get_num_account(Personne p){
    return p->num_account;
}

autor get_autor(Personne p){
    return p->a;
}

char*get_name(Personne p){
    return p->nom;
}

char*get_prenom(Personne p){
    return p->prenom;
}

char*get_id(Personne p){
    return p->id;
}

char*get_pwd(Personne p){
    return p->pwd;
}

char*get_mail(Personne p){
    return p->mail;
}   

char*get_tel(Personne p){
    return p->tel;
}



 //setters
void set_num_account(int i,Personne p){
    p->num_account=i;
} 
void set_autor(Personne p){
    int a;
    char *s;
    char*u ="USER";
    char*ad ="ADMIN";
    printf("Veuillez entrer votre abilitation :")
    scanf(%s,&s);
    int n=strcmp(s,u);
    int m=strcmp(s,ad);

    if(n=0){
        a=0;
        p->a=a;
    }
    if(m=0){
        a=1;
        p->a=a;
    }
    else{
        printf("ERRROR");
    }  
}

void set_name(Personne p){
    char name[32];
    printf("Veuillez entrer votre nom :")
    scanf(%s,&name);
    p->nom=name;
}

void set_prenom(Personne p){
    char prenom[32];
    printf("Veuillez entrer votre prénom :")
    scanf(%s,&prenom);
    p->prenom=prenom;
}

void set_id(Personne p){
    char *id;
    printf("Veuillez entrer votre identifiant:")
    scanf(%s,&id);
    p->id=id;
}

void set_pwd(Personne p){
    char *pwd;
    char *crypted;
    printf("Veuillez entrer votre mot de passe:")
    scanf(%s,&pwd);
    crypted=chiffrementMdp(pwd);
    p->pwd=crypted;
}

void set_mail(Personne p){
    char mail[15];
    printf("Veuillez entrer votre adresse mail :")
    scanf(%s,&mail);
    p->mail=mail;
}   

void set_tel(Personne p){
    char tel[15];
    printf("Veuillez entrer votre numéro de téléphone :")
    scanf(%s,&tel);
    p->tel=tel;
}

//Fonctions sur listes de Personnes= type Annuaire




int nb_pret(Personne p){
	return(p->emprunt->size);
//consulter le nombre de pret
}

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
}//permet d'ajouter un Elementa à un indice précis de l'Annuaire

Annuaire remove_at(int i,Annuaire annu){
    assert(i<annu->size)&&(i>=0);
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
}//permet d'enlever un Elementa à un indice précis de l'Annuaire

Annuaire add_pers(Annuaire annu,Personne pers){
    int i=annu->size-1;
    int num=create_num_account(annu,pers);
    set_num_account(num,pers);
    annu= insert_at(i,pers,annu);
    return annu;
}//permet d'ajouter une Personne à l'Annuaire

Annuaire remove_pers(Annuaire annu, Personne pers){
    int i=indice_personne_annu(annu,pers);
    annu=remove_at(i,annu);
    return annu;
}//permet de supprimer une Personne de l'Annuaire



//Fonction sur les manipulations de personnes
Personne create_pers(){
    Personne pers=(Personne)malloc(sizeof(s_pers));
    pers->emprunt=(Liste)malloc(sizeof(s_liste));
    set_autor(pers);
    set_name(pers);
    set_prenom(pers);
    set_id(pers);
    set_pwd(pers);
    set_mail(pers);
    set_tel(pers);
    return pers;
}//permet d'initialiser les champs de la structure Personne

Personne search_pers(Annuaire annu, char * id){
     int i;
     int j=annu->size;
     Elementa current_a=annu->head;
     for (i=0;i<j;i++){
         if(strcmp(id,current_a->p->id)){
             return current->a->p;
         }
         current_a=current_a->next;
     }
}//permet de rechercher une personne ds un Annuaire à partir de son id  

int create_num_account(Annuaire annu, Personne pers){
    int num=annu->tail->previous->p->num_account;
    int i=num++;
    return i;
}//permet d'initialiser le num de compte

int indice_personne_annu(Annuaire annu, Personne pers){
     int i;
     int j=annu->size;
     Elementa current_a=annu->head;
     for (i=0;i<j;i++){
         if(strcmp(pers->id,current_a->p->id)){
             return i;
         }
         current_a=current_a->next;
     }
}