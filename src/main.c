#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>
#include "../include/admi.h"
#include "../include/chiffrement.h"
#include "../include/annuaire.h"

#ifndef CLEAR_STDIN
    #define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#endif

int main ( int argc, char *argv []){
    Personne p=initPers();
    Annuaire annu=new_annu();
    Liste ls=new_list();
    ls=LoadListe(ls);
    annu=LoadAnnu(annu);
    affichageGen(ls,annu);
    update
   
    return 0;

}


       
