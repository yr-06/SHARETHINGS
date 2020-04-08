#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <crypt.h>
#include <unistd.h>
#include <string.h>
#include "../include/ressources.h"

struct s_pers {
    int num_account;//numéro de compte (correspondra aussi à son indice dans Annuaire)
    int a;//int qui definit autorisation ou non d'entrer ds le menu admin
    char nom[32];//nom de la personne
    char prenom[32];//prenom de la personne
    char date_naiss[20];//date de naissance
    char id[32];//identifiant de son compte
    char pwd[64];//mot de passe lié au compte
    char mail[32];//mail de la personne
    char tel[32];//numero de telephone de la personne
    Liste emprunt;//Liste de Ressources empruntées actuellement par la personne
    //Liste possession;--> liste des ressources dont la personne est proprio --> necessaire?
};
/*----------------------------------------------------------------*/
struct s_elementa{
    Personne p;
    struct s_elementa *previous;
    struct s_elementa *next;
};//element d'un Annuaire
/*----------------------------------------------------------------*/
struct s_annuaire {
    int size;
    Elementa head;
    Elementa tail;
};
/*----------------------------------------------------------------*/

//getters

int getNumAccount(Personne p){
    return p->num_account;
}
/*----------------------------------------------------------------*/
int getAutor(Personne p){
    return p->a;
}
/*----------------------------------------------------------------*/
char*getName(Personne p){
    return p->nom;
}
/*----------------------------------------------------------------*/
char * getPrenom(Personne p){
    return (p->prenom);
}
/*----------------------------------------------------------------*/
char * getNaiss(Personne p){
    return (p->date_naiss);
}
/*----------------------------------------------------------------*/
char * getID(Personne p){
    return (p->id);
}
/*----------------------------------------------------------------*/
char * getPwd(Personne p){
    return (p->pwd);
}
/*----------------------------------------------------------------*/
char * getMail(Personne p){
    return (p->mail);
}   
/*----------------------------------------------------------------*/
char * getTel(Personne p){
    return (p->tel);
}
/*----------------------------------------------------------------*/
Liste getListeEmprunt(Personne p){
	return (p->emprunt);
}
/*----------------------------------------------------------------*/
int getNbPret(Personne p){
	return(p->emprunt->size);
}//consulter le nombre de pret
/*----------------------------------------------------------------*/

//setters
void setNumAccount(Personne p, int i){
   strcpy( p->num_account,i);
}
/*----------------------------------------------------------------*/ 

void setAutor(Personne p,FILE*f){
    int a;
    char*mdp_admin;
    fscanf(f,"%s",mdp_admin);
    char *s;
    s=(char *)malloc(sizeof(char)*10);
    char*u ="USER";
    char*ad ="ADMIN";
    printf("Veuillez choisir l'habilitation du compte en tapant USER ou ADMIN :\n");
    scanf("%s",s);
    
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
        }else{
          printf("ERRROR-Mot de passe incorrect\n");
          setAutor(p,f);
        }
    }
    else{
        printf("ERRROR");
        setAutor(p,f);
    }  
}
/*----------------------------------------------------------------*/

void setName(Personne p,char * name){
    strcpy(p->nom,name);
}
/*----------------------------------------------------------------*/

void setPrenom(Personne p,char * prenom){
    strcpy(p->prenom,prenom);
}
/*----------------------------------------------------------------*/

void  setNaiss(Personne p, char * date){
    strcpy(p->date_naiss,date);
}
/*----------------------------------------------------------------*/
void setId(Personne p,char * id){
   strcpy(p->id,id);
}
/*----------------------------------------------------------------*/
void setPwd(Personne p,char * pwd){
    strcpy(p->pwd,pwd);
}
/*----------------------------------------------------------------*/
void setMail(Personne p,char * mail){
    strcpy(p->mail,mail);
}   
/*----------------------------------------------------------------*/
void setTel(Personne p,char * tel){
    strcpy(p->tel,tel);
}
/*----------------------------------------------------------------*/

//Fonctions permettants de modifier données d'une personne

void modif_name(Personne p){
  char *name;
  name=(char*)malloc(sizeof(char)*33);
  printf("Veuillez entrer un nom:\n");
  scanf("%[^\n]%*c",name); 
  setName(p,name);
  free(name);
}
/*----------------------------------------------------------------*/

