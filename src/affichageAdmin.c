#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>

#include "../include/personne.h"

#ifndef COLOR
    #define color(param) printf("\033[%sm",param)
#endif

/* Paramètre  Couleur
30 Noir |31 Rouge | 32 Vert | 33 Jaune | 34 Bleu | 35 Magenta | 36 Cyan | 37 Blanc
 
"1" active la haute intensité des caractères.
*/

void welcomeMenuAdmin(Personne p){
    color("36;1");
    printf("       ****   Bienvenue %s dans le menu administrateur !   ***       \n",getPrenom(p));
    color("37");
    return;
}

//Operation Done



//Notifications

//Messages d'erreur


void messErrorRedirection(){
    color("31;1");
    printf("\nERROR--Vous allez être redirigé\n");
    color("37");
    return;
}

