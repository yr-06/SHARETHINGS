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
    char *date_naiss;//date de naissance de la personne
    char *id;//identifiant de son compte
    char *pwd;//mot de passe lié au compte
    char *mail;//mail de la personne
    char *tel;//numero de telephone de la personne
};


//getters

int getNumAccount(Personne p){
    return p->num_account;
}//fonctionne
/*----------------------------------------------------------------*/
int getAutor(Personne p){
    return p->a;
}//fonctionne
/*----------------------------------------------------------------*/
char *getName(Personne p){
    return (p->nom);
}//fonctionne
/*----------------------------------------------------------------*/
char *getPrenom(Personne p){
    return (p->prenom);
}//fonctionne
/*----------------------------------------------------------------*/
char *getNaiss(Personne p){
    return (p->date_naiss);
}//fonctionne
/*----------------------------------------------------------------*/
char *getIDPers(Personne p){
    return (p->id);
}//fonctionne
/*----------------------------------------------------------------*/
char *getPwd(Personne p){
    return (p->pwd);
}//fonctionne
/*----------------------------------------------------------------*/
char *getMail(Personne p){
    return (p->mail);
}//fonctionne  
/*----------------------------------------------------------------*/
char *getTel(Personne p){
    return (p->tel);
}//fonctionne
/*----------------------------------------------------------------*/

 //setters
void setNumAccount(Personne p, int i){
  p->num_account=i;
}
/*----------------------------------------------------------------*/
void setAutor(Personne p){
    FILE *f=fopen("../data/Mtdp_admin.txt", "r");
    CLEAR_STDIN
    printf("\nVous allez être invité à choisir l'habilitation de votre compte\n");
    int i;
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
            char *cmp;
            char *mdp_admin;
            cmp=(char *)malloc(sizeof(char)*65);
            mdp_admin=(char *)malloc(sizeof(char)*65);
            
            //plante à partir de là 
            printf("Veuillez entrer le mot de passe administrateur :\n");
            fgets(cmp,65,stdin);
            
            printf("cmp=%s\n",cmp);// à utiliser pour tester fct°
            
            fscanf(f,"%65s",mdp_admin);
            printf("Mdp_admin=%s\n",mdp_admin);// à utiliser pour tester fct°
        
           
            printf("strcmp=%d\n",strcmp(mdp_admin, chiffrementMdp(cmp)));// à utiliser pour tester fct°
            
            if(strcmp(mdp_admin, chiffrementMdp(cmp))==0){
                p->a=1;
                printf("Vous êtes habilité en tant qu'administrateur\n");
                free(mdp_admin);
                free(cmp);
               return;
            }//pb avec strcmp-->initialiser le mot de passe ds le fichier
            else{
                CLEAR_STDIN
                printf("\nERRROR--Vous allez être redirigé\n");
                free(mdp_admin);
                free(cmp);
                mdp_admin=NULL;
                cmp=NULL;
                setAutor(p);
            }
            break;
        default:
            CLEAR_STDIN
            printf("\nERRROR--Vous allez être redirigé\n");
            free(mdp_admin);
            free(cmp);
            mdp_admin=NULL;
            cmp=NULL;
            setAutor(p);
            break;
    }  
}//fonctionne
/*----------------------------------------------------------------*/
void setName(Personne p,char *name){
    strcpy(p->nom,name);
}
/*----------------------------------------------------------------*/
void setPrenom(Personne p,char *prenom){
    strcpy(p->prenom,prenom);
}//fonctionne
/*----------------------------------------------------------------*/
void setNaiss(Personne p,char *date){
    strcpy(p->date_naiss,date);
}//fonctionne
/*----------------------------------------------------------------*/
void setIDPers(Personne p,char *id){
   strcpy(p->id,id);
}//fonctionne
/*----------------------------------------------------------------*/
void setPwd(Personne p,char *pwd){
    strcpy(p->pwd,pwd);
}//fonctionne
/*----------------------------------------------------------------*/
void setMail(Personne p,char *mail){
    strcpy(p->mail,mail);
} //fonctionne 
/*----------------------------------------------------------------*/
void setTel(Personne p,char *tel){
    strcpy(p->tel,tel);
    
}//fonctionne
/*----------------------------------------------------------------*/
Personne setPers(Personne p, int num,int a ,char*name,char*prenom,char*date,char*id,char*pwd,char*mail,char*tel){
    setNumAccount(p,num);
    setName(p,name);
    setPrenom(p,prenom);
    p->a=a;
    setNaiss(p,date);
    setIDPers( p,id);
    setPwd(p,pwd);
    setMail(p,mail);
    setTel(p,tel);
}//fonctionne

