#include <stdio.h>
#include <stdlib.h>                        
#include <string.h>
#include <crypt.h>
#include <unistd.h>
#include "../include/ressources.h"
#include "../include/welcome.h"
#include "../include/annuaire.h"


#ifndef CLEAR_STDIN
    #define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#endif

int main ( int argc, char *argv []){
   
    Annuaire annu=new_annu();
    Liste ls=new_list();
    
    ls=LoadListe_JSON(ls);
    annu=LoadAnnu_JSON(annu);
    
    affichageGen(ls,annu);

    updateListe_JSON(ls);
    updateAnnu_JSON(annu);

    ls=clear_list(ls);
    annu=clear_annu(annu);

    return 0;

}


       
