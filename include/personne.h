#ifndef PERSONNE__H
#define PERSONNE__H
typedef struct s_pers *Personne;

typedef struct s_elementa *Elementa;

typedef struct s_annuaire *Annuaire;

int nb_pret(Personne p);
Annuaire push_ba(Annuaire annu,int i, Elementa a)
Annuaire push_fa(Annuaire a,Elementa a)
Annuaire pop_fa(Annuaire ls)
Annuaire pop_ba(Annuaire ls)
Annuaire insert_at(int i,Personne pers,Annuaire annu)
Annuaire remove_at(int i,Annuaire annu)
  
#endif
