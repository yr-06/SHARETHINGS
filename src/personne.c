#include <stdio.h>
#include <assert.h>
#include <crypt.h>
#include "../include/personne.h"
#include "../include/ressources.h"
#include "../include/chiffrement.h"
/*-completer code des fonctions vides-->demander aux filles ou à PY
-setters opérationnels (tester et réfléchir pour set_pwd, set_autor,set_emprunt)
-getters opérationnels (tester et répléchir celui de pwd, autor, emprunt)*/

struct s_pers {
    int num_account;//numéro de compte (correspondra aussi à son indice dans Annuaire)
    int a;//int qui definit autorisation ou non d'entrer ds le menu admin
    char nom[32];//nom de la personne
    char prenom[32];//prenom de la personne
    char id[32];//identifiant de son compte
    char pwd[64];//mot de passe lié au compte
    char mail[32];//mail de la personne
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

int get_autor(Personne p){
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
void set_num_account(Personne p, int i){
   strcpy( p->num_account,i);
} 
void set_autor(Personne p, int a){
    strcpy( p->a,a);
    /* int a;
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
    }  */
}

void set_name(Personne p,char*name){
    strcpy(p->nom,name);
}

void set_prenom(Personne p,char*prenom){
    strcpy(p->prenom,prenom);
}

void set_id(Personne p,char*id){
   strcpy(p->id,id);
}

void set_pwd(Personne p,char*pwd){
    strcpy(p->pwd,pwd);
}

void set_mail(Personne p,char*mail){
    strcpy(p->mail,mail);
}   

void set_tel(Personne p,char*tel){
    strcpy(p->tel,tel);
}


//Fonctions sur listes de Personnes= type Annuaire

int nb_pret(Personne p){
	return(p->emprunt->size);
}//consulter le nombre de pret


/*
Annuaire create_annuaire(){
    Annuaire annu=(Annuaire)malloc(sizeof(struct s_annuaire ));
}
Annuaire push_ba(Annuaire annu,int i, Elementa a){
    return annu;
}

Annuaire push_fa(Annuaire a,Elementa a){
    return annu;
}

Annuaire pop_fa(Annuaire ls){
    return annu;
}

Annuaire pop_ba(Annuaire ls){
    return annu;
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
*/

//Fonction sur les manipulations de personnes
Personne create_pers(){
    Personne pers=(Personne)malloc(sizeof(struct s_pers));
    pers->emprunt=(Liste)malloc(sizeof(struct s_liste));
    char *name;
    name=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre nom :\n");
    scanf("%33s",name);
    set_name(pers,name);
    free(name);

    char *prenom;
    prenom=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre prénom :");
    scanf("%33s",prenom);
    set_prenom(pers,prenom);
    free(prenom);
   

    char *id;
    id=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre identifiant:");
    scanf("%33s",id);
    set_id(pers,id);
    free(id);

    char *pwd;
    char *crypted;
    pwd=(char*)malloc(sizeof(char)*65);
    crypted=(char*)malloc(sizeof(char)*65);
    printf("Veuillez entrer votre mot de passe:");
    scanf("%65s",pwd);
    crypted=chiffrementMdp(pwd);
    set_pwd(pers,crypted);
    free(pwd);
    free(crypted);
   
    char *mail;
    mail=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre adresse mail :");
    scanf("%32s",mail);
    set_mail(pers,mail);
    free(mail);
    
    char *tel;
    tel=(char*)malloc(sizeof(char)*16);
    printf("Veuillez entrer votre numéro de téléphone :");
    scanf("%16s",tel);
    set_tel(pers,tel);
    free(tel);
    pers->emprunt=create_liste;
    return pers;
}//permet d'initialiser les champs de la structure Personne

/*
Personne search_pers(Annuaire annu, char * id){
    Personne pers=(Personne)malloc(sizeof(struct s_pers));
     int i;
     int j=annu->size;
     Elementa current_a=annu->head;
     for (i=0;i<j;i++){
         if(strcmp(id,current_a->p->id)){
            pers=current->a->p;
         }
         current_a=current_a->next;
     }
     return pers;
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
}*/