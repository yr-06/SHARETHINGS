#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <crypt.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "../include/chiffrement.h"
#include "../include/personne.h"
#include "../include/parson.h"

#ifndef CLEAR_STDIN
    #define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#endif

#ifndef COLOR
    #define color(param) printf("\033[%sm",param)
#endif

/* Paramètre  Couleur
30 Noir |31 Rouge | 32 Vert | 33 Jaune | 34 Bleu | 35 Magenta | 36 Cyan | 37 Blanc
 
"1" active la haute intensité des caractères.
*/

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


void viderBuffer2() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

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
    FILE *f=fopen("./data/Mtdp_admin.txt", "r");
    viderBuffer2();
    char *cmp;
    char *mdp_admin;
    cmp=(char *)malloc(sizeof(char)*65);
    mdp_admin=(char *)malloc(sizeof(char)*65);
        
    color("33;1");
    printf("\nVous allez être invité à choisir l'habilitation de votre compte\n");
    int i;
    color("35;1");
    printf("\nCOMPTE USER: Permet utilisaton de la base de données (1) \n");
    printf("COMPTE ADMIN: Permet utilisaton de la base de données et son administration(2)\n");
    printf("\nVeuillez choisir l'habilitation du compte :\n");
    color("37");
    scanf("%d",&i);
    viderBuffer2();
    switch(i)
    {
        case 1:
            
            p->a=0;
            color("32;1");
            printf("Vous aves choisi d'être USER\n");
            color("37");
            free(mdp_admin);
            free(cmp);
            mdp_admin=NULL;
            cmp=NULL;
            return;
        case 2:
            
            color("35;1");
            printf("Veuillez entrer le mot de passe administrateur :\n");
            color("37");
            scanf("%s",cmp);
	    viderBuffer2();

            fscanf(f,"%65s",mdp_admin);
            if(strcmp(mdp_admin, chiffrementMdp(cmp))==0){
                p->a=1;
                color("32;1");
                printf("Vous êtes habilité en tant qu'administrateur\n");
                color("37");
                free(mdp_admin);
                free(cmp);
               return;
            }//pb avec strcmp-->initialiser le mot de passe ds le fichier
            else{
                
                color("31;1");
                printf("\nERRROR--Vous allez être redirigé\n");
                color("37");
                free(mdp_admin);
                free(cmp);
                mdp_admin=NULL;
                cmp=NULL;
                setAutor(p);
            }
            break;
        default:
            color("31;1");
            printf("\nERRROR--Vous allez être redirigé\n");
            color("37");
            free(mdp_admin);
            free(cmp);
            mdp_admin=NULL;
            cmp=NULL;
            setAutor(p);
            break;
    }  
}//fonctionne-->goodc
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
void setPers(Personne p, int num,int a ,char*name,char*prenom,char*date,char*id,char*pwd,char*mail,char*tel){
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
    color("33;1");
    printf("Veuillez entrer un nouveau nom en MAJUSCULES:\n");
    color("37");
    fgets(newName,41,stdin);
    
    free(p->nom);
    (p->nom)=(char*)malloc(sizeof(char)*41);
    setName(p,newName);
    return;
}//fonctionne-->goodc
/*----------------------------------------------------------------*/
void modif_prenom(Personne p){
    
    char *newPrenom;
    newPrenom=(char*)malloc(sizeof(char)*33);
    color("33;1");
    printf("Veuillez entrer un nouveau prénom:\n");
    color("37");
    fgets(newPrenom,33,stdin);
    
    free(p->prenom);
    (p->prenom)=(char*)malloc(sizeof(char)*33);
    setPrenom(p,newPrenom);
    return;
}//fonctionne-->goodc
/*----------------------------------------------------------------*/
void modif_naiss(Personne p){
    
    char *date=(char *)malloc(sizeof(char)*21);
    int day,month,year;
     color("33;1");
    printf("Veuillez entrer une nouvelle date de naissance au format JJ-MM-AAAA :\n");
    color("37");
    scanf("%02d-%02d-%4d",&day,&month,&year);
    sprintf(date,"%d/%d/%d",day,month,year);
   
    free(p->date_naiss);
    p->date_naiss=(char *)malloc(sizeof(char)*21);
    setNaiss(p,date);
    return;
 
}//fonctionne-->goodc
/*----------------------------------------------------------------*/
void modif_pwd(Personne p){
   
     char *newPwd;
     char *confirm;
  
     newPwd=(char*)malloc(sizeof(char)*65);
     confirm=(char*)malloc(sizeof(char)*65);
      color("33;1");
     printf("Veuillez entrer un nouveau mot de passe:\n");
     color("37");
     fgets(newPwd,65,stdin);
   
    
    if(strcmp(getPwd(p),chiffrementMdp(newPwd))==0){
        color("31;1");
        printf("Veuillez entrer un mot de passe différent de celui déjà enregistré\n");
        color("37");
        free(newPwd);
        free(confirm);
        CLEAR_STDIN
        modif_pwd(p);
    }else{
         color("33;1");
        printf("\nVeuillez confirmer le nouveau mot de passe:\n");
        color("37");
        fgets(confirm,65,stdin);
        if(strcmp(newPwd,confirm)==0){
            free(p->pwd);
            (p->pwd)=(char*)malloc(sizeof(char)*65);
            setPwd(p,chiffrementMdp(newPwd));
            free(confirm);
            return;
        }else{
            color("33;1");
            printf("Veuillez entrer le même mot de passe pour confirmer la modification\n");
            color("31;1");
            printf("ERROR--Vous allez être rédirigé\n");
            color("37");
            free(newPwd);
            free(confirm);
            CLEAR_STDIN
            modif_pwd(p);
        }
    }    
    
}//fonctionne-->goodc
/*----------------------------------------------------------------*/
void modif_mail(Personne p){
    
    char *newMail;
    newMail=(char*)malloc(sizeof(char)*33);
    color("33;1");
    printf("Veuillez entrer une nouvelle adresse mail :\n");
    color("37");
    fgets(newMail,33,stdin);
    
    free(p->mail);
    (p->mail)=(char*)malloc(sizeof(char)*33);
    setMail(p,newMail);
    return;
}//fonctionne-->goodc
/*----------------------------------------------------------------*/
void modif_tel(Personne p){

    char *newTel;
    newTel=(char*)malloc(sizeof(char)*33);
    color("33;1");
    printf("Veuillez entrer un nouveau numéro de téléphone :\n");
    color("37");
    fgets(newTel,33,stdin);
    
    free(p->tel);
    (p->tel)=(char*)malloc(sizeof(char)*33);
    setTel(p,newTel);
    free(newTel);
    
    return;
}//fonctionne-->goodc
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
    pers->num_account=0;

    char *name;
    name=(char*)malloc(sizeof(char)*41);
    printf("\nVeuillez entrer votre nom en MAJUSCULES:\n");
    scanf("%s",name);
    viderBuffer2();
    setName(pers,name);

    char *prenom;
    prenom=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre prénom :\n");
    scanf("%s",prenom);
    viderBuffer2();
    setPrenom(pers,prenom);

    char *date=(char *)malloc(sizeof(char)*21);
    int day,month,year;
    printf("Veuillez entrer votre date de naissance au format JJ/MM/AAAA :\n");
    scanf("%02d/%02d/%4d",&day,&month,&year);
    sprintf(date,"%d/%d/%d",day,month,year);
    viderBuffer2();
    setNaiss(pers,date);

    
    char *pwd;
    pwd=(char*)malloc(sizeof(char)*65);
    printf("Veuillez entrer votre mot de passe:\n");
    scanf("%s",pwd);
    viderBuffer2();
    setPwd(pers,chiffrementMdp(pwd));

    char *mail;
    mail=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre adresse mail :\n");
    scanf("%s",mail);
    viderBuffer2();
    setMail(pers,mail);

    char *tel;
    tel=(char*)malloc(sizeof(char)*33);
    printf("Veuillez entrer votre numéro de téléphone :\n");
    scanf("%s",tel);
    viderBuffer2();
    setTel(pers,tel);


    setAutor(pers);
    return pers;
}//fonctionne-->permet d'initialiser les champs de la structure Personne-->good c
/*----------------------------------------------------------------*/
char *createIDPers(Personne p){
    char * id = (char *) malloc(sizeof(char)*4);
    id="IDP";
    
    char *num=(char *) malloc(sizeof(char)*8);
    
    sprintf(num,"%d", getNumAccount(p));
    
    char *fullID= (char *) malloc(sizeof(char)*33);
    strcpy(fullID,id);
    strcat( fullID,num);

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
} //fonctionne-->good c