//Fonctions permettants de modifier données d'une personne

void modif_name(Personne p){
    char *newName;
    newName=(char*)malloc(sizeof(char)*41);
    
    printf("Veuillez entrer un nouveau nom:\n");
    fgets(newName,41,stdin);
    
    free(p->nom);
    (p->nom)=(char*)malloc(sizeof(char)*41);
    setName(p,newName);
    return;
}//fonctionne
/*----------------------------------------------------------------*/
void modif_prenom(Personne p){
    
    char *newPrenom;
    newPrenom=(char*)malloc(sizeof(char)*33);
    
    printf("Veuillez entrer un nouveau prénom:\n");
    fgets(newPrenom,33,stdin);
    
    free(p->prenom);
    (p->prenom)=(char*)malloc(sizeof(char)*33);
    setPrenom(p,newPrenom);
    return;
}//fonctionne
/*----------------------------------------------------------------*/
void modif_naiss(Personne p){
    
    char *date=(char *)malloc(sizeof(char)*21);
    int day,month,year;

    printf("Veuillez entrer une nouvelle date de naissance au format JJ-MM-AAAA :\n");
    scanf("%02d-%02d-%4d",&day,&month,&year);
    sprintf(date,"%d/%d/%d",day,month,year);
   
    free(p->date_naiss);
    p->date_naiss=(char *)malloc(sizeof(char)*21);
    setNaiss(p,date);
    return;
 
}//fonctionne
/*----------------------------------------------------------------*/
void modif_pwd(Personne p){
   
     char *newPwd;
     char *confirm;
  
     newPwd=(char*)malloc(sizeof(char)*65);
     confirm=(char*)malloc(sizeof(char)*65);
     
     printf("Veuillez entrer un nouveau mot de passe:\n");
     fgets(newPwd,65,stdin);
   
    
    if(strcmp(getPwd(p),chiffrementMdp(newPwd))==0){
        printf("Veuillez entrer un mot de passe différent de celui déjà enregistré\n");
        free(newPwd);
        free(confirm);
        CLEAR_STDIN
        modif_pwd(p);
    }else{
        printf("\nVeuillez confirmer le nouveau mot de passe:\n");
        fgets(confirm,65,stdin);
        if(strcmp(newPwd,confirm)==0){
            free(p->pwd);
            (p->pwd)=(char*)malloc(sizeof(char)*65);
            setPwd(p,chiffrementMdp(newPwd));
            free(confirm);
            return;
        }else{
            printf("Veuillez entrer le même mot de passe pour confirmer la modification\n");
            printf("Vous allez être rédirigé\n");
            free(newPwd);
            free(confirm);
            CLEAR_STDIN
            modif_pwd(p);
        }
    }    
    
}//fonctionne
/*----------------------------------------------------------------*/
void modif_mail(Personne p){
    
    char *newMail;
    newMail=(char*)malloc(sizeof(char)*33);
    
    printf("Veuillez entrer une nouvelle adresse mail :\n");
    fgets(newMail,33,stdin);
    
    free(p->mail);
    (p->mail)=(char*)malloc(sizeof(char)*33);
    setMail(p,newMail);
    return;
}//fonctionne
/*----------------------------------------------------------------*/
void modif_tel(Personne p){

    char *newTel;
    newTel=(char*)malloc(sizeof(char)*33);
    
    printf("Veuillez entrer un nouveau numéro de téléphone :\n");
    fgets(newTel,33,stdin);
    
    free(p->tel);
    (p->tel)=(char*)malloc(sizeof(char)*33);
    setTel(p,newTel);
    free(newTel);
    
    return;
}//fonctionne
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
    
    return pers;
}
/*----------------------------------------------------------------*/
Personne create_pers(){
    Personne pers=initPers();
    
    CLEAR_STDIN
    char *name;
    name=(char*)malloc(sizeof(char)*41);
    printf("\nVeuillez entrer votre nom en MAJUSCULES:\n");
    fgets(name,41,stdin);
    setName(pers,name);
   
    
    CLEAR_STDIN
    char *prenom;
    prenom=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre prénom :\n");
    fgets(prenom,33,stdin);
    setPrenom(pers,prenom);
   
   
    CLEAR_STDIN
    
    char *date=(char *)malloc(sizeof(char)*21);
    int day,month,year;
    
    printf("Veuillez entrer votre date de naissance au format JJ-MM-AAAA :\n");
    scanf("%02d-%02d-%4d",&day,&month,&year);
    

    char *nday=(char *) malloc(sizeof(char)*6);
    char *nmonth=(char *) malloc(sizeof(char)*3);
    sprintf(nmonth,"%d",month);
    sprintf(nday,"%d",day);
    
    setIDPers(pers,strcat(nday,nmonth));
    
    sprintf(date,"%d/%d/%d",day,month,year);
    setNaiss(pers,date);
   
    CLEAR_STDIN
    char *pwd;
    pwd=(char*)malloc(sizeof(char)*65);
    printf("Veuillez entrer votre mot de passe:\n");
    fgets(pwd,65,stdin);
    setPwd(pers,chiffrementMdp(pwd));
  
    CLEAR_STDIN
    char *mail;
    mail=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre adresse mail :\n");
    fgets(mail,33,stdin);
    setMail(pers,mail);
   
    
    CLEAR_STDIN
    char *tel;
    tel=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre numéro de téléphone :\n");
    fgets(tel,33,stdin);
    setTel(pers,tel);
   
    CLEAR_STDIN
    setAutor(pers);
    return pers;
}//fonctionne-->permet d'initialiser les champs de la structure Personne
/*----------------------------------------------------------------*/
char *createIDPers(Personne p){
    char * id = (char *) malloc(sizeof(char)*4);
    id="IDP";
    
    char *num=(char *) malloc(sizeof(char)*8);
    
    sprintf(num,"%d", getNumAccount(p));
    
    char *subname=(char *) malloc(sizeof(char)*3);
    subname=strncpy(subname,getName(p),3);
    
    char *subfname=(char *) malloc(sizeof(char)*1);
    subfname=strncpy(subfname,getPrenom(p),1);
    
    
    
    char *fullID= (char *) malloc(sizeof(char)*33);
    strcpy(fullID,id);
    strcat( fullID,num);
    strcat( fullID,subname);
    strcat( fullID,subfname);
    strcat( fullID,getIDPers(p));
    
    free(p->id);
    (p->id)=(char *) malloc(sizeof(char)*33);

    return fullID;

}//fonctionne
/*----------------------------------------------------------------*/
void affich_pers(Personne p){
    printf("\n--------Voici le récapitulatif des données de ce compte:-------\n");
    printf("N° de compte :%d\n", getNumAccount(p));
    printf("Nom :%s\n", getName(p));
    printf("Prenom :%s\n", getPrenom(p));
  
    printf("Date de naissance :%s\n",getNaiss(p));
    
    printf("\n");
    printf("Identifiant :%s\n", getIDPers(p));
    printf("Mot de passe :%s\n", getPwd(p));
    printf("\n");
    printf("Adresse mail :%s\n", getMail(p));
    printf("N° de téléphone :%s\n", getTel(p));
    
    if(getAutor(p)==1){
        printf("--------Ce compte est habilité à se connecter en tant qu'administrateur----------\n");
    }else{
        printf("-----Ce compte est habilité à se connecter en tant que simple utilisateur-------\n");
    }
} //fonctionne
void modif_persAdmin(Personne p){
    int i;
    printf("\n\n Que voulez-vous modifier ?\n");
    printf(" Modifier nom: 1\n Modifier prenom: 2\n Modifier date de naissance: 3\n");
    printf(" Modifier mot de passe: 4\n Modifier adresse mail: 5\n");
    printf(" Modifier numéro de téléphone: 6\n Modifier habilitation: 7\n Quitter: 0\n");
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
            modif_pwd(p);
            break;
        
        case 5:
            CLEAR_STDIN
            modif_mail(p);
            break;
            
        case 6:
            CLEAR_STDIN
            modif_tel(p);
            break;
        
        case 7:
            CLEAR_STDIN
            setAutor(p);
            break;
            
        default :
            break;
        }
    int u;
    printf(" Continuer les modifications ?\n OUI=1 ?\t NON=0 ?\n");
    scanf("%d",&u);
    if(u==1){
        CLEAR_STDIN
        modif_persAdmin(p);
    }
    return;
}//fonctionne
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
}//fonctionne
/*----------------------------------------------------------------*/

