#ifndef __RESSOURCES_H__
#define __RESSOURCES_H__


//structures:
typedef struct s_ressource *Ressource; 
typedef struct s_elementl *Elementl;
typedef struct s_liste *Liste;

//getters
char*getType(Ressource r)
char * getNom(Ressource r)
int getDispo(Ressource r)
char * getID(Ressource r)
char * getTakenBy(Ressource r)
char * getDropBy(Ressource r)
char * getID(Ressource r) //récupère l'identifiant d'une ressource
char * getDropBy(Ressource r)//récupére l'identifiant du propriétaire d'une ressource
char * getTakenBy(Ressource r)////récupére l'identifiant de l'emprunteur
char * getDateDebut(Ressource r)
char * getDateFin(Ressource r)

//setters
void setType(Ressource r,char*type)//associe un type de ressource à la ressource en paramètre
void setName(Ressource r,char*name)
void setDispo(Ressource r, int d)
void setID(Ressource r,char*id)//associe l'ID entré à la ressource en paramètre
void setTakenBy(Ressource r, char * takenBy)
void setDropBy(Ressource r, char * dropBy)
void setDateDebut(Ressource r, char * date_d)
void setDateFin(Ressource r, char * date_f)

void modifNom(Ressource r)
void modifDispo(Ressource r)
void modifTakenBy(Ressource r)
void modifDate_Deb(Ressource r)
void modifDate_Fin(Ressource r)

Liste pop_fl(Liste ls)
Liste pop_bl(Liste ls)

Liste insert_at(int i,Ressource ress,Liste ls)
Liste remove_at(int i,Liste ls)

Ressource create_ress()
void affich_ress(Ressource r)
void affich_list_ress(Liste ls,FILE*f)

Liste add_ress(Liste ls,Ressource ress)
Liste remove_ress(Liste ls, Ressource ress)

Ressource getRessource(int index, Liste l)
Ressource search_ress(Liste ls, char * id)
void search_ress_type(Liste ls,char*type)

int getIndex(Liste l,Ressource r)
int ress_existing (Liste ls, Ressource r)