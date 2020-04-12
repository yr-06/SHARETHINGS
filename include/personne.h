#ifndef PERSONNE__H
#define PERSONNE__H
typedef struct s_pers *Personne;

typedef struct s_elementa *Elementa;

//getters
int getNumAccount(Personne p);
/*----------------------------------------------------------------*/
int getAutor(Personne p);
/*----------------------------------------------------------------*/
char*getName(Personne p);
/*----------------------------------------------------------------*/
char*getPrenom(Personne p);
/*----------------------------------------------------------------*/
char*getNaiss(Personne p);
/*----------------------------------------------------------------*/
char*getID(Personne p);
/*----------------------------------------------------------------*/
char*getPwd(Personne p);
/*----------------------------------------------------------------*/
char*getMail(Personne p);
/*----------------------------------------------------------------*/
char*getTel(Personne p);
/*----------------------------------------------------------------*/
int getPossess(Personne p);
/*----------------------------------------------------------------*/
//int getNbPret(Personne p);
/*----------------------------------------------------------------*/

 //setters
void setNumAccount(Personne p, int i);
/*void setAutor(Personne p,FILE*f)*/
void setAutor(Personne p,int i);//version utilisée pour phase de tests
/*----------------------------------------------------------------*/
void setName(Personne p,char*name);
/*----------------------------------------------------------------*/
void setPrenom(Personne p,char*prenom);
/*----------------------------------------------------------------*/
void  setNaiss(Personne p, char*date);
/*----------------------------------------------------------------*/
void setID(Personne p,char*id);
/*----------------------------------------------------------------*/
void setPwd(Personne p,char*pwd);
/*----------------------------------------------------------------*/
void setMail(Personne p,char*mail);
/*----------------------------------------------------------------*/
void setTel(Personne p,char*tel);
/*----------------------------------------------------------------*/
/*void setPossess(Personne p,int i)*/
/*----------------------------------------------------------------*/

//Fonctions permettants de modifier données d'une personne
void modif_name(Personne p);
/*----------------------------------------------------------------*/
void modif_prenom(Personne p);
/*----------------------------------------------------------------*/
void modif_naiss(Personne p);
/*----------------------------------------------------------------*/
void modif_id(Personne p);
/*----------------------------------------------------------------*/
void modif_pwd(Personne p);
/*----------------------------------------------------------------*/
void modif_mail(Personne p);
/*----------------------------------------------------------------*/
void modif_tel(Personne p);
/*----------------------------------------------------------------*/
Personne initPers();
/*----------------------------------------------------------------*/
Personne create_pers(FILE*f);//enlever FILE*f pour tester pour le moment 
/*----------------------------------------------------------------*/
void affich_pers(Personne p);
/*----------------------------------------------------------------*/
void modif_persAdmin(Personne p,FILE*f);
/*----------------------------------------------------------------*/
void modif_persUser(Personne p);
#endif