void print_pers_JSON(Personne p){
    char path[64];
    sprintf(path,"../data/Personne/%s.json",getIDPers(p));
    
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    char *serialized_string = NULL;
    FILE *fjson = NULL;

    fjson = fopen(path,"w+");
    
    json_object_set_number(root_object, "N° de compte",getNumAccount(p));
    json_object_set_string(root_object, "Nom",getName(p));
    json_object_set_string(root_object, "Prenom",getPrenom(p));
    json_object_set_number(root_object, "Habilitation",getAutor(p));
    
    json_object_set_string(root_object,"Date de naissance",getNaiss(p));
    json_object_set_string(root_object,"Identifiant",getIDPers(p));
    json_object_set_string(root_object,"Mot de passe",getPwd(p));
    json_object_set_string(root_object,"Adresse mail",getMail(p));
    json_object_set_string(root_object,"N° de téléphone",getTel(p));
    
    serialized_string = json_serialize_to_string_pretty(root_value);
    fprintf(fjson,"%s",serialized_string);
    fclose(fjson);
    json_free_serialized_string(serialized_string);
    json_value_free(root_value);
}//fonctionne
/*----------------------------------------------------------------*/
void addPersAnnu(Personne p){
    FILE *Annuf = NULL;
    Annuf = fopen("../data/Personne/Annuaire.dat","a");
    //fprintf(Annuf,"%s,%s,%s,%s \n",getIDPers(p),getName(p),getPrenom(p),getPwd(p));
    fprintf(Annuf,"%s\n",getIDPers(p));
    fclose(Annuf);
}//fonctionne
/*----------------------------------------------------------------*/
void removePersAnnu(Personne p){
	//char line[128];
    char line[33];
	//char *id;
    //char *pchain;

	FILE * file = fopen("../data/Personne/Annuaire.dat","r");
    FILE * Newfile = fopen("../data/Personne/NewAnnuaire.dat","w");
    rewind(file);
    rewind(Newfile);

    if(file!= NULL){
        while (!feof(file) && (fgets(line,33, file) != NULL)){
            //pchain=(char*)malloc(sizeof(char)*129);
            //strcpy(pchain,line);
			//id = strtok(line,",");
			
            if(strcmp(line,getIDPers(p))!=0){
                fprintf(Newfile,"%s \n",line);
				//fprintf(Newfile,"%s \n",pchain);
                //free(pchain);
			}
			/*while ( id!= NULL ) {
                id= strtok( NULL,",");
                
            }*/
        }
    }else{
        fprintf(stderr, "Erreur :Impossible d'ouvrir le fichier.\n");
		exit(EXIT_FAILURE);
    }
    fclose(file);
    fclose(Newfile);

    remove("../data/Personne/Annuaire.dat");
    rename("../data/Personne/NewAnnuaire.dat","../data/Personne/Annuaire.dat");
}//à revoir
/*----------------------------------------------------------------*/
Personne LoadPersonne(char *ID){
    Personne p=initPers();
    JSON_Value *root_value;
    JSON_Object *root_object;
    char path[64];
    sprintf(path,"../data/Personne/%s.json",ID);
    
    
    root_value = json_parse_file(path);
    root_object = json_value_get_object(root_value);

   
    p=setPers(p,(int)json_object_get_number (root_object,"N° de compte"),(int)json_object_get_number (root_object,"Habilitation"),(char*)json_object_get_string (root_object,"Nom"),(char*)json_object_get_string (root_object,"Prenom"),(char*)json_object_get_string (root_object,"Date de naissance"),(char*)json_object_get_string (root_object,"Identifiant"),(char*)json_object_get_string (root_object,"Mot de passe"),(char*)json_object_get_string (root_object,"Adresse mail"),(char*)json_object_get_string (root_object,"N° de téléphone"));
    return p;
}//fonctionne