void modif_prenom(Personne p){
  char *prenom;
  prenom=(char*)malloc(sizeof(char)*33);
  printf("Veuillez entrer un prénom:\n");
  scanf("%[^\n]%*c",prenom); 
  setPrenom(p,prenom);
  free(prenom);
}
/*----------------------------------------------------------------*/
void modif_naiss(Personne p){
  char *naiss;
  naiss=(char*)malloc(sizeof(char)*21);
  printf("Veuillez entrer une date de naissance:\n");
  scanf("%[^\n]%*c",naiss); 
  //scanf("%21s",naiss);
  setNaiss(p,naiss);
  free(naiss);
}
/*----------------------------------------------------------------*/
void modif_id(Personne p){
  char *id;
  id=(char*)malloc(sizeof(char)*33);
  printf("Veuillez entrer un identifiant:\n");
  scanf("%33s",id);
  setId(p,id);
  free(id);
}
/*----------------------------------------------------------------*/
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
/*----------------------------------------------------------------*/
void modif_mail(Personne p){
    char *mail;
    mail=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre adresse mail :\n");
    scanf("%33s",mail);
    setMail(p,mail);
    free(mail);
}
/*----------------------------------------------------------------*/
void modif_tel(Personne p){
    char *tel;
    tel=(char*)malloc(sizeof(char)*33);
    printf("\nVeuillez entrer un numéro de téléphone :");   
    scanf("%[^\n]%*c",tel); 
    //scanf("%21s",tel);
    setTel(p,tel);
    free(tel);   
}
/*----------------------------------------------------------------*/

//Fonctions sur listes de Personnes= type Annuaire
/Fonctions sur listes de Personnes= type Annuaire
Annuaire create_annuaire(){
    Annuaire annu=(Annuaire)malloc(sizeof(struct s_annuaire ));
    annu->size=0;
    /*annu->head=(Elementa)malloc(sizeof(struct s_elementa));
    annu->tail=(Elementa)malloc(sizeof(struct s_elementa));
    annu->head->p=(Personne)malloc(sizeof(struct s_pers));
    annu->tail->p=(Personne)malloc(sizeof(struct s_pers));
    //annu->head->p->emprunt=(Liste)malloc(size_of(struct s_liste));
    //annu->tail->p->emprunt=(Liste)malloc(size_of(struct s_liste));
    annu->head->i=0;
    annu->tail->i=0;
    annu->head->previous=NULL;
    annu->head->next=NULL;
    annu->head=annu->tail;*/
    return annu;
}

int create_num_account(Annuaire annu){
    assert(annu->size>=1);
    int i=getNumAccount(annu->tail->p)++;
    return i;
}//permet d'initialiser le num de compte

void affich_list_pers(Annuaire annu,FILE*f){
     int i;
     int j=annu->size;
     Elementa current_a=annu->head;
     for (i=0;i<j;i++){
        fprintf(f,"N° de compte :%d\t", getNumAccount(current_a->p));
        fprintf(f,"Nom :%s\t", getName(current_a->p));
        fprintf(f,"Prenom :%s\t", getPrenom(current_a->p));
        fprintf(f,"Date de naissance :%s\t",getNaiss(current_a->p));
        fprintf(f,"Identifiant :%s\n", getID(current_a->p));
        current_a=current_a->next;
    } 
}

Annuaire add_pers(Annuaire annu,Personne pers){
    int n=pers_existing(annu,pers);
    switch (n)
    {
    case 0 :
        print("Le compte a été créé avec succès\n");
        int i=annu->size-1;
        int num=create_num_account(annu);
        setNumAccount(num,pers);
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
         if(strcmp(id,getID(current_a->p))==0){
            pers=current_a->p;
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
         if(strcmp(getID(pers),getID(current_a->p))==0){
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
}//permet de vérifier si les données de la personne P ne sont pas déjà présentes

Annuaire modif_annuaire(Annuaire annu,Personne p, FILE*f){
     int j=annu->size;
     int i;
     Elementa current_a=annu->head;
     for (i=0;i<j;i++){
         if(strcmp(getID(p),getID(current_a->p))==0){
            modif_pers(current_a->p,f);
            int n=pers_existing (annu,current_a->p);
            switch (n){
                case 0:
                    printf("Modification effectuée avec succès\n");
                    affich_pers(current_a->p);
                    return annu;
                case 1:
                    printf("Identifiant déjà utilisé.Veuillez en changer\n");
                    modif_pers(current_a->p,f);
                    break;
                case 2:
                    print("Cet utilisateur existe déjà\n");
                    affich_pers(current_a->p);
                    modif_pers(current_a->p,f);
                    //return annu;
                case 3:
                    printf("Cette adresse mail est déjà liée à un compte. Veuillez en choisir une autre\n");
                    modif_pers(current_a->p,f);
                    break;
                case 4:
                    printf("Ce numéro de téléphone est déjà lié à un compte. Veuillez en utiliser un autre\n");
                    modif_pers(current_a->p,f);
                    break;
                default:
                        break;
                }
            }
         current_a=current_a->next;
     }

}
