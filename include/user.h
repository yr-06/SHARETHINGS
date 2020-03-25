#define __USER_H__


//structures:

typedef struct compte_u *user;

//liste des fonctions:
//getters
char * get_nom(user u); //permet de recuperer le nom de l'utilisateur
char * get_prenom(user u);//permet de recuperer le prenom de l'utilisateur
char * get_mdp(user u);//permet de recuperer le mot de passe de l'utilisateur
char * get_ID(user u);//permet de recuperer l'identifiant de l'utilisateur

//setters
void set_nom(user u, char * nom);//associe le nom entré à l'utilisateur en param
void set_prenom(user u, char * prenom);//associe le prenom entré à l'utilisateur en param
void set_mdp(user u, char * mdp);//associe le mot de passe entré à l'utilisateur en param
void set_ID(user u, char * ID);//associe l'identifiant entré à l'utilisateur en param 

//gestion du compte
user changer_donnees(user u, int choix); //permet de changer les donnees liees a son compte
void suppr_compte(user u);//supprime le compte d'un utilisateur


