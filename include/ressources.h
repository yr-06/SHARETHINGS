#ifndef __RESSOURCES_H__
#define __RESSOURCES_H__


//structures:
typedef struct s_ressource *Ressource; 
typedef struct s_elementl *Elementl;
typedef struct s_liste *Liste;

//getters 

char * getID(ressources r); //récupère l'identifiant relié à une ressource
char * getDropBy(ressources r);//récupére l'information sur la disponibilité & la provenance d'une ressource
char * getTakenBy(ressources r);//meme principe & l'appartenance de la personne qui l'a pris
ressources getNextRessource(ressources r);//accès aux autres ressources

//setters
void setID(ressources r, char * ID);//associe l'ID entré à la ressource en paramètre
void setType(ressources r, char * type);//associe un type de ressource à la ressource en paramètre

//fonctions 
ressources suppr_ressource(ressources r, ressources suppr);//supprime une ressource
char ressource_dispo(ressources r);//permet de savoir si un ressource est dispo
int nb_pret(s_pers p);//retourne le nombre de pret d'une personne
int nb_emprunt(s_pers p);//retourne le nombre d'emprunt d'une personne
void rappel_finEmprunt(ressources r);//affiche un message pour rappeler la date de fin d'emprunt 

Liste push_bl(Liste ls,int i, Elementl l)
Liste push_fl(Liste ls,Elementl l)
Liste pop_fl(Liste ls)
Liste pop_bl(Liste ls)
Liste insert_at(int i,Ressource ress,Liste ls)
Liste remove_at(int i,Liste ls)


