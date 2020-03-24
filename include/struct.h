#ifndef STRUCT__H
#define STRUCT__H
typedef struct s_pers *Personne;

typedef struct s_ressource *Ressource; 

typedef struct s_elementa *Elementa;

typedef struct s_elementl *Elementl;


typedef struct s_annuaire *Annuaire;

typedef struct s_liste *Liste;

Liste push_bl(Liste ls,int i, Elementl l)
Liste push_fl(Liste ls,Elementl l)
Liste pop_fl(Liste ls)
Liste pop_bl(Liste ls)
Liste insert_at(int i,Ressource ress,Liste ls)
Liste remove_at(int i,Liste ls)
Annuaire push_ba(Annuaire annu,int i, Elementa a)
Annuaire push_fa(Annuaire a,Elementa a)
Annuaire pop_fa(Annuaire ls)
Annuaire pop_ba(Annuaire ls)
Annuaire insert_at(int i,Personne pers,Annuaire annu)
Annuaire remove_at(int i,Annuaire annu)
  

#endif
