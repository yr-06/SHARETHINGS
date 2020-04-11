#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <crypt.h>
#include <unistd.h>
#include <string.h>
#include "../include/ressources.h"
#include "../include/chiffrement.h"
#include "../include/personne.h"

#ifndef CLEAR_STDIN
    #define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#endif
//structure a initialiser en dynamique
struct s_pers {
    int num_account;//numéro de compte (correspondra aussi à son indice dans Annuaire)
    int a;//int qui definit autorisation ou non d'entrer ds le menu admin
    char *nom;//nom de la personne
    char *prenom;//prenom de la personne
    char *date_naiss;//date de naissance
    char *id;//identifiant de son compte
    char *pwd;//mot de passe lié au compte
    char *mail;//mail de la personne
    char *tel;//numero de telephone de la personne
    //Liste emprunt;//Liste de Ressources empruntées actuellement par la personne
    //int possess; nbre de ressources dont la personne est proprio 
};

struct s_elementa{
    Personne p;
    struct s_elementa *previous;
    struct s_elementa *next;
};//element d'un Annuaire

struct s_annuaire {
    int size;
    Elementa head;
    Elementa tail;
};

//Définition d'un Booléen 
typedef enum{
    false,
    true
}Bool;

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
    return (p->nom);
}
/*----------------------------------------------------------------*/
char*getPrenom(Personne p){
    return (p->prenom);
}
/*----------------------------------------------------------------*/
char*getNaiss(Personne p){
    return (p->date_naiss);
}
/*----------------------------------------------------------------*/
char*getID(Personne p){
    return (p->id);
}
/*----------------------------------------------------------------*/
char*getPwd(Personne p){
    return (p->pwd);
}
/*----------------------------------------------------------------*/
char*getMail(Personne p){
    return (p->mail);
}   
/*----------------------------------------------------------------*/
char*getTel(Personne p){
    return (p->tel);
}
/*----------------------------------------------------------------*/
/*int getPossess(Personne p){
    return p->possess;
}*/
/*----------------------------------------------------------------*/
/*int getNbPret(Personne p){
	return(p->emprunt->size);
}//consulter le nombre de pret
*/
/*----------------------------------------------------------------*/

 //setters
void setNumAccount(Personne p, int i){
  p->num_account=i;
} 
/*void setAutor(Personne p,FILE*f){
    int a;
    char*mdp_admin;
    fscanf(f,"%s",mdp_admin);
    char *s;
    s=(char *)malloc(sizeof(char)*10);
    char*u ="USER";
    char*ad ="ADMIN";
    printf("\nVeuillez choisir l'habilitation du compte en tapant USER ou ADMIN :\n");
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
        }
    }
    else{
        printf("ERRROR");
        setAutor(p,f);
    }  
}*/
void setAutor(Personne p,int i){
    p->a=i;
}//version utilisée pour phase de tests
/*----------------------------------------------------------------*/
void setName(Personne p,char*name){
    strcpy(p->nom,name);
}
/*----------------------------------------------------------------*/
void setPrenom(Personne p,char*prenom){
    strcpy(p->prenom,prenom);
}
/*----------------------------------------------------------------*/
void  setNaiss(Personne p, char*date){
    strcpy(p->date_naiss,date);
}
/*----------------------------------------------------------------*/
void setID(Personne p,char*id){
   strcpy(p->id,id);
}
/*----------------------------------------------------------------*/
void setPwd(Personne p,char*pwd){
    strcpy(p->pwd,pwd);
}
/*----------------------------------------------------------------*/
void setMail(Personne p,char*mail){
    strcpy(p->mail,mail);
}   
/*----------------------------------------------------------------*/
void setTel(Personne p,char*tel){
    strcpy(p->tel,tel);
}
/*----------------------------------------------------------------*/
/*void setPossess(Personne p,int i){
    p->possess=i;
}*/
/*----------------------------------------------------------------*/

//Fonctions permettants de modifier données d'une personne

