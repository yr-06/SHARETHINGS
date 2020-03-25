#ifndef __RESSOURCES_H__
#define __RESSOURCES_H__


//structures:
typedef struct s_ressource *Ressource; 
typedef struct s_elementl *Elementl;
typedef struct s_liste *Liste;

//getters 

char * getID(Ressource r); //récupère l'identifiant relié à une ressource
char * getDropBy(Ressource r);//récupére l'information sur la disponibilité & la provenance d'une ressource
char * getTakenBy(Ressource r);//meme principe & l'appartenance de la personne qui l'a pris
char * getType(Ressource r);
char * getNom(Ressource r);
char * getRessourceDispo(Ressource r);
char * getDateDebut(Ressource r);
char * getDateFin(Resource r);
ressources getNextRessource(ressources r);//accès aux autres ressources

//setters
void setTakenBy(Ressource r, char * takenBy);
void setDateDebut(Ressource r, char * date_d);
void setDateFin(Ressource r, char * date_f);

//fonctions 
ressources suppr_ressource(ressources r, ressources suppr);//supprime une ressource
int isDisp(Ressource r);//permet de savoir si un ressource est dispo
void removeRessource(Ressource r, Liste l);//retourne le nombre de pret d'une personne


Liste push_bl(Liste ls,int i, Elementl l);
Liste push_fl(Liste ls,Elementl l);
Liste pop_fl(Liste ls);
Liste pop_bl(Liste ls);
Liste insert_at(int i,Ressource ress,Liste ls);
Liste remove_at(int i,Liste ls);

int getIndex(Ressource r, Liste l);
Ressource getRessource(int index, Liste l);
