#ifndef __RESSOURCES_H__
#define __RESSOURCES_H__

//structures
typedef struct s_ressource *Ressource;
typedef struct s_elementl *Elementl;
typedef struct s_liste *Liste;

//setters
void setType(Ressource r, char * type);
void setNom(Ressource r, char * nom);
void setDateDeb(Ressource r, char * date_d);
void setTakenBy(Ressource r, char * takenBy);

//getters
char * getType(Ressource r);
char * getNom(Ressource r);
char * getDateDeb(Ressource r);
char * getTakenBy(Ressource r);
char * getRessourceDispo(Ressource r);

//fonctions sur Ressource
int isDispo(Ressource r);
Ressource initRessource();

//fonctions sur Liste :
int getIndex(Ressource r, Liste l);
Ressource getRessouce(int index, Liste l);


#endif
