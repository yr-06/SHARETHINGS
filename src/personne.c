#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <crypt.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "../include/ressources.h"
#include "../include/chiffrement.h"
#include "../include/personne.h"
#include "../include/parson.h"

#ifndef CLEAR_STDIN
    #define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#endif

//structure a initialiser en dynamique
struct s_pers {
    int num_account;//numéro de compte (correspondra aussi à son indice dans Annuaire)
    int a;//int qui definit autorisation ou non d'entrer ds le menu admin
    char *nom;//nom de la personne
    char *prenom;//prenom de la personne
    Date date_naiss;
    char *id;//identifiant de son compte
    char *pwd;//mot de passe lié au compte
    char *mail;//mail de la personne
    char *tel;//numero de telephone de la personne
    int possess;// nbre de ressources dont la personne est proprio
    Liste emprunt;//Liste de Ressources empruntées actuellement par la personne
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
char *getName(Personne p){
    return (p->nom);
}
/*----------------------------------------------------------------*/
char *getPrenom(Personne p){
    return (p->prenom);
}
/*----------------------------------------------------------------*/
Date getNaiss(Personne p){
    return (p->date_naiss);
}
/*----------------------------------------------------------------*/
char *getIDPers(Personne p){
    return (p->id);
}
/*----------------------------------------------------------------*/
char *getPwd(Personne p){
    return (p->pwd);
}
/*----------------------------------------------------------------*/
char *getMail(Personne p){
    return (p->mail);
}   
/*----------------------------------------------------------------*/
char *getTel(Personne p){
    return (p->tel);
}
/*----------------------------------------------------------------*/
int getPossess(Personne p){
    return p->possess;
}
/*----------------------------------------------------------------*/
int getNbPret(Personne p){
	return(p->emprunt->size);
}//consulter le nombre de pret
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
    mdp_admin=(char *)malloc(sizeof(char)*65);
    cmp=(char *)malloc(sizeof(char)*65);
   
    
    printf("\nCOMPTE USER: Permet utilisaton de la base de données (1) \n");
    printf("COMPTE ADMIN: Permet utilisaton de la base de données et son administration(2)\n");
    printf("\nVeuillez choisir l'habilitation du compte :\n");
    scanf("%d",&i);
    switch(i)
    {
        case 1:
            CLEAR_STDIN
            p->a=0;
            printf("Vous aves choisi d'être USER\n");
            return;
        case 2:
            CLEAR_STDIN
           
            fgets(mdp_admin,65,f);
            printf("Mdp_admin=%s\n",mdp_admin);// à utiliser pour tester fct°
        
            printf("Veuillez entrer le mot de passe administrateur :\n");
            fgets(cmp,65,stdin);
            //cmp=chiffrementMdp(cmp);
            
            printf("cmp=%s\n",cmp);// à utiliser pour tester fct°
            printf("strcmp=%d\n",strcmp(mdp_admin,cmp));// à utiliser pour tester fct°
            
            if(strcmp(mdp_admin,cmp)==0){
                p->a=1;
                printf("Vous êtes habilité en tant qu'administrateur\n");
               return;
            }//pb avec strcmp-->initialiser le mot de passe ds le fichier
            else{
                CLEAR_STDIN
                printf("\nERRROR\n");
                printf("Vous allez être redirigé\n");
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
            free(mdp_admin);
            free(cmp);
            mdp_admin=NULL;
            cmp=NULL;
            setAutor(p,f);
            break;
    }  
}
/*----------------------------------------------------------------*/
void setName(Personne p,char*name){
    strcpy(p->nom,name);
}
/*----------------------------------------------------------------*/
void setPrenom(Personne p,char*prenom){
    strcpy(p->prenom,prenom);
}
/*----------------------------------------------------------------*/
void setNaiss(Personne p,Date d){
    p->date_naiss=d;

}
/*----------------------------------------------------------------*/
void setIDPers(Personne p,char*id){
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
        CLEAR_STDIN
        modif_name(p);
    }else{
        free(p->nom);
        (p->nom)=(char*)malloc(sizeof(char)*41);
        setName(p,newName);
        return;
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
        CLEAR_STDIN
        modif_prenom(p);
    }else{
        free(p->prenom);
        (p->prenom)=(char*)malloc(sizeof(char)*33);
        setPrenom(p,newPrenom);
        free(newPrenom);
        return;
    }    
}
/*----------------------------------------------------------------*/
void modif_naiss(Personne p){
    Date newDate=(Date)malloc(sizeof(struct tm));
    
    int day,month,year;
    
    char *naiss;
    naiss=(char*)malloc(sizeof(char)*21);
    strftime(naiss,21,"%d/%m/%Y",getNaiss(p));

    char*newNaiss;
    newNaiss=(char*)malloc(sizeof(char)*21);
    
    printf("Veuillez entrer une nouvelle date de naissance au format JJ-MM-AAAA :\n");
    scanf("%02d-%02d-%4d",&day,&month,&year);
   
    newDate->tm_mday = day;
    newDate->tm_mon = month-1;  
    newDate->tm_year =year-1900;
     
    strftime(newNaiss,21,"%d/%m/%Y",newDate);
    //printf("naiss=%s\nnewNaiss=%s\n",naiss,newNaiss);
      
   // printf("strcmp=%d\n",strcmp(naiss,newNaiss));
    if(strcmp(naiss,newNaiss)==0){
        printf("Veuillez entrer une date de naissance différente de celle déjà enregistrée\n");
        free(newNaiss);
        free(naiss);
        CLEAR_STDIN
        modif_naiss(p);
    }else{
        
        free(p->date_naiss);
        p->date_naiss=(Date)malloc(sizeof(struct tm));
        setNaiss(p,newDate);
        free(newNaiss);
        free(naiss);
        return;
    }    
 
}
/*----------------------------------------------------------------*/
void modif_id(Personne p){
   
    char *id;
    char*newID;
    id=(char*)malloc(sizeof(char)*33);
    id=getIDPers(p);
    
    newID=(char*)malloc(sizeof(char)*33);
    
    printf("Veuillez entrer un nouvel identifiant:\n");
    fgets(newID,33,stdin);
    
   
    if(strcmp(id,newID)==0){
        printf("Veuillez entrer un identifiant différent de celui déjà enregistré\n");
        free(newID);
        free(id);
        CLEAR_STDIN
        modif_id(p);
    }else{
         free(p->id);
         (p->id)=(char*)malloc(sizeof(char)*33);
         setIDPers(p,id);
         free(id);
         return;
    }    
}
/*----------------------------------------------------------------*/
void modif_pwd(Personne p){
    
     char *pwd;//déjà crypté
     char *newPwd;
     char *confirm;
     //char *crypted;-->pour crypter confirm qui est pareil que newPwd
     
     pwd=(char*)malloc(sizeof(char)*65);
     pwd=getPwd(p);
     
     newPwd=(char*)malloc(sizeof(char)*65);
     confirm=(char*)malloc(sizeof(char)*65);
     //crypted=(char*)malloc(sizeof(char)*65);
     
    printf("Veuillez entrer un nouveau mot de passe:\n");
    fgets(newPwd,65,stdin);
    
    //crypted=chiffrementMdp(newPwd);
    
    if(strcmp(pwd,newPwd)==0){
        //comparer normalement avec crypted si fct°chiffrementMdp() marche-->strcmp(pwd,crypted);
        printf("Veuillez entrer un mot de passe différent de celui déjà enregistré\n");
        free(pwd);
        free(newPwd);
        free(confirm);
        //free(crypted);
        CLEAR_STDIN
        modif_pwd(p);
    }else{
        printf("\nVeuillez confirmer le nouveau mot de passe:\n");
        fgets(confirm,65,stdin);
        if(strcmp(newPwd,confirm)==0){
            free(p->pwd);
            (p->pwd)=(char*)malloc(sizeof(char)*65);
            setPwd(p,newPwd);//normalement setPwd(p,crypted);
            return;
        }else{
            printf("Veuillez entrer le même mot de passe pour confirmer la modification\n");
            printf("Vous allez être rédirigé\n");
            free(pwd);
            free(newPwd);
            //free(crypted);
            //free(newCrypted);
            free(confirm);
            CLEAR_STDIN
            modif_pwd(p);
        }
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
        CLEAR_STDIN
        modif_mail(p);
    }else{
        free(p->mail);
        (p->mail)=(char*)malloc(sizeof(char)*33);
        setMail(p,newMail);
        free(newMail);
        return;
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
        CLEAR_STDIN
        modif_tel(p);
    }else{
        free(p->tel);
        (p->tel)=(char*)malloc(sizeof(char)*33);
        setTel(p,newTel);
        free(newTel);
        return;
    }
}
/*----------------------------------------------------------------*/
//Fonction sur les manipulations de personnes
Personne initPers(){
    Personne pers=(Personne)malloc(sizeof(struct s_pers));
    (pers->nom)= (char*)malloc(sizeof(char)*41);
    (pers->prenom)=(char*)malloc(sizeof(char)*33);
    (pers->date_naiss) =(Date)malloc(sizeof(struct tm));
    (pers->id)=(char*)malloc(sizeof(char)*33);
    (pers->pwd)=(char*)malloc(sizeof(char)*65);
    (pers->mail)=(char*)malloc(sizeof(char)*33);
    (pers->tel)=(char*)malloc(sizeof(char)*33);
    pers->emprunt=new_list();
    return pers;
}
/*----------------------------------------------------------------*/
Personne create_pers(FILE*f){
    Personne pers=initPers();
    
    pers->possess=0;
    
    
    CLEAR_STDIN
    char *name;
    name=(char*)malloc(sizeof(char)*41);
    printf("\n\nVeuillez entrer votre nom :\n");
    fgets(name,41,stdin);
    setName(pers,name);
    free(name);
    
    CLEAR_STDIN
    char *prenom;
    prenom=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre prénom :\n");
    fgets(prenom,33,stdin);
    setPrenom(pers,prenom);
    free(prenom);
   
    CLEAR_STDIN
    
    Date date=(Date)malloc(sizeof(struct tm));
    int day,month,year;
    
    printf("Veuillez entrer votre date de naissance au format JJ-MM-AAAA :\n");
    scanf("%02d-%02d-%4d",&day,&month,&year);

    date->tm_mday = day;
    date->tm_mon = month-1;  
    date->tm_year =year-1900;
    
    setNaiss(pers,date);
   
    CLEAR_STDIN
    char *id;
    id=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre identifiant:\n");
    fgets(id,33,stdin);
    setIDPers(pers,id);
    free(id);
    
    CLEAR_STDIN
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
   
    CLEAR_STDIN
    char *mail;
    mail=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre adresse mail :\n");
    fgets(mail,33,stdin);
    setMail(pers,mail);
    free(mail);
    
    CLEAR_STDIN
    char *tel;
    tel=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre numéro de téléphone :\n");
    fgets(tel,33,stdin);
    setTel(pers,tel);
    free(tel);
   
    CLEAR_STDIN
    setAutor(pers,f);
    return pers;
}//permet d'initialiser les champs de la structure Personne
/*----------------------------------------------------------------*/
void affich_pers(Personne p){
    printf("\n--------Voici le récapitulatif des données de ce compte:-------\n");
    printf("N° de compte :%d\n", getNumAccount(p));
    printf("Nom :%s\n", getName(p));
    printf("Prenom :%s\n", getPrenom(p));
    
    char*cdate;
    cdate=(char*)malloc(sizeof(char)*21);
    strftime(cdate,21,"%d/%m/%Y",getNaiss(p));
    printf("Date de naissance :%s\n",cdate);
    
    printf("\n");
    printf("Identifiant :%s\n", getIDPers(p));
    printf("Mot de passe :%s\n", getPwd(p));
    printf("\n");
    printf("Adresse mail :%s\n", getMail(p));
    printf("N° de téléphone :%s\n", getTel(p));
    //printf("Nombre d'emprunt actuel :%d\n", getNbPret(p));
    printf("Nombre de ressources créées:%d\n",getPossess(p));
    if(getAutor(p)==1){
        printf("--------Ce compte est habilité à se connecter en tant qu'administrateur----------\n");
    }else{
        printf("-----Ce compte est habilité à se connecter en tant que simple utilisateur-------\n");
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
    return;
}
/*----------------------------------------------------------------*/

void print_pers_JSON(Personne p,FILE*f){
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    char *serialized_string = NULL;
    
    json_object_set_number(root_object, "N° de compte",getNumAccount(p));
    json_object_set_string(root_object, "Nom",getName(p));
    json_object_set_string(root_object, "Prenom",getPrenom(p));
    
    char*date;
    date=(char*)malloc(sizeof(char)*21);
    strftime(date,21,"%d/%m/%Y",getNaiss(p));
    
    json_object_set_string(root_object,"Date de naissance",date);
    json_object_set_string(root_object,"Identifiant",getIDPers(p));
    json_object_set_string(root_object,"Mot de passe",getPwd(p));
    json_object_set_string(root_object,"Adresse mail",getMail(p));
    json_object_set_string(root_object,"N° de téléphone",getTel(p));
    if(getAutor(p)==1){
        json_object_set_string(root_object,"Habilitation","ADMINISTRATEUR");
     
    }else{
        json_object_set_string(root_object,"Habilitation","USER");
    }
    json_object_set_number(root_object, "Nombre d'emprunt actuel",getNbPret(p));
    json_object_set_number(root_object, "Nombre de ressources créées",getPossess(p));
    if(getNbPret(p)>0){
        int i;
        Elementl current_l=emprunt->head;
        for(i=0,i<p->emprunt->size,i++){
            current_l=current_l->next;
        }
    }//-->faire en sorte que chaque ressource s'affiche
    serialized_string = json_serialize_to_string_pretty(root_value);
    fseek(f,0,SEEK_END);
    fprintf(f,"%s",serialized_string);
    json_free_serialized_string(serialized_string);
    json_value_free(root_value);
    
}//fonctionne-->affichage de \n et /--> possibilité de s'en débarasser
int main(int argc, char *argv[]){
    FILE *f=fopen("../data/Mtdp_admin.txt", "r");
    FILE *g=fopen("../data/Annuaire.json","w+");
    Personne p= create_pers(f);
    affich_pers(p);
    print_pers_JSON(p,g);

}