void modif_persAdmin(Personne p){
    int i;
    color("33;1");
    printf("\n\n Que voulez-vous modifier ?\n");
    color("37");
    printf(" Modifier nom: 1\n Modifier prenom: 2\n Modifier date de naissance: 3\n");
    printf(" Modifier mot de passe: 4\n Modifier adresse mail: 5\n");
    printf(" Modifier numéro de téléphone: 6\n Modifier habilitation: 7\n Quitter: 0\n");
    color("33;1");
    printf(" \n\nSaisissez votre choix : \n");
    color("37");
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
    color("33;1");
    printf(" Continuer les modifications ?\n OUI=1 ?\t NON=0 ?\n");
    color("37");
    scanf("%d",&u);
    if(u==1){
        CLEAR_STDIN
        modif_persAdmin(p);
    }
    return;
}//fonctionne-->good c
/*----------------------------------------------------------------*/
void modif_persUser(Personne p){
    int i;
    color("33;1");
    printf("\n\n Que voulez-vous modifier ?\n");
    color("37");
    printf("(1)Modifier mot de passe\n (2)Modifier adresse mail\n");
    printf("(3)Modifier numéro de téléphone \n (0)Quitter\n");
    color("33;1");
    printf(" \n\nSaisissez votre choix : \n");
    color("37");
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
    color("33;1");
    printf(" Continuer les modifications ?\n OUI=1 ?\t NON=0 ?\n");
    color("37");
    scanf("%d",&u);
    if(u==1){
        CLEAR_STDIN
        modif_persUser(p);
    }
    return;
}//fonctionne
/*----------------------------------------------------------------*/

