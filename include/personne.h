#ifndef PERSONNE__H
#define PERSONNE__H
typedef struct s_pers *Personne;

typedef struct s_elementa *Elementa;

typedef struct s_annuaire *Annuaire;


char*get_num_account(Personne p)
int get_autor(Personne p)

char*get_name(Personne p)
char*get_prenom(Personne p)
char*get_naiss(Personne p)

char*get_id(Personne p)
char*get_pwd(Personne p)


char*get_mail(Personne p)
char*get_tel(Personne p)

int get_nb_pret(Personne p)

 
void set_num_account(Personne p, int i)
void set_autor(Personne p,FILE*f)

void set_name(Personne p,char*name)
void set_prenom(Personne p,char*prenom)
void  set_naiss(Personne p, char*date)

void set_id(Personne p,char*id)
void set_pwd(Personne p,char*pwd)

void set_mail(Personne p,char*mail)
void set_tel(Personne p,char*tel)


void modif_name(Personne p)
void modif_prenom(Personne p)
void modif_naiss(Personne p)

void modif_id(Personne p)
void modif_pwd(Personne p)

void modif_mail(Personne p)
void modif_tel(Personne p)

Annuaire create_annuaire()

Annuaire push_fa(Annuaire a,Elementa a)
Annuaire push_ba(Annuaire annu,int i, Elementa a)
Annuaire pop_fa(Annuaire ls)
Annuaire pop_ba(Annuaire ls)

Annuaire insert_at(int i,Personne pers,Annuaire annu)
Annuaire remove_at(int i,Annuaire annu)

    
Personne create_pers(FILE *f)
void affich_pers(Personne p)

Annuaire add_pers(Annuaire annu,Personne pers)
Annuaire remove_pers(Annuaire annu, Personne pers)


Personne search_pers(Annuaire annu, char * id)
int indice_personne_annu(Annuaire annu, Personne pers)

int pers_existing (Annuaire annu, Personne p)
int create_num_account(Annuaire annu)








#endif
