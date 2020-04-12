#ifndef __RESSOURCES_H__
#define __RESSOURCES_H__

//structures
typedef struct s_ressource *Ressource;
typedef struct s_elementl *Elementl;
typedef struct s_liste *Liste;
typedef enum{
    false,
    true
}Bool;

//setters
void setType(Ressource r, char *type);
void setNom(Ressource r , char * nom);
void setID(Ressource r, char * ID);
void setTakenBy(Ressource r, char * takenBy);
void setDropBy(Ressource r, char * dropBy);
void setDateDebut(Ressource r, char * date_d);
void setDateFin(Ressource r, char * date_f);
//void setDateCrea(Ressource r,char* date_crea);

//getters
char * getTypeRessource(Ressource r);
char * getNom(Ressource r);
char * getID(Ressource r);
char * getDropBy(Ressource r);
char * getTakenBy(Ressource r);
char * getRessourceDispo(Ressource r);
char * getDateDebut(Ressource r);
char * getDateFin(Ressource r);
//char*getDateCrea(Ressource r);

//modifyer
void modifType(Ressource r);
void modifNom(Ressource r);
void modifDispo(Ressource r);
void modifTakenBy(Ressource r);


//fonctions sur Ressource
int isDispo(Ressource r);
Ressource initRessource();

//fonctions sur Liste :
int getIndex(Ressource r, Liste l);
Ressource getRessouce(int index, Liste l);
void removeRessource(Ressource r,Liste l);

//int haveRessource(Personne p)
//void retirerRessource(Ressource r, Personne p)-->ces 2 fct vont ds user.c

//Fonctions sur les manipulations de Liste

Liste new_list();
Bool is_empty_list(Liste l);
int list_size(Liste l);
void print_list(Liste l);

Liste push_bl(Liste l,Ressource r);
Liste push_fl(Liste l,Ressource r);
Liste pop_bl(Liste l);
Liste pop_fl(Liste l);
Liste clear_list(Liste l);
Liste insert_at_l(int i,Ressource r, Liste ls);
Liste remove_at_l(int i,Liste ls);


/*//modifyer
void modifType(Ressource r)
void modifNom(Ressource r)
void modifDate_Deb(Ressource r)
void modifDate_Fin(Ressource r)
void modif_ress(Ressource r)
Ressource create_ress()
void affich_ress(Ressource r);
*/

#endif
