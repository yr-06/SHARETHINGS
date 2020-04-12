#ifndef PERSONNE__H
#define PERSONNE__H
typedef struct s_pers *Personne;

typedef struct s_elementa *Elementa;

typedef struct s_annuaire *Annuaire;

typedef enum{
    false,
    true
}Bool;

//getters

int getNumAccount(Personne p)
/*----------------------------------------------------------------*/
int getAutor(Personne p)
/*----------------------------------------------------------------*/
char*getName(Personne p)
/*----------------------------------------------------------------*/
char*getPrenom(Personne p)
/*----------------------------------------------------------------*/
char*getNaiss(Personne p)
/*----------------------------------------------------------------*/
char*getID(Personne p)
/*----------------------------------------------------------------*/
char*getPwd(Personne p)
/*----------------------------------------------------------------*/
char*getMail(Personne p)
/*----------------------------------------------------------------*/
char*getTel(Personne p)
/*----------------------------------------------------------------*/
//int getPossess(Personne p)
/*----------------------------------------------------------------*/
//int getNbPret(Personne p)
/*----------------------------------------------------------------*/

 //setters
void setNumAccount(Personne p, int i){
  p->num_account=i;
} 
/*void setAutor(Personne p,FILE*f)*/
void setAutor(Personne p,int i)//version utilisée pour phase de tests
/*----------------------------------------------------------------*/
void setName(Personne p,char*name)
/*----------------------------------------------------------------*/
void setPrenom(Personne p,char*prenom)
/*----------------------------------------------------------------*/
void  setNaiss(Personne p, char*date)
/*----------------------------------------------------------------*/
void setID(Personne p,char*id)
/*----------------------------------------------------------------*/
void setPwd(Personne p,char*pwd)
/*----------------------------------------------------------------*/
void setMail(Personne p,char*mail)
/*----------------------------------------------------------------*/
void setTel(Personne p,char*tel)
/*----------------------------------------------------------------*/
/*void setPossess(Personne p,int i)*/
/*----------------------------------------------------------------*/

//Fonctions permettants de modifier données d'une personne

void modif_name(Personne p)
/*----------------------------------------------------------------*/
void modif_prenom(Personne p)
/*----------------------------------------------------------------*/
void modif_naiss(Personne p)
/*----------------------------------------------------------------*/
void modif_id(Personne p)
/*----------------------------------------------------------------*/
void modif_pwd(Personne p)
/*----------------------------------------------------------------*/
void modif_mail(Personne p)
/*----------------------------------------------------------------*/
void modif_tel(Personne p)
/*----------------------------------------------------------------*/
Personne initPers()
/*----------------------------------------------------------------*/
Personne create_pers()
/*----------------------------------------------------------------*/
void affich_pers(Personne p)
/*----------------------------------------------------------------*/
void modif_pers(Personne p)
/*----------------------------------------------------------------*/
Annuaire new_annu()
/*----------------------------------------------------------------*/
Bool is_empty_annu(Annuaire annu)
/*----------------------------------------------------------------*/
int annuaire_size(Annuaire annu)
/*----------------------------------------------------------------*/
void print_annu(Annuaire annu)
/*----------------------------------------------------------------*/
Annuaire push_ba(Annuaire annu,Personne p)
/*----------------------------------------------------------------*/
Annuaire push_fa(Annuaire annu,Personne p)
/*----------------------------------------------------------------*/
Annuaire pop_ba(Annuaire annu)
/*----------------------------------------------------------------*/
Annuaire pop_fa(Annuaire annu)
/*----------------------------------------------------------------*/
Annuaire clear_annu(Annuaire annu)
/*----------------------------------------------------------------*/
Annuaire insert_at(int i,Personne p,Annuaire annu)
/*----------------------------------------------------------------*/
Annuaire remove_at(int i,Annuaire annu)
/*----------------------------------------------------------------*/
int getIndicePersonne(Annuaire annu, Personne pers)
/*----------------------------------------------------------------*/
int pers_existing(Annuaire annu, Personne p)
/*----------------------------------------------------------------*/
int createNumAccount(Annuaire annu)
/*----------------------------------------------------------------*/

void affichAnnuaire(Annuaire annu,FILE*f)
/*----------------------------------------------------------------*/
Annuaire add_pers(Annuaire annu,Personne pers)
/*----------------------------------------------------------------*/
Annuaire remove_pers(Annuaire annu, Personne pers)
/*----------------------------------------------------------------*/

Personne search_pers(Annuaire annu, char * id)
/*----------------------------------------------------------------*/
Annuaire modif_annuaire(Annuaire annu,Personne p)

#endif
