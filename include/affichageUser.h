#ifndef __AFFICHAGEUSER_H__
#define __AFFICHAGEUSER_H__
 
#include "personne.h" 
#include "ressources.h"

 //fonctions : 
char * getString(int size, char * requete);
void viderBuffer();
void modifRessource(Personne p, Ressource r, Liste l);
void modifDonneesPers(Personne p);
void welcomeUser(Personne p, Liste ressources);
void addRessourceAtListe(Personne p, Liste ressources);
void infoTakeRessource(Personne p, Ressource r, Liste ressources);


#endif
