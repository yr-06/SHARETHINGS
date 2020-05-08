#ifndef __AFFICHAGEADMIN_H__
#define __AFFICHAGEADMIN_H__

 #include "ressources.h"

void messwelcomeAdmin(Personne p);
void messByeAdmin(Personne p);
void messErrorRedirection();
void messQuit();

void init_mtp_admin();


void choix_admin(Annuaire annu,Liste ls,Personne p);
void menuAdmin(Annuaire annu,Liste ls,Personne p);
void welcomeAdmin(Annuaire annu,Liste ls,Personne p);
#endif
