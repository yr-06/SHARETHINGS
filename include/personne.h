#ifndef PERSONNE__H
#define PERSONNE__H
typedef struct s_pers *Personne;

typedef struct s_elementa *Elementa;

typedef struct s_annuaire *Annuaire;

char*get_num_account(Personne p)
autor get_autor(Personne p)
char*get_name(Personne p)
char*get_prenom(Personne p)
char*get_id(Personne p)
char*get_pwd(Personne p)
char*get_mail(Personne p)
char*get_tel(Personne p)

void set_num_account(int i,Personne p)
void set_autor(Personne p)
void set_name(Personne p)
void set_prenom(Personne p)
void set_id(Personne p)
void set_pwd(Personne p)
void set_mail(Personne p)
void set_tel(Personne p)

Annuaire push_ba(Annuaire annu,int i, Elementa a)
Annuaire push_fa(Annuaire a,Elementa a)
Annuaire pop_fa(Annuaire ls)
Annuaire pop_ba(Annuaire ls)

Annuaire insert_at(int i,Personne pers,Annuaire annu)
Annuaire remove_at(int i,Annuaire annu)

Annuaire add_pers(Annuaire annu,Personne pers)
Annuaire remove_pers(Annuaire annu, Personne pers)

Personne create_pers()
Personne search_pers(Annuaire annu, char * id)

int create_num_account(Annuaire annu, Personne pers)
int indice_personne_annu(Annuaire annu, Personne pers)

#endif