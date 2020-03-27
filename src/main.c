#include <stdio.h>
#include "struct.h"
//Initialise mot de passe

// gestion des menus
enum connexion={
    GET_CONNECT;
    CREATE_PERS;


}
 gestmenu(){
    Personne p= (Personne)malloc(sizeof(s_pers));
    
    printf("Bienvenue dans le menu de notre base de données !\n");
    printf("Que souhaitez-vous faire ?\n Se connecter=0\t Creer un compte=1\n");
    scanf("%d",&c);
    switch (c)
    {
    case 
        /* code */
        break;
    
    default:
        break;
    }
    )
    printf("Veuillez entrer votre identifiant (tapez):\n");
    scanf("%s",&s);
    p=search_pers(annu,s);






int main ( int argc, char *argv []){
    FILE *f=NULL;
    FILE *g=NULL;
    f=fopen("mtp_amin.txt", "a+");
    g=fopen("id_users.json", "a+");
    gestmenu(f,g);

}