/*
Ressource setRess(Ressource r,char *type,char *nom,char *ID,char *dropBy,char *takenBy,char *date_d,char *date_f){
    setType(r,type);
    setNom(r ,nom);
    setID_r(r,ID);
    setDropBy(r,dropBy);
    setTakenBy(r,takenBy);
    setDateDeb(r,date_d);
    setDateFin(r,date_f);
}//à tester
void print_ress_JSON(Ressource r){
    char path[64];
    sprintf(path,"../data/Ressources/%s.json",getID_r(r));
    
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    char *serialized_string = NULL;
    FILE *fjson = NULL;

    fjson = fopen(path,"w+");
    
    json_object_set_string(root_object, "Type",getTypeRessource(r));
    json_object_set_string(root_object, "Nom", getNom(r));
    json_object_set_string(root_object, "ID",getID_r(r));
    json_object_set_string(root_object, "Propriétaire",getDropBy(r));
    json_object_set_number(root_object, "Statut",isDispo(r));
    json_object_set_string(root_object, "Emprunté par",getTakenBy(r));
    json_object_set_string(root_object,"Date de début du pret", getDateDebut(r));
    json_object_set_string(root_object,"Date de fin du pret",getDateFin(r));
  
    serialized_string = json_serialize_to_string_pretty(root_value);
    fprintf(fjson,"%s",serialized_string);
    fclose(fjson);
    json_free_serialized_string(serialized_string);
    json_value_free(root_value);
   
}//à tester
void addRessListe(Ressource r){
    FILE *Listef = NULL;
    Listef = fopen("../data/Ressources/Liste.dat","a");
    fprintf(Listef,"%s,%s,%s,%s \n",getID_r(r),getTypeRessource(r),getNom(r),getDropBy(r));
    fclose(Listef);
}//à tester
void removeRessListe(Ressource r){
	char line[128];
	char *id;
    char *pchain;

	FILE * file = fopen("../data/Ressources/Liste.dat","r");
    FILE * Newfile = fopen("../data/Ressources/NewListe.dat","w");

    if(file!= NULL){
        while (fgets(line, 128, file) != NULL){
            pchain=(char*)malloc(sizeof(char)*129);
            strcpy(pchain,line);
			id = strtok(line,",");
            if(strcmp(id,getID_r(r))!=0){
				fprintf(Newfile,"%s \n",pchain);
                free(pchain);
			}
        }
    }else{
        fprintf(stderr, "Erreur :Impossible d'ouvrir le fichier.\n");
		exit(EXIT_FAILURE);
    }
    fclose(file);
    fclose(Newfile);

    remove("../data/Ressources/Liste.dat");
    rename("../data/Ressources/NewListe.dat","../data/Ressources/Liste.dat");
}//à tester
Ressource LoadRessource(char *ID){
    Ressource r=initRessource();
    JSON_Value *root_value;
    JSON_Object *root_object;
    char path[64];
    sprintf(path,"../data/Ressources/%s.json",ID);
    
    root_value = json_parse_file(path);
    root_object = json_value_get_object(root_value);
   
    r=setRess(r,(char*)json_object_get_string (root_object,"Type"),(char*)json_object_get_string (root_object,"Nom"),(char*)json_object_get_string (root_object,"ID"),(char*)json_object_get_string (root_object,"Propriétaire"),(char*)json_object_get_string (root_object,"Emprunté par"),(char*)json_object_get_string (root_object,"Date de début du pret"),(char*)json_object_get_string (root_object,"Date de fin du pret"));
    return r;
}//à tester*/


int main(int argc, char *argv[]){
    FILE *f=fopen("../data/Mtdp_admin.txt", "r");
    Personne p=create_pers(f);
    p->num_account=1000;
    setIDPers(p,createIDPers(p));
    affich_pers(p);
    print_pers_JSON(p);
    addPersAnnu(p);
    
}
