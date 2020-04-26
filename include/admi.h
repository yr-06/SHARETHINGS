#ifndef __ADMI__H
#define __ADMI__H

#include "annuaire.h"

void get_adm(FILE *f,FILE *g,Annuaire annu,Personne p)
int get_mdp(FILE*f,FILE *g,Annuaire annu,Personne p)
void init_mtp_admin(FILE *f)
void add_ress(Personne p, Liste base)
void modif_ress(){}; 
void modif_pers(Personne p,FILE*f)
void choix_admin(Annuaire annu,FILE*f,FILE *g)
Annuaire modif_annuaire(Annuaire annu,Personne p, FILE*f)

#endif
