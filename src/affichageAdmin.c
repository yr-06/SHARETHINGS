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

#ifndef COLOR
    #define color(param) printf("\033[%sm",param)
#endif

/* Paramètre  Couleur
30 Noir |31 Rouge | 32 Vert | 33 Jaune | 34 Bleu | 35 Magenta | 36 Cyan | 37 Blanc
 
"1" active la haute intensité des caractères.
*/


void messwelcomeAdmin(Personne p){
    color("36;1");
    printf("       ****   Bienvenue %s dans le menu administrateur !   ***       \n",getPrenom(p));
    color("37");
    return;
}

void messByeAdmin(Personne p){
    color("36;1");
    printf("       ****   Au revoir %s et à bientôt dans le menu administrateur  !   ***       \n",getPrenom(p));
    color("37");
    return;
}

void messErrorRedirection(){
    color("31;1");
    printf("\nERROR--Vous allez être redirigé\n");
    color("37");
    return;
}
void messQuit(){
    color("33;1");
    printf("Vous allez quitter le menu administrateur\n");
    color("37");
    return;
}

void get_adm(Annuaire annu,Liste ls,Personne p){
    int i=get_autor(p);
    switch(i){
        case 0:
            printf("Vous n'avez pas les habilitations nécessaire pour continuer\n");
            printf("Vous allez être redirigé\n");
            gestmenu(f,g,h,annu,ls,p);
            break;
        case 1:
            printf("Vous êtes habilité à vous connecter en tant qu'administrateur\n");
            get_mdp_admin(annu,ls,p);
            return;
        default :
            printf("ERROR--Vous allez être redirigé\n");
            get_adm(f,g,h,annu,ls,p);
            break;
    }
}//useless

void welcomeAdmin(Annuaire annu,Liste ls,Personne p){
    int i;
    color("33;1");
    printf("Voulez-vous vous connecter en tant qu'admnisitrateur ?\n OUI=1 ?\t NON=0 ?\n");
    color("37");
    scanf("%d",&i);
    switch (i)
    {
    case 0:
        color("33;1");
        printf("Vous allez être redirigé vers le menu utilisateur\n");
        color("37");
        //fonction de Yayou
        break;
    case 1:
        color("33;1");
        printf("Vous allez entrer dans le menu administrateur\n");
        color("37");
        menuAdmin(annu,ls,p);
        break;
    default:
        messErrorRedirection();
        welcomeAdmin(annu,ls,p);
        break;
    }
    
}//-->good color

void menuAdmin(Annuaire annu,Liste ls,Personne p){
    FILE *f=fopen("../data/Mtdp_admin.txt", "r");
    if(f!=NULL){
        char *mdp;
        char *c;
        mdp=(char*)malloc(sizeof(char)*65);
        c=(char*)malloc(sizeof(char)*65);
        
        fscanf(f,"%65s",mdp);
        printf("Veuillez entrer le mot de passe administrateur :\n");
        fgets(c,65,stdin);
        
        int n=strcmp(mdp,chiffrementMdp(c));
        switch(n){
            case 0:
                messwelcomeAdmin(p);
                color("33;1");
                printf("Que voulez-vous faire ?\n");
                color("37");
                printf("Ajouter un usager: 1\n Modifier les données d'un usager: 2\n Supprimer un usager: 3\n");
                printf("Afficher les données d'un usager: 4\n Afficher la liste des usagers:5\n Changer le mot de passe administrateur:6\n");
                printf("Transférer une ressource à un autre utilisateur:7\n Basculer vers le menu utilisateur:8\n");
                printf("Quitter le menu administrateur: 0\n");
                choix_admin(annu,ls,p);
                break;
            default :
                int i;
                color("31;1");
                printf("Mot de passe incorrect. Réessayez?\n");
                printf("OUI= 1 ?\t NON=0 ?\n");
                color("37");
                scanf("%d",&i);
                if(i==1){
                    free(c);
                    free(mdp);
                    menuAdmin(annu,ls,p);
                }else{
                    messQuit()
                    messByeAdmin(p);
                    return;
                }
                
            }
            int s;
            printf("Quitter le menu administrateur ?\nOUI= 1 ?\t NON=0 ?\n");
            scanf("%d",&s);
            if(s==0){
                free(c);
                free(mdp);
                menuAdmin(annu,ls,p);
                
            }else{
                messQuit()
                messByeAdmin(p);
                return;
            }
                
    
    }else{
        init_mtp_admin(f);
        welcomeAdmin(annu,ls,p);
    }

}




void init_mtp_admin(){
    FILE *f=fopen("../data/Mtdp_admin.txt", "w");
    char*pwd;
    pwd=(char*)malloc(sizeof(char)*65);
    printf("Veuillez initialiser le mot de passe administrateur:");
    fgets(pwd,65,stdin);
    fprintf(f,"%s",chiffrementMdp(pwd));
    printf("cryptage=%s",chiffrementMdp(pwd));
    fclose(f);
}// intitialise mot de passe administrateur si f=NULL



void choix_admin(Annuaire annu,FILE*f,FILE*g){
    color("33;1");
    printf("Saisissez votre choix : \n");
    color("37");
    int d;
    scanf("%d",&d);
    switch(d){
    case 0:
        return;
        break;
    case 1:
        return choix_admin(crea,f);
       
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
        affichAnnuaire(annu);
        break;
    default :
        int i;
        printf("Choix invalide.Réessayer ?\n OUI=1 ?\t NON=0 ?\n");
        scanf("%d",&i);
        if(i=1){
            choix_admin(annu,);
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










