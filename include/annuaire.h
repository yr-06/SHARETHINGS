#ifndef ANNUAIRE__H
#define ANNUAIRE__H
typedef struct s_annuaire *Annuaire;

typedef enum{
    false,
    true
}Bool;

Annuaire new_annu();//fonctionne
/*----------------------------------------------------------------*/
Bool is_empty_annu(Annuaire annu);//fonctionne
/*----------------------------------------------------------------*/
int annuaire_size(Annuaire annu);//fonctionne
/*----------------------------------------------------------------*/
void print_annu(Annuaire annu);//fonctionne->utile lors des tests de fonctions
/*----------------------------------------------------------------*/
Annuaire push_ba(Annuaire annu,Personne p);//fonctionne
/*----------------------------------------------------------------*/
Annuaire push_fa(Annuaire annu,Personne p);//fonctionne
/*----------------------------------------------------------------*/
Annuaire pop_ba(Annuaire annu);//fonctionne
/*----------------------------------------------------------------*/
Annuaire pop_fa(Annuaire annu);//fonctionne
/*----------------------------------------------------------------*/
Annuaire clear_annu(Annuaire annu);//fonctionne
/*----------------------------------------------------------------*/
Annuaire insert_at(int i,Personne p,Annuaire annu);//fonctionne-permet d'ajouter un Elementa à un indice précis de l'Annuaire
/*----------------------------------------------------------------*/
Annuaire remove_at(int i,Annuaire annu);//fonctionne-permet d'enlever un Elementa à un indice précis de l'Annuaire
/*----------------------------------------------------------------*/
//Fonctions sur listes de Personnes= type Annuaire à tester
int getIndicePersonne(Annuaire annu, Personne pers);//fonctionne-indice d'une personne ds l'Annuaire
/*----------------------------------------------------------------*/
int pers_existing(Annuaire annu, Personne p);//fonctionne-permet de vérifier si les données de la personne P ne sont pas déjà présentes
/*----------------------------------------------------------------*/
int createNumAccount(Annuaire annu);//permet d'initialiser le num de compte
/*----------------------------------------------------------------*/
void affichAnnuaire(Annuaire annu,FILE*f);//fonctionne (affichage ds fichier pas satisfaisant)
/*----------------------------------------------------------------*/
Annuaire add_pers(Annuaire annu,Personne pers);//fonctionne-permet d'ajouter une Personne n'existant pas encore à l'Annuaire
/*----------------------------------------------------------------*/
Annuaire remove_pers(Annuaire annu, Personne pers);//fonctionne-permet de supprimer une Personne de l'Annuaire
/*----------------------------------------------------------------*/
Personne search_pers(Annuaire annu, char * id);//fonctionne-permet de rechercher une personne ds un Annuaire à partir de son id 
/*----------------------------------------------------------------*/
Annuaire modifAnnuaireAdmin(Annuaire annu,Personne p);//à peaufiner
/*----------------------------------------------------------------*/
Annuaire modifAnnuaireUser(Annuaire annu,Personne p);//à peaufiner
/*----------------------------------------------------------------*/
Annuaire createAccount(Annuaire annu,FILE*f);//à tester
#endif