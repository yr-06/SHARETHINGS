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
    char date_naiss[13];//date de naissance
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
char*get_naiss(Personne p){
    return p->date_naiss;
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

int get_nb_pret(Personne p){
	return(p->emprunt->size);
}//consulter le nombre de pret

 //setters
void set_num_account(Personne p, int i){
   strcpy( p->num_account,i);
} 
void set_autor(Personne p,FILE*f){
    int a;
    char*mdp_admin;
    fscanf(f,"%s",mdp_admin);
    char *s;
    s=(char *)malloc(sizeof(char)*10);
    char*u ="USER";
    char*ad ="ADMIN";
    printf("Veuillez choisir l'habilitation du compte en tapant USER ou ADMIN :\n");
    scanf(%s,s);
    
    if(strcmp(s,u)==0){
        a=0;
        p->a=a;
        printf("Vous aves choisi d'être USER\n");
    }
    if(strcmp(s,ad)==0){
        char* cmp;
        cmp=(char *)malloc(sizeof(char)*65);
        printf("Veuillez entrer le mot de passe administrateur :\n");
        scanf("%65s",cmp);
        cmp=chiffrementMdp(cmp);
        if(strcmp(mdp_admin,cmp)==0){
            a=1;
            p->a=a;
            printf("Vous êtes habilité en tant qu'administrateur\n");
        }
    }
    else{
        printf("ERRROR");
        set_autor(p,f);
    }  
}

void set_name(Personne p,char*name){
    strcpy(p->nom,name);
}

void set_prenom(Personne p,char*prenom){
    strcpy(p->prenom,prenom);
}

void  set_naiss(Personne p, char*date){
    strcpy(p->date_naiss,date);
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

//Fonctions permettants de modifier données d'une personne
void modif_name(Personne p){
        char *name;
        name=(char*)malloc(sizeof(char)*33);
        printf("Veuillez entrer un nom:\n");
        scanf("%33s",name);
        set_name(p,name);
        free(name);
}

void modif_prenom(Personne p){
    char *prenom;
    prenom=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer un prénom:\n");
    scanf("%33s",prenom);
    set_prenom(p,prenom);
    free(prenom);
}

void modif_naiss(Personne p){
    char *naiss;
    naiss=(char*)malloc(sizeof(char)*13);
    printf("Veuillez entrer une date de naissance:\n");
    scanf("%13s",naiss);
    set_naiss(p,naiss);
    free(naiss);
}

void modif_id(Personne p){
    char *id;
    id=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer un identifiant:\n");
    scanf("%33s",id);
    set_id(p,id);
    free(id);
}

void modif_pwd(Personne p){
    char *pwd;
    char *crypted;
    pwd=(char*)malloc(sizeof(char)*65);
    crypted=(char*)malloc(sizeof(char)*65);
    printf("Veuillez entrer votre mot de passe:\n");
    scanf("%65s",pwd);
    crypted=chiffrementMdp(pwd);
    set_pwd(p,crypted);
    free(pwd);
    free(crypted);
   
}
void modif_mail(Personne p){
    char *mail;
    mail=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre adresse mail :\n");
    scanf("%32s",mail);
    set_mail(p,mail);
    free(mail);
}

void modif_tel(Personne p){
    char *tel;
    tel=(char*)malloc(sizeof(char)*16);
    printf("Veuillez entrer un numéro de téléphone :\n");   
    scanf("%16s",tel);
    set_tel(p,tel);
    free(tel);   
}

//Fonctions sur listes de Personnes= type Annuaire
Annuaire create_annuaire(){
    Annuaire annu=(Annuaire)malloc(sizeof(struct s_annuaire ));
    annu->size=0;
    annu->head=(Elementa)malloc(sizeof(struct s_elementa));
    annu->tail=(Elementa)malloc(sizeof(struct s_elementa));
    annu->head->p=(Personne)malloc(sizeof(struct s_pers));
    annu->head->p->emprunt=(Liste)malloc(size_of(struct s_liste));
    annu->head->i=0;
    annu->head->previous=NULL;
    annu->head->next=annu->tail;
    annu->tail->previous=annu->head;
    annu->tail->next=NULL;
    return annu;
}

Annuaire push_fa(Annuaire a,Elementa a){
    return annu;
}

Annuaire push_ba(Annuaire annu,int i, Elementa a){
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

    


//Fonction sur les manipulations de personnes
Personne create_pers(FILE *f){
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
    printf("Veuillez entrer votre prénom :\n");
    scanf("%33s",prenom);
    set_prenom(pers,prenom);
    free(prenom);

    char*date;
    date=(char*)malloc(sizeof(char)*13);
    printf("Veuillez entrer votre date de naissance au format JJ-MM-AAAA :\n");
    scanf("%13s",date);
    set_naiss(pers,date);
    free(date);

    char *id;
    id=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre identifiant:\n");
    scanf("%33s",id);
    set_id(pers,id);
    free(id);

    char *pwd;
    char *crypted;
    pwd=(char*)malloc(sizeof(char)*65);
    crypted=(char*)malloc(sizeof(char)*65);
    printf("Veuillez entrer votre mot de passe:\n");
    scanf("%65s",pwd);
    crypted=chiffrementMdp(pwd);
    set_pwd(pers,crypted);
    free(pwd);
    free(crypted);
   
    char *mail;
    mail=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre adresse mail :\n");
    scanf("%32s",mail);
    set_mail(pers,mail);
    free(mail);
    
    char *tel;
    tel=(char*)malloc(sizeof(char)*16);
    printf("Veuillez entrer votre numéro de téléphone :\n");
    scanf("%16s",tel);
    set_tel(pers,tel);
    free(tel);

    set_autor(pers,f);
    pers->emprunt=create_liste();
    return pers;
}//permet d'initialiser les champs de la structure Personne

void affich_pers(Personne p){
    printf("\nVoici le récapitulatif de vos informations personnelles:\n");
    printf("N° de compte :%s\n", get_num_account(p))
    printf("Nom :%s\n", get_name(p));
    printf("Prenom :%s\n", get_prenom(p));
    printf("Date de naissance :%s\n",get_naiss(p));
    printf("\n");
    printf("Identifiant :%s\n", get_id(p));
    printf("Mot de passe :%s\n", get_pwd(p));
    printf("\n");
    printf("Adresse mail :%s\n", get_mail(p));
    printf("N° de téléphone :%s\n", get_tel(p));
    printf("Nombre d'emprunt actuel :%s\n", get_nb_pret(p));
    if(get_autor(p)==1){
        printf("_--------Ce compte est habilité à se connecter en tant qu'administrateur----------\n");
    }
} 

Annuaire add_pers(Annuaire annu,Personne pers){
    int n=pers_existing (annu,pers);
    switch (n)
    {
    case 0 :
        print("Le compte a été créé avec succès\n");
        int i=annu->size-1;
        int num=create_num_account(annu,pers);
        set_num_account(num,pers);
        affich_pers(pers);
        annu= insert_at(i,pers,annu);
        return annu;
    case 1:
        printf("Identifiant déjà utilisé.Veuillez en changer\n");
        modif_id(pers);
        add_pers(annu,pers);
    case 2:
        print("Cet utilisateur existe déjà");
        modif_name(pers);
        modif_prenom(pers);
        modif_naiss(pers);
        add_pers(annu,pers);

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
}//permet d'ajouter une Personne n'existant pas encore à l'Annuaire

Annuaire remove_pers(Annuaire annu, Personne pers){
    int i=indice_personne_annu(annu,pers);
    annu=remove_at(i,annu);
    return annu;
}//permet de supprimer une Personne de l'Annuaire


Personne search_pers(Annuaire annu, char * id){
    Personne pers=(Personne)malloc(sizeof(struct s_pers));
     int i;
     int j=annu->size;
     Elementa current_a=annu->head;
     for (i=0;i<j;i++){
         if(strcmp(id,current_a->p->id)==0){
            pers=current->a->p;
         }
         current_a=current_a->next;
     }
     return pers;
}//permet de rechercher une personne ds un Annuaire à partir de son id 

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
}//indice d'une personne ds l'Annuaire

int pers_existing (Annuaire annu, Personne p){
    Elementa current_a=annu->head;
    int j=annu->size;
    int i;
    for (i=0;i<j;i++){
        if(strcmp(p->id,current_a->p->id)==0){
            //printf("Identifiant déjà utilisé.Veuillez en changer");
            return 1;
         }
         if(strcmp(p->nom,current_a->p->nom)==0){
             if (strcmp(p->prenom,current_a->p->prenom)==0){
                 if(strcmp(p->date_naiss,current_a->p->date_naiss)==0){
                      return 2;
                 }
             }
         }
         if(strcmp(p->mail,current_a->p->mail)==0){
             return 3;
         }
         if(strcmp(p->tel,current_a->p->tel)==0){
             return 4;
         }
         current_a=current_a->next;
    }
    return 0;
}//permet de vérifier si les données de la personne P ne sont pas déjà présentes

int create_num_account(Annuaire annu){
    int num=annu->tail->previous->p->num_account;
    int i=num++;
    return i;
}//permet d'initialiser le num de compte






