
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure pour compte users. si compte commun , mettre un int qui dit si oui ou non on est admin.
typedef struct compte_u{
        char nom[32];
        char prenom[32]
        char ID[64];
        char mdp[64];
        //ressource à afficher : struct ressource_user* ressource; livres empruntes/deposes

}user;

//getters : permet de recuperer les differentes variables
char * get_nom(user u){
        return(u->nom);

 }

char * get_prenom(user u){
        return(u->prenom);

}
char * get_mdp(user u){
        return(u->mdp);
}


char * get_ID(user u){
        return(u->ID);
}

//Setters : permet d'attribuer a des variables des valeurs

void set_nom(user u, char * nom){
        strcpy(u->nom, nom);//copie la valeur d'une chaine de caractere à la position voulue(par le biais de
//pointeur)
}


void set_prenom(user u, char * prenom){
        strcpy(u->prenom, prenom);

}

void set_mdp(user u, char * mdp){
        strcpy(u->mdp, mdp);

}

void set_ID(user u, char * ID){
        strcpy(u->ID, ID);

}

user changer_mdp(user u){


