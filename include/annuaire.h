#ifndef __ANNUAIRE__H
#define __ANNUAIRE__H


#include "personne.h"
typedef struct s_annuaire *Annuaire;
typedef struct s_elementa *Elementa;
 
Annuaire new_annu();

Bool is_empty_annu(Annuaire annu);

int annuaire_size(Annuaire annu);

Annuaire push_ba(Annuaire annu,Personne p);
Annuaire push_fa(Annuaire annu,Personne p);

Annuaire pop_ba(Annuaire annu);
Annuaire pop_fa(Annuaire annu);

Annuaire clear_annu(Annuaire annu);

Annuaire insert_at(int i,Personne p,Annuaire annu);
Annuaire remove_at(int i,Annuaire annu);

int getIndicePersonne(Annuaire annu, Personne pers);

int pers_existing(Annuaire annu, Personne p);

int createNumAccount(Annuaire annu);

void affichAnnuaire(Annuaire annu);

Annuaire add_pers(Annuaire annu,Personne pers);
Annuaire remove_pers(Annuaire annu, Personne pers);

Personne search_pers(Annuaire annu, char * id);

Annuaire modifAnnuaireAdmin(int i,Annuaire annu,Personne temp);
Annuaire modifAnnuaireUser(int i,Annuaire annu,Personne temp);

Annuaire createAccount(Annuaire annu);

#endif
