#ifndef __RESSOURCES_H__
#define __RESSOURCES_H__

typedef int Bool ;  //définition du type booléen,

#define false  0 /* affectation des valeurs conventionnelles*/

#define true  1

#include "personne.h"


//structures
typedef struct s_ressource *Ressource;
typedef struct s_elementl *Elementl;
typedef struct s_liste *Liste;


//setters
void setType(Ressource r, char *type);
void setNom(Ressource r , char * nom);
void setID_r(Ressource r, char * ID);
void setTakenBy(Ressource r, char * takenBy);
void setDropBy(Ressource r, char * dropBy);
void setDateDeb(Ressource r, char * date_d);
void setDateFin(Ressource r, char * date_f);

//getters
char * getTypeRessource(Ressource r);
char * getNom(Ressource r);
char * getID_r(Ressource r);
char * getDropBy(Ressource r);
char * getTakenBy(Ressource r);
char * getRessourceDispo(Ressource r);
char * getDateDebut(Ressource r);
char * getDateFin(Ressource r);


//fonctions sur Ressource
int isDispo(Ressource r);
Ressource initRessource();
int haveRessource(Personne p, Ressource r);
char * generateID(Liste ressources);
void gererDropRessource(Personne p, Liste l);

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

//getters sur les listes
Ressource getRessource(int index, Liste l);
Ressource getRessource_ID(char * ID, Liste l);

#endif
