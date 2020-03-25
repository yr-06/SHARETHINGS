#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>
#include "../include/admi.h"
#include "../include/chiffrement.h"
#include "../include/personne.h"
#include "../include/ressources.h"

int get_adm(FILE *f,Annuaire annu){
    char *s;
    char *c;
    char *pwd;
    
    if (p->a=1){
        printf("Veuillez entrer le mot de passe administrateur\n");
        scanf("%s",&c);

        printf("Mot de passe incorrect. Réessayez?\n")
        printf("OUI= 1, NON=0\n");

    }
 /*   c=crypt(c,);
    fscanf(f,"%s",&c);
    int n=strcmp(s,c);
  if (n=0){
        printf("Bienvenue dans le menu administrateur\n");
        printf("Que voulez-vous faire ?\n");
        printf("Ajouter un usager: 1\n Modifier les données d'un usager: 2\n Supprimer un usager: 3\n");
        printf("Afficher la liste des usagers:4\n Quitter: 0\n");
        choix();
    }
   
    printf("votre choix ")
    scanf("%d",&n);
    if(n=1){
         get_admf(f);
    }
}*/
void init_mtp(FILE *f){
    char*pwd;
    printf("Veuillez initialiser le mot de passe administrateur:");
    scanf("%s",&pwd);
    fprintf(f,"%s",chiffrementMdp(pwd));
}


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

void modif_pers(Annuaire annu,Personne p){
    int i,j;
    j=annu->size;
    current_a=annu->head;
    for(i=0;i<j;i++){
        if(p->num_account==current_a->p->num_account){
            //offrir le choix du champ à modifier 
        }
        current_a=current_a->next;
    }

} 
void supp_pers(){};
void affichPers(){};
/*void choix(){
      int d;
      printf("Saisissez votre choix: ");
      scanf("%d",d);
      switch(d){
          case 0:
              printf("Vous allez être redirigé\n");
              break;
          case 1:
              add_pers();
              break;

          case 2:
              modif_pers();
              break;
          
          case 3:
              supp_pers();
              break;
          
          case 4:
              affichPers();
              break;
          
          default :
              printf("Choix invalide");
              choix();
              break;
    }
}*/