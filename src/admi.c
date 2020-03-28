#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>
#include "../include/admi.h"
#include "../include/chiffrement.h"
#include "../include/personne.h"
#include "../include/ressources.h"

void get_adm(FILE *f,Annuaire annu,Personne p){
    int i=get_autor(p);
    switch(i){
        case 0:
         printf("Vous n'avez pas les habilitations nécessaire pour continuer\n");
        case 1:
            printf("Vous êtes habilité à vous connecter en tant qu'administrateur\n");
            get_mdp(f,annu,p);
    }
}

int get_mdp(FILE*f,Annuaire annu,Personne p){
    if(f=NULL){
        init_mtp_admin(f);
        get_mdp(f,p);
    }
    char*mdp;
    char*c;
    mdp=(char*)malloc(sizeof(char)*65);
    c=(char*)malloc(sizeof(char)*65);
    fscanf(f,"%65s",mdp);
    printf("Veuillez entrer le mot de passe administrateur :\n");
    scanf("%65s",c);
    c=chiffrementMdp(c);
    int n=strcmp(mdp,c);
  if (n=0){
       printf("Bienvenue %s %s dans le menu administrateur!\n",get_name(p),get_prenom(p));
        printf("Que voulez-vous faire ?\n");
        printf("Ajouter un usager: 1\n Modifier les données d'un usager: 2\n Supprimer un usager: 3\n");
        printf("Afficher la liste des usagers:4\n Quitter: 0\n");
        choix();
        return 0;
    }
    int i;
    printf("Mot de passe incorrect. Réessayez?\n")
    printf("OUI= 1 ?\t NON=0 ?\n");
    scanf("%d",&i);
    if(i=1){
        get_mdp(f,p);
    }
    else{
        return 1;
    }   
}

void init_mtp_admin(FILE *f){
    char*pwd;
    printf("Veuillez initialiser le mot de passe administrateur:");
    scanf("%s",&pwd);
    fprintf(f,"%s",chiffrementMdp(pwd));
}// intitialise mot de passe administrateur si f=NULL


void add_ress(Personne p, Liste base){
    Elementl lr=(Elementl)malloc(sizeof(s_elementl));
    Ressource ress=(Ressource)malloc(sizeof(s_ressource));
    char*type;
    char*name;
    ress->nom_proprio=p->nom;
    ress->prenom_proprio=p->prenom_proprio;
    printf("Veuillez entrer le type de votre ressource :");
    scanf(%s,&type);
    printf("\nVeuillez entrer le nom de votre ressource :");
    scanf(%s,&name);
    ress->nom=name;
    ress->type=type;
    r->t=0;
    //ajouter instruction pour initialiser dates de pret, nom de l'emprunteur
    lr->r->ress;
    lr->i=i++;
    int i=base->size;
    push_bl(base,i,lr);
}
   
void modif_ress(){}; 

void modif_pers(Personne p,FILE*f){
    int i;
    printf("Modifier nom: 1\n Modifier prenom: 2\n Modifier date de naissance: 3\n");
    printf("Modifier identifiant: 4\n Modifier mot de passe: 5\n Modifier adresse mail: 6\n");
    printf("Modifier numéro de téléphone: 7\n Modifier habilitation: 8\n Quitter: 0\n");
    printf("Saisissez votre choix : \n");
    scanf("%d",&i);
    switch (i)
    {
    case 0:
        break;
    case 1:
        modif_name(p);
    case 2:
        modif_prenom(p);
    case 3:
        modif_naiss(p);
    case 4:
       modif_id(p);
    case 5:
        modif_pwd(p);
    case 6:
        modif_mail(p);
    case 7:
        modif_tel(p);
    case 8:
        set_autor(p,f);
    
    default:
        break;
    }
    int u;
    printf("Continuer ?\n OUI=1 ?\t NON=0 ?\n");
    scanf("%d",&u);
    if(u==1){
        modif_per(p,f);
    }
}

void choix(Annuaire annu,FILE*f){
      int d;
      printf("Saisissez votre choix : \n");
      scanf("%d",&d);
      switch(d){
          case 0:
              printf("Vous allez être redirigé\n");
              break;
          case 1:
                Personne pers=create_pers(f);
                add_pers(annu,pers);
              break;

          case 2:
            char*m;
            m=(char*)malloc(sizeof(char)*33);
            printf("Veuillez entrer l'identifiant du compte que vous souhaitez modifier:\n");
            scanf("%33s",m);
            Personne pat=search_pers(annu,m);
            affich_pers(pat);
            modif_pers(pat,f);
            affich_pers(pat);
          case 3:
            char*m;
            m=(char*)malloc(sizeof(char)*33);
            printf("Veuillez entrer l'identifiant du compte que vous souhaitez supprimer:\n");
            scanf("%33s",m);
            Personne pat=search_pers(annu,m);
            remove_pers(annu,pat);
          
          case 4:
            char*m;
            m=(char*)malloc(sizeof(char)*33);
            printf("Veuillez entrer l'identifiant du compte que vous souhaitez afficher:\n");
            scanf("%33s",m);
            Personne pat=search_pers(annu,m);
            affichPers(pat);
          
          default :
            int i;
            printf("Choix invalide.Réessayer ?\n OUI=1 ?\t NON=0 ?\n");
            scanf("%d",&i);
            if(i=1){
                 choix();
            }
            break;
    }
}

void modif_annuaire(Annuaire annu,Personne p, FILE*f){
     int j=annu->size;
     Elementa current_a=annu->head;
     for (i=0;i<j;i++){
         if(strcmp(id,current_a->p->id)==0){
            modif_pers(current->a->p,f);
            int n=pers_existing (annu,current->a->p);
            if(n!==0){
                switch (n){
                    case 0 :
                    printf("Modification effectuée avec succès\n");
                    return annu;
                    case 1:
                    printf("Identifiant déjà utilisé.Veuillez en changer\n");
                    modif_pers(current->a->p,f);
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
            }
         }
         current_a=current_a->next;
     }

}