#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>
#include "../include/admi.h"
#include "../include/chiffrement.h"
#include "../include/personne.h"
#include "../include/ressources.h"

void welcomeAdmin(Personne p){
  printf("Bienvenue %s %s dans le menu administrateur!\n",get_name(p),get_prenom(p));
  printf("Que voulez-vous faire ?\n");
  printf("Ajouter un usager: 1\n Modifier les données d'un usager: 2\n Supprimer un usager: 3\n");
  printf("Afficher les données d'un usager: 4\n Afficher la liste des usagers:5\n Quitter: 0\n");
  
}