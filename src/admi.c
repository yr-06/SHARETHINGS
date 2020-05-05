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


void get_adm(FILE *f,FILE*g,FILE*h,Annuaire annu,Liste ls,Personne p){
    int i=get_autor(p);
    switch(i){
        case 0:
            printf("Vous n'avez pas les habilitations nécessaire pour continuer\n");
            printf("Vous allez être redirigé\n");
            gestmenu(f,g,h,annu,ls,p);
            break;
        case 1:
            printf("Vous êtes habilité à vous connecter en tant qu'administrateur\n");
            get_mdp_admin(f,g,annu,p);
            return;
        default :
            printf("ERROR--Vous allez être redirigé\n");
            get_adm(f,g,h,annu,ls,p);
            break;
    }
}

void get_mdp_admin(FILE*f,FILE*g,Annuaire annu,Personne p){
    if(f==NULL){
        init_mtp_admin(f);
        get_mdp_admin(f,p,annu,p);
    }
    char *mdp;
    char *c;
    
    mdp=(char*)malloc(sizeof(char)*65);
    c=(char*)malloc(sizeof(char)*65);
    fscanf(f,"%s",mdp);
    
    printf("Veuillez entrer le mot de passe administrateur :\n");
    fgets(c,65,stdin);
    //c=chiffrementMdp(c);
    
    int n=strcmp(mdp,c);
    
    switch(n){
        case 0:
            printf("Bienvenue %s %s dans le menu administrateur!\n",getName(p),getPrenom(p));
            printf("Que voulez-vous faire ?\n");
            printf("Ajouter un usager: 1\n Modifier les données d'un usager: 2\n Supprimer un usager: 3\n");
            printf("Afficher les données d'un usager: 4\n Afficher la liste des usagers:5\n Quitter le menu administrateur: 0\n");
            choix_admin(annu,f,g);
        default :
            int i;
            printf("Mot de passe incorrect. Réessayez?\n")
            printf("OUI= 1 ?\t NON=0 ?\n");
            scanf("%d",&i);
            if(i==1){
                get_mdp_admin(f,g,annu,p);
            }
            break;
    }
    int s;
    printf("Quitter le menu administrateur ?\n")
    printf("OUI= 1 ?\t NON=0 ?\n");
    scanf("%d",&s);
    if(s==0){
        get_mdp_admin(f,g,annu,p);
    }else{
        return ;
    }
}

void init_mtp_admin(){
    FILE *f=fopen("../data/Mtdp_admin.txt", "w+");
    char*pwd;
    pwd=(char*)malloc(sizeof(char)*65);
    printf("Veuillez initialiser le mot de passe administrateur:");
    fgets(pwd,65,stdin);
    fprintf(f,"%s",chiffrementMdp(pwd));
    printf("cryptage=%s",chiffrementMdp(pwd));
}// intitialise mot de passe administrateur si f=NULL



void choix_admin(Annuaire annu,FILE*f,FILE*g){
    int d;
    printf("Saisissez votre choix : \n");
    scanf("%d",&d);
    switch(d){
    case 0:
        return;
        break;
    case 1:
        annu=createAccount(annu,f);
        break;
    case 2:
        char*m;
        m=(char*)malloc(sizeof(char)*33);
        printf("Veuillez entrer l'identifiant du compte que vous souhaitez modifier:\n");
        fgets(m,33,stdin);
        
        Personne pat=initPers();
        pat=search_pers(annu,m);
        affich_pers(pat);
        
        int i=getIndicePersonne(annu,pat);
        Personne temp=initPers();
        temp=pat;
        
        annu=remove_at(i,annu);
        annu=modif_annuaireAdmin(i,annu,temp,f);
        f=fopen("../data/Annuaire.json","w");
        print_annu_JSON(annu,f);
        return annu;

    case 3:
        char *m;
        m=(char*)malloc(sizeof(char)*33);
        printf("Veuillez entrer l'identifiant du compte que vous souhaitez supprimer:\n");
        fgets(m,33,stdin);
        Personne pat=initPers();
        pat=search_pers(annu,m);
        remove_pers(annu,pat);
        break;
          
    case 4:
        char*m;
        m=(char*)malloc(sizeof(char)*33);
        printf("Veuillez entrer l'identifiant du compte que vous souhaitez afficher:\n");
        fgets(m,33,stdin);
        Personne pat=initPers();
        pat=search_pers(annu,m);
        affichPers(pat);
        break;

    case 5:
        printf("Voici la liste des usagers\n");
        affichAnnuaire(annu);
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
    int i;
    printf("Réaliser une autre action ?\n OUI=1 ?\t NON=0 ?\n");
    scanf("%d",&i);
    if(i=1){
        choix_admin(annu,f,g);
    }else{
        return;
    }
}



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
*/
