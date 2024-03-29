#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>
#include "../include/chiffrement.h"
#include "../include/ressources.h"
#include "../include/personne.h"
#include "../include/annuaire.h"
#include "../include/affichageAdmin.h"
#include "../include/affichageUser.h"
#include "../include/welcome.h"

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

void init_mtp_admin(){
    FILE *f=fopen("./data/Mtdp_admin.txt", "w+");
    
    char*pwd;
    pwd=(char*)malloc(sizeof(char)*65);
    printf("Veuillez entrer le nouveau mot de passe administrateur:\n");
    fgets(pwd,65,stdin);
    fprintf(f,"%s",chiffrementMdp(pwd));

    color("32;01");
    printf("Mot de passe changé avec succès\n");
    color("37");
    printf("Le nouveau mot de passe est %s\n",pwd);
    fclose(f);
    return;

}// intitialise mot de passe administrateur si f=NULL



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
        welcomeUser(p,ls);
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
    FILE *f=fopen("./data/Mtdp_admin.txt", "r");
    if(f!=NULL){
        CLEAR_STDIN
        char *mdp;
        char *c;
        mdp=(char*)malloc(sizeof(char)*65);
        c=(char*)malloc(sizeof(char)*65);
        
        printf("\nVeuillez entrer le mot de passe administrateur :\n");
        fgets(c,65,stdin);
            
        fscanf(f,"%65s",mdp);
       
        int n=strcmp(mdp,chiffrementMdp(c));
        switch(n){
            case 0:
                messwelcomeAdmin(p);
                choix_admin(annu,ls,p);
                break;
            default :
                CLEAR_STDIN
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
                    CLEAR_STDIN
                    messAurevoir();
                    return;
                }   
            }
            int s;
            printf("Quitter le menu administrateur ?\nOUI= 1 ?\t NON=0 ?\n");
            scanf("%d",&s);
            if(s==0){
                CLEAR_STDIN
                free(c);
                free(mdp);
                menuAdmin(annu,ls,p);
                
            }else{
                messQuit();
                messByeAdmin(p);
                return;
            }
                
    
    }else{
        CLEAR_STDIN
        printf("Le mot de passe administrateur est inexistant. Veuillez l'initialiser.\n");
        init_mtp_admin();
        welcomeAdmin(annu,ls,p);
    }
}

void choix_admin(Annuaire annu,Liste ls,Personne p){
    color("33;1");
    printf("Que voulez-vous faire ?\n");
    color("37");
    printf("Ajouter un usager: 1\n Modifier les données d'un usager: 2\n Supprimer un usager: 3\n");
    printf("Afficher les données d'un usager: 4\n Afficher la liste des usagers:5\n Changer le mot de passe administrateur:6\n");
    printf("Transférer une ressource à un autre utilisateur:7\n Basculer vers le menu utilisateur:8\n");
    printf("Quitter le menu administrateur: 0\n");
    color("33;1");
    printf("Saisissez votre choix : \n");
    color("37");
    int d;
    scanf("%d",&d);
    switch(d){
    case 0:
        //Quitter le menu administrateur: 0
        CLEAR_STDIN
        return;
    case 1:
        //Ajouter un usager: 1
        CLEAR_STDIN
        annu=createAccount(annu);
        CLEAR_STDIN
        break;
    case 2:
        //Modifier les données d'un usager: 2
        CLEAR_STDIN
        char*m;
        m=(char*)malloc(sizeof(char)*33);
        printf("Veuillez entrer l'identifiant du compte que vous souhaitez modifier:\n");
        scanf("%s",m);
        
        CLEAR_STDIN
        
        Personne pat=search_pers(annu,m);
        
        if(pat!=NULL){
            CLEAR_STDIN
            affich_pers(pat);
            int i=getIndicePersonne(annu,pat);
            
            Personne temp=initPers();
            setPers(temp,getNumAccount(pat),getAutor(pat),getName(pat),getPrenom(pat),getNaiss(pat),getIDPers(pat),getPwd(pat),getMail(pat),getTel(pat));
            annu=remove_at(i,annu);
            annu=modifAnnuaireAdmin(i,annu,temp);
            break;
        }else{
            CLEAR_STDIN
            color("31;1");
            printf("Il n'existe pas de compte associé à cet identifiant.\n");
            color("37");
            choix_admin(annu,ls,p);
        }
    case 3:
        //Supprimer un usager: 3
        CLEAR_STDIN
        char *n;
        n=(char*)malloc(sizeof(char)*33);
        printf("Veuillez entrer l'identifiant du compte que vous souhaitez supprimer:\n");
        scanf("%s",n);
        Personne pa=search_pers(annu,n);
        if (pa!=NULL){
            CLEAR_STDIN
            int r;
            color("31;1");
            printf("Etes-vous sûr(e) de vouloir supprimer ce compte ?\nOUI= 1 ?\t NON=0 ?\n");
            color("37");
            scanf("%d",&r);
            if(r==1){
                annu=remove_pers(annu,pa);
                break;
            }else{
                CLEAR_STDIN
                choix_admin(annu,ls,p);
            }

        }else{
            CLEAR_STDIN
            color("31;1");
            printf("Il n'existe pas de compte associé à cet identifiant.\n");
            color("37");
            choix_admin(annu,ls,p);
         }
    case 4:
        //Afficher les données d'un usager: 4
        CLEAR_STDIN
        char*o;
        o=(char*)malloc(sizeof(char)*33);
        printf("Veuillez entrer l'identifiant du compte que vous souhaitez afficher:\n");
        scanf("%s",o);
        Personne pt=search_pers(annu,o);
        if (pt!=NULL){
            CLEAR_STDIN
            affich_pers(pt);
            break;
        }else{
            CLEAR_STDIN
            color("31;1");
            printf("Il n'existe pas de compte associé à cet identifiant.\n");
            color("37");
            choix_admin(annu,ls,p);
        }
    case 5:
        //Afficher la liste des usagers:5
        CLEAR_STDIN
        affichAnnuaire(annu);
        break;
    case 6:
        //Changer le mot de passe administrateur:6
        CLEAR_STDIN
        init_mtp_admin();
        break;
    case 7:
        //Transférer une ressource à un autre utilisateur:7
        CLEAR_STDIN
        transfererRessource(p,ls,annu);
        break;
    case 8:
        //Basculer vers le menu utilisateur:8
        CLEAR_STDIN
        color("33;1");
        printf("\nVous allez être redirigé vers le menu utilisateur\n");
        color("37");
        welcomeUser(p,ls);
	break;
    default :
        printf("Choix invalide.Réessayer ?\n OUI=1 ?\t NON=0 ?\n");
        int v;
        scanf("%d",&v);
        if(v==1){
            CLEAR_STDIN
            choix_admin(annu,ls,p);
        }else{
            return;
        }
    }
    int c; 
    printf("Réaliser une autre action ?\n OUI=1 ?\t NON=0 ?\n");
    scanf("%d",&c);
    if(c==1){
        CLEAR_STDIN
        choix_admin(annu,ls,p);
    }else{
        return;
    }
}

