#ifndef __RESSOURCES_H__
#define __RESSOURCES_H__

typedef int Bool ;  //définition du type booléen,

#define false  0 /* affectation des valeurs conventionnelles*/

#define true  1
#include "personne.h"
#include "date.h"
#include "annuaire.h"

//structures
typedef struct s_ressource *Ressource;
typedef struct s_elementl *Elementl;
typedef struct s_liste *Liste;

//setters
void setType(Ressource r, char * type);
void setNom(Ressource r, char * nom);
void setDateDeb(Ressource r, Date date_d);
void setCreateDate(Ressource r, Date date);
void setDateFin(Ressource r, Date date_f);
void setTakenBy(Ressource r, char * takenBy);
void setDropBy(Ressource r, char * dropBy);

//getters
char * getType(Ressource r);
char * getNom(Ressource r);
Date getDateDeb(Ressource r);
Date getDateFin(Ressource r);
Date getDateCrea(Ressource r);
char * getTakenBy(Ressource r);
char * getRessourceDispo(Ressource r);
char * getID_r(Ressource r);
char *getPwd(Personne p);
int getPossess(Personne p,Liste ressources);
int getEmprunt(Personne p, Liste ressources);

//fonctions sur Ressource
int isDispo(Ressource r);
Ressource initRessource(Liste ressources);
int haveRessource(Personne p, Ressource r);
char * generateID(Liste ressources);
void gererDropRessource(Personne p, Liste l);
void gererTakeRessource(Personne p, Liste l);
void searchRessourceByDate(Personne p, Liste ressources);
void searchRessource(Personne p, Liste ressources);
void afficherActions(Personne p, Liste l);

//fonctions sur Liste :
int getIndex(Ressource r, Liste l);
Ressource getRessouce(int index, Liste l);
Liste new_list();
Bool is_empty_list(Liste l);
int list_size(Liste l);
void affich_ress(Ressource r);
void print_list(Liste l);
Liste push_bl(Liste l,Ressource r);
Liste push_fl(Liste l,Ressource r);
Liste pop_bl(Liste l);
Liste pop_fl(Liste l);
Liste clear_list(Liste l);
Liste insert_at_l(int i,Ressource r, Liste ls);
Liste remove_at_l(int i,Liste ls);
int ress_existing(Liste ls, Ressource r);
void removeRessource(Ressource r,Liste l);
void takeRessource(Personne p, Liste l);
Liste depotRessource(Personne p,Liste ressources);
Liste empruntRessource(Personne p,Liste ressources);

//getters sur les listes
Ressource getRessource(int index, Liste l);
Ressource getRessource_ID(char * ID, Liste l);
Liste getRessource_Type (char * type, Liste l);
Liste getRessource_Nom (char * nom, Liste l);
Liste getRessource_Date (Date date, Liste l);

#endif