void modif_name(Personne p){
    char *name;
    char *newName;
    name=(char*)malloc(sizeof(char)*41);
    name=getName(p);
    
    newName=(char*)malloc(sizeof(char)*41);
    
    printf("Veuillez entrer un nouveau nom:\n");
    fgets(newName,41,stdin);
    
    if(strcmp(name,newName)==0){
        printf("Veuillez entrer un nom différent de celui déjà enregistré\n");
        free(newName);
        free(name);
        modif_name(p);
    }else{
        free(p->nom);
        (p->nom)=(char*)malloc(sizeof(char)*41);
        setName(p,newName);
       
    }    
}
/*----------------------------------------------------------------*/
void modif_prenom(Personne p){
    
    char *prenom;
    char *newPrenom;
    prenom=(char*)malloc(sizeof(char)*33);
    prenom=getPrenom(p);
    
    newPrenom=(char*)malloc(sizeof(char)*33);
    
    printf("Veuillez entrer un nouveau prénom:\n");
    fgets(newPrenom,33,stdin);
    
    if(strcmp(prenom,newPrenom)==0){
        printf("Veuillez entrer un prénom différent de celui déjà enregistré\n");
        free(newPrenom);
        free(prenom);
        modif_prenom(p);
    }else{
        free(p->prenom);
        (p->prenom)=(char*)malloc(sizeof(char)*33);
        setPrenom(p,newPrenom);
        free(newPrenom);
    }    
}
/*----------------------------------------------------------------*/
void modif_naiss(Personne p){
   
    char *naiss;
    char*newNaiss;
    naiss=(char*)malloc(sizeof(char)*21);
    naiss=getNaiss(p);
   
    newNaiss=(char*)malloc(sizeof(char)*21);
      
    printf("Veuillez entrer une nouvelle date de naissance:\n");
    fgets(newNaiss,21,stdin);
   
    if(strcmp(naiss,newNaiss)==0){
        printf("Veuillez entrer une date de naissance différente de celle déjà enregistrée\n");
        free(newNaiss);
        free(naiss);
        modif_naiss(p);
    }else{
        free(p->date_naiss);
        (p->date_naiss)=(char*)malloc(sizeof(char)*21);
        setNaiss(p,newNaiss);
        free(newNaiss);
    }    
 
}
/*----------------------------------------------------------------*/
void modif_id(Personne p){
   
    char *id;
    char*newID;
    id=(char*)malloc(sizeof(char)*33);
    id=getID(p);
    
    newID=(char*)malloc(sizeof(char)*33);
    
    printf("Veuillez entrer un nouvel identifiant:\n");
    fgets(newID,33,stdin);
   
    if(strcmp(id,newID)==0){
        printf("Veuillez entrer un identifiant différent de celui déjà enregistré\n");
        free(newID);
        free(id);
        modif_id(p);
    }else{
         free(p->id);
         (p->id)=(char*)malloc(sizeof(char)*33);
         setID(p,id);
         free(id);
    }    
}
/*----------------------------------------------------------------*/
void modif_pwd(Personne p){
    
     char *pwd;
     //char *crypted;
     char*newPwd;
    
     pwd=(char*)malloc(sizeof(char)*65);
     pwd=getPwd(p);
     
     //crypted=(char*)malloc(sizeof(char)*65);
     newPwd=(char*)malloc(sizeof(char)*65);
     
    printf("Veuillez entrer un nouveau mot de passe:\n");
    fgets(newPwd,65,stdin);
    
    //crypted=chiffrementMdp(newPwd);
    
    if(strcmp(pwd,newPwd)==0){
        printf("Veuillez entrer un mot de passe différent de celui déjà enregistré\n");
        free(newPwd);
        free(pwd);
        modif_pwd(p);
    }else{
         free(p->pwd);
         (p->pwd)=(char*)malloc(sizeof(char)*65);
         setPwd(p,newPwd);
         free(newPwd);
         //free(crypted);
    }    
    
}
/*----------------------------------------------------------------*/
void modif_mail(Personne p){
   
    char *mail;
    char *newMail;
    mail=(char*)malloc(sizeof(char)*33);
    mail=getMail(p);
    
    newMail=(char*)malloc(sizeof(char)*33);
    
    
    printf("Veuillez entrer une nouvelle adresse mail :\n");
    fgets(newMail,33,stdin);
    
    if(strcmp(mail,newMail)==0){
        printf("Veuillez entrer une adresse mail différente de celle déjà enregistrée\n");
        free(newMail);
        free(mail);
        modif_mail(p);
    }else{
        free(p->mail);
        (p->mail)=(char*)malloc(sizeof(char)*33);
        setMail(p,newMail);
        free(newMail);
    }
}
/*----------------------------------------------------------------*/
void modif_tel(Personne p){
    
    char *tel;
    char *newTel;
    tel=(char*)malloc(sizeof(char)*33);
    tel=getTel(p);
    
    newTel=(char*)malloc(sizeof(char)*33);
    
    printf("Veuillez entrer un nouveau numéro de téléphone :\n");
    fgets(newTel,33,stdin);
   
    if(strcmp(tel,newTel)==0){
        printf("Veuillez entrer un numéro de téléphone différent de celui déjà enregistré\n");
        free(newTel);
        free(tel);
        modif_tel(p);
    }else{
        free(p->tel);
        (p->tel)=(char*)malloc(sizeof(char)*33);
        setTel(p,newTel);
        free(newTel);
    }
}
/*----------------------------------------------------------------*/
//Fonction sur les manipulations de personnes
Personne initPers(){
    Personne pers=(Personne)malloc(sizeof(struct s_pers));
    (pers->nom)= (char*)malloc(sizeof(char)*41);
    (pers->prenom)=(char*)malloc(sizeof(char)*33);
    (pers->date_naiss)=(char*)malloc(sizeof(char)*21);
    (pers->id)=(char*)malloc(sizeof(char)*33);
    (pers->pwd)=(char*)malloc(sizeof(char)*65);
    (pers->mail)=(char*)malloc(sizeof(char)*33);
    (pers->tel)=(char*)malloc(sizeof(char)*33);
    //pers->emprunt=(Liste)malloc(sizeof(struct s_liste));
     //pers->emprunt=create_liste();
    return pers;
}
/*----------------------------------------------------------------*/
Personne create_pers(){
    Personne pers=initPers();
    //pers->emprunt= new_list();
    char *name;
    name=(char*)malloc(sizeof(char)*41);
    printf("Veuillez entrer votre nom :\n");
    fgets(name,41,stdin);
    setName(pers,name);
    free(name);
 
    char *prenom;
    prenom=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre prénom :\n");
    fgets(prenom,33,stdin);
    setPrenom(pers,prenom);
    free(prenom);
   
    char*date;
    date=(char*)malloc(sizeof(char)*21);
    printf("Veuillez entrer votre date de naissance au format JJ-MM-AAAA :\n");
    fgets(date,21,stdin);
    setNaiss(pers,date);
    free(date);

    char *id;
    id=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre identifiant:\n");
    fgets(id,33,stdin);
    setID(pers,id);
    free(id);

    char *pwd;
    //char *crypted;
    pwd=(char*)malloc(sizeof(char)*65);
    //crypted=(char*)malloc(sizeof(char)*65);
    printf("Veuillez entrer votre mot de passe:\n");
    fgets(pwd,65,stdin);
    //crypted=chiffrementMdp(pwd);
    //set_pwd(pers,crypted);
    setPwd(pers,pwd);
    free(pwd);
    //free(crypted);
   
    char *mail;
    mail=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre adresse mail :\n");
    fgets(mail,33,stdin);
    setMail(pers,mail);
    free(mail);
  
    char *tel;
    tel=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre numéro de téléphone :\n");
    fgets(tel,33,stdin);
    setTel(pers,tel);
    free(tel);
   
    setAutor(pers,1);//version de tests
    return pers;
}//permet d'initialiser les champs de la structure Personne
/*----------------------------------------------------------------*/
void affich_pers(Personne p){
    printf("\nVoici le récapitulatif des données de ce compte:\n");
    printf("N° de compte :%d\n", getNumAccount(p));
    printf("Nom :%s\n", getName(p));
    printf("Prenom :%s\n", getPrenom(p));
    printf("Date de naissance :%s\n",getNaiss(p));
    printf("\n");
    printf("Identifiant :%s\n", getID(p));
    printf("Mot de passe :%s\n", getPwd(p));
    printf("\n");
    printf("Adresse mail :%s\n", getMail(p));
    printf("N° de téléphone :%s\n", getTel(p));
    //printf("Nombre d'emprunt actuel :%d\n", getNbPret(p));
    //printf("Nombre de ressources créées:%d\n",getPossess(p));
    if(getAutor(p)==1){
        printf("--------Ce compte est habilité à se connecter en tant qu'administrateur----------\n");
    }
} 
/*----------------------------------------------------------------*/
void modif_pers(Personne p){
    int i;
    printf("\n\n Que voulez-vous modifier ?\n");
    printf(" Modifier nom: 1\n Modifier prenom: 2\n Modifier date de naissance: 3\n");
    printf(" Modifier identifiant: 4\n Modifier mot de passe: 5\n Modifier adresse mail: 6\n");
    printf(" Modifier numéro de téléphone: 7\n Modifier habilitation: 8\n Quitter: 0\n");
    printf(" \n\nSaisissez votre choix : \n");
    scanf("%d",&i);
    switch(i){
        case 0:
            CLEAR_STDIN
            break;
        case 1:
            CLEAR_STDIN
            modif_name(p);
            break;
        
        case 2:
            CLEAR_STDIN
            modif_prenom(p);
            break;
        
        case 3:
            CLEAR_STDIN
            modif_naiss(p);
            break;
        
        case 4:
            CLEAR_STDIN
            modif_id(p);
            break;
        
        case 5:
            CLEAR_STDIN
            modif_pwd(p);
            break;
        
        case 6:
            CLEAR_STDIN
            modif_mail(p);
            break;
            
        case 7:
            CLEAR_STDIN
            modif_tel(p);
            break;
        
        /*case 8:
            CLEAR_STDIN
            setAutor(p,f);*/
            
        default :
            break;
        }
    int u;
    printf(" Continuer les modifications ?\n OUI=1 ?\t NON=0 ?\n");
    scanf("%d",&u);
    if(u==1){
        CLEAR_STDIN
        modif_pers(p);
    }
}
/*----------------------------------------------------------------*/

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

Annuaire modif_annuaire(Annuaire annu,Personne p){
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