//fonctions pour le JSON
void print_pers_JSON(Personne p){
    char path[64];
    sprintf(path,"./data/Personne/%s.json",getIDPers(p));
    
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
void addPersAnnu_JSON(Personne p){
    FILE *Annuf = NULL;
    Annuf = fopen("./data/Personne/Annuaire.dat","a");
    fprintf(Annuf,"%s,%s,%s \n",strtok(getIDPers(p),"\n"),strtok(getName(p),"\n"),strtok(getPrenom(p),"\n"));
    fclose(Annuf);
}//fonctionne
/*----------------------------------------------------------------*/
Personne LoadPersonne_JSON(char *ID){
    Personne p=initPers();
    JSON_Value *root_value;
    JSON_Object *root_object;
    char path[64];
    sprintf(path,"./data/Personne/%s.json",ID);
    
    root_value = json_parse_file(path);
    root_object = json_value_get_object(root_value);

    int number_compte = (int) json_object_get_number (root_object,"N° de compte");
    int habit = (int) json_object_get_number (root_object,"Habilitation");
   
    char * nom = (char*)json_object_get_string (root_object,"Nom");
    char * prenom = (char*)json_object_get_string (root_object,"Prenom");
    char * date_naissance = (char*)json_object_get_string (root_object,"Date de naissance");
    char * identifiant = (char*)json_object_get_string (root_object,"Identifiant");
    char * mdp = (char*)json_object_get_string (root_object,"Mot de passe");
    char * mail = (char*)json_object_get_string (root_object,"Adresse mail");
    char * tel = (char*)json_object_get_string (root_object,"N° de téléphone");
    
    setPers(p, number_compte, habit, nom, prenom, date_naissance, identifiant, mdp, mail, tel);
    return p;
}//fonctionne
/*----------------------------------------------------------------*/
void suppr_pers_JSON(char *ID){
    char path[64];
    sprintf(path,"./data/Personne/%s.json",ID);
    remove(path);
}//fonctionne

