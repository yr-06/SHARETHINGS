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
    int possess; //nbre de ressources dont la personne est proprio 
    //Liste emprunt;//Liste de Ressources empruntées actuellement par la personne
};

struct s_elementa{
    Personne p;
    struct s_elementa *previous;
    struct s_elementa *next;
};//element d'un Annuaire

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
int getPossess(Personne p){
    return p->possess;
}
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
/*----------------------------------------------------------------*/
void setAutor(Personne p,FILE*f){
    CLEAR_STDIN
    printf("\nVous allez être invité à choisir l'habilitation de votre compte\n");
    int i;
    char *cmp;
    char *mdp_admin;
    mdp_admin=(char *)malloc(sizeof(char)*21);
    fgets(mdp_admin,21,f);
    printf("%s\n",mdp_admin);
    
    printf("\nCOMPTE USER: Permet utilisaton de la base de données (1) \n");
    printf("COMPTE ADMIN: Permet utilisaton de la base de données et son administration(2)\n");
    printf("\nVeuillez choisir l'habilitation du compte :\n");
    scanf("%d",&i);
    switch(i)
    {
        case 1:
            CLEAR_STDIN
            p->a=0;
            getAutor(p);
            printf("Vous aves choisi d'être USER\n");
            free(mdp_admin);
            mdp_admin=NULL;
            cmp=NULL;
            i=0;
            break;
        case 2:
            CLEAR_STDIN
            cmp=(char *)malloc(sizeof(char)*65);
            printf("Veuillez entrer le mot de passe administrateur :\n");
            fgets(cmp,65,stdin);
            //cmp=chiffrementMdp(cmp);
            printf("cmp=%s\n",cmp);// à utiliser pour tester fct°
            printf("strcmp=%d\n",strcmp(mdp_admin,cmp));// à utiliser pour tester fct°
            
            if(strcmp(mdp_admin,cmp)==0){
                p->a=1;
                getAutor(p);
                printf("Vous êtes habilité en tant qu'administrateur\n");
                free(mdp_admin);
                free(cmp);
                mdp_admin=NULL;
                cmp=NULL;
                i=0;
            }//pb avec strcmp-->initialiser le mot de passe ds le fichier
            else{
                CLEAR_STDIN
                printf("\nERRROR\n");
                printf("Vous allez être redirigé\n");
                i=0;
                free(mdp_admin);
                free(cmp);
                mdp_admin=NULL;
                cmp=NULL;
                setAutor(p,f);
            }
            break;
        default:
            CLEAR_STDIN
            printf("\nERRROR\n");
            printf("Vous allez être redirigé\n");
            i=0;
            free(mdp_admin);
            free(cmp);
            mdp_admin=NULL;
            cmp=NULL;
            setAutor(p,f);
            break;
    }  
}
/*----------------------------------------------------------------*/
/*void setAutor(Personne p,int i){
    p->a=i;
}//version utilisée pour phase de tests*/
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
Personne create_pers(FILE*f){
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
    //setPwd(pers,crypted);
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
   
    //setAutor(pers,1);//version de tests
    setAutor(pers,f);
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
void modif_persAdmin(Personne p,FILE*f){
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
        
        case 8:
            CLEAR_STDIN
            setAutor(p,f);
            break;
            
        default :
            break;
        }
    int u;
    printf(" Continuer les modifications ?\n OUI=1 ?\t NON=0 ?\n");
    scanf("%d",&u);
    if(u==1){
        CLEAR_STDIN
        modif_persAdmin(p,f);
    }
}
/*----------------------------------------------------------------*/
void modif_persUser(Personne p){
    int i;
    printf("\n\n Que voulez-vous modifier ?\n");
    printf("Modifier mot de passe: 1\n Modifier adresse mail: 2\n");
    printf(" Modifier numéro de téléphone: 3\nQuitter: 0\n");
    printf(" \n\nSaisissez votre choix : \n");
    scanf("%d",&i);
    switch(i){
        case 0:
            CLEAR_STDIN
            break;
        case 1:
            CLEAR_STDIN
            modif_pwd(p);
            break;
        case 2:
            CLEAR_STDIN
            modif_mail(p);
            break;
            
        case 3:
            CLEAR_STDIN
            modif_tel(p);
            break;
        default :
            break;
        }
    int u;
    printf(" Continuer les modifications ?\n OUI=1 ?\t NON=0 ?\n");
    scanf("%d",&u);
    if(u==1){
        CLEAR_STDIN
        modif_persUser(p);
    }
}
/*----------------------------------------------------------------*/
