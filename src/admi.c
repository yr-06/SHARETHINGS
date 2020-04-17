#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>
#include "../include/chiffrement.h"
#include "../include/admi.h"
#include "../include/ressources.h"
#include "../include/personne.h"
#include "../include/annuaire.h"

/*modif_pers opérationnel*/

void get_adm(FILE *f,FILE*g,Annuaire annu,Personne p){
    int i=get_autor(p);
    switch(i){
        case 0:
         printf("Vous n'avez pas les habilitations nécessaire pour continuer\n");
        case 1:
            printf("Vous êtes habilité à vous connecter en tant qu'administrateur\n");
            get_mdp(f,g,annu,p);
    }
}

int get_mdp_admin(FILE*f,FILE*g,Annuaire annu,Personne p){
    if(f==NULL){
        init_mtp_admin(f);
        get_mdp(f,p);
    }
    char*mdp;
    char*c;
    mdp=(char*)malloc(sizeof(char)*65);
    c=(char*)malloc(sizeof(char)*65);
    fscanf(f,"%65s",mdp);
    printf("Veuillez entrer le mot de passe administrateur :\n");
    fgets(c,65,stdin);
    c=chiffrementMdp(c);
    int n=strcmp(mdp,c);
  if (n==0){
      //welcomeAdmin(p);
       printf("Bienvenue %s %s dans le menu administrateur!\n",getName(p),getPrenom(p));
       printf("Que voulez-vous faire ?\n");
       printf("Ajouter un usager: 1\n Modifier les données d'un usager: 2\n Supprimer un usager: 3\n");printf("Afficher les données d'un usager: 4\n Afficher la liste des usagers:5\n Quitter: 0\n");
  
      choix_admin(annu,f,g);
        return 0;
    }
    int i;
    printf("Mot de passe incorrect. Réessayez?\n")
    printf("OUI= 1 ?\t NON=0 ?\n");
    scanf("%d",&i);
    if(i==1){
        get_mdp(f,p);
    }
    else{
        return 1;
    }   
}

void init_mtp_admin(FILE *f){
    char*pwd;
    pwd=(char*)malloc(sizeof(char)*65);
    printf("Veuillez initialiser le mot de passe administrateur:");
    fgets(pwd,65,stdin);
    fprintf(f,"%s",chiffrementMdp(pwd));
}// intitialise mot de passe administrateur si f=NULL


/*void add_ress(Personne p, Liste base){
    Elementl lr=(Elementl)malloc(sizeof(s_elementl));
    Ressource ress=(Ressource)malloc(sizeof(s_ressource));
    char*type;
    char*name;
    ress->nom_proprio=p->nom;
    ress->prenom_proprio=p->prenom_proprio;
    printf("Veuillez entrer le type de votre ressource :");
    scanf("%s",&type);
    printf("\nVeuillez entrer le nom de votre ressource :");
    scanf("%s",&name);
    ress->nom=name;
    ress->type=type;
    r->t=0;
    //ajouter instruction pour initialiser dates de pret, nom de l'emprunteur
    lr->r->ress;
    lr->i=i++;
    int i=base->size;
    push_bl(base,i,lr);
}
void modif_pers(Personne p,FILE*f){
    int i;
    printf("\n\n Que voulez-vous modifier ?\n")
    printf(" Modifier nom: 1\n Modifier prenom: 2\n Modifier date de naissance: 3\n");
    printf(" Modifier identifiant: 4\n Modifier mot de passe: 5\n Modifier adresse mail: 6\n");
    printf(" Modifier numéro de téléphone: 7\n Modifier habilitation: 8\n Quitter: 0\n");
    printf(" Saisissez votre choix : \n");
    scanf("%d",&i);
    switch (i)
    {
    case 0:
        break;
    case 1:
        modif_name(p);
        break;
    case 2:
        modif_prenom(p);
        break;
    case 3:
        modif_naiss(p);
        break;
    case 4:
       modif_id(p);
       break;
    case 5:
        modif_pwd(p);
        break;
    case 6:
        modif_mail(p);
        break;
    case 7:
        modif_tel(p);
        break;
    case 8:
        set_autor(p,f);
        break;
    
    default:
        break;
    }
    int u;
    printf(" Continuer les modifications ?\n OUI=1 ?\t NON=0 ?\n");
    scanf("%d",&u);
    if(u==1){
        modif_pers(p,f);
    }
}*/

void choix_admin(Annuaire annu,FILE*f,FILE*g){
    int d;
    printf("Saisissez votre choix : \n");
    scanf("%d",&d);
    switch(d){
    case 0:
        printf("Vous allez être redirigé\n");
        break;
    case 1:
        annu=createAccount(annu,f);
        break;

    case 2:
        char*m;
        m=(char*)malloc(sizeof(char)*33);
        printf("Veuillez entrer l'identifiant du compte que vous souhaitez modifier:\n");
        fgets(m,33,stdin);
        Personne pat=search_pers(annu,m);
        affich_pers(pat);
        modif_annuaireAdmin(annu,pat,f);
        break;

    case 3:
        char*m;
        m=(char*)malloc(sizeof(char)*33);
        printf("Veuillez entrer l'identifiant du compte que vous souhaitez supprimer:\n");
        fgets(m,33,stdin);
        Personne pat=search_pers(annu,m);
        remove_pers(annu,pat);
        break;
          
    case 4:
        char*m;
        m=(char*)malloc(sizeof(char)*33);
        printf("Veuillez entrer l'identifiant du compte que vous souhaitez afficher:\n");
        fgets(m,33,stdin);
        Personne pat=search_pers(annu,m);
        affichPers(pat);
        break;

    case 5:
        affichAnnuaire(annu,g);
        break;
    default :
        int i;
        printf("Choix invalide.Réessayer ?\n OUI=1 ?\t NON=0 ?\n");
        scanf("%d",&i);
        if(i=1){
            choix_admin(annu,f,g);
        }
        break;
    }
}

Annuaire modif_annuaireAdmin(int i,Annuaire annu,Personne p, FILE*f){
    Personne temp=initPers();
    temp=p;
    if(pers_existing (annu,temp)!=0){
        i=getIndicePersonne(annu,temp);
        annu=remove_at(i,annu);
    }
    int indice =i;
    modif_persAdmin(temp,f);
    int n=pers_existing (annu,temp);
    switch (n){
        case 0:
            printf("Modification effectuée avec succès\n");
            annu=insert_at(indice,temp,annu);
            return annu;
        case 1:
            printf("Identifiant déjà utilisé.Veuillez en changer\n");
            modif_id(temp);
            annu=modif_annuaireAdmin(indice,annu,temp,f);
            break;
        case 2:
            print("Cet utilisateur existe déjà\n");
            return annu;
        case 3:
            printf("Cette adresse mail est déjà liée à un compte. Veuillez en choisir une autre\n");
            modif_mail(temp);
            return modif_annuaireAdmin(indice,annu,temp,f);
            break;
        case 4:
            printf("Ce numéro de téléphone est déjà lié à un compte. Veuillez en utiliser un autre\n");
            modif_tel(temp);
            return modif_annuaireAdmin(indice,annu,temp,f);
            break;
        default:
            break;
        }
}//à tester