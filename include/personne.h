#ifndef __PERSONNE__H
#define __PERSONNE__H


typedef struct s_pers *Personne;

void viderBuffer2();
//getters

int getNumAccount(Personne p);

int getAutor(Personne p);

char *getName(Personne p);

char *getPrenom(Personne p);

char *getNaiss(Personne p);

char *getIDPers(Personne p);

char *getPwd(Personne p);

char *getMail(Personne p);

char *getTel(Personne p);


 //setters
void setNumAccount(Personne p, int i);

void setAutor(Personne p);

void setName(Personne p,char *name);

void setPrenom(Personne p,char *prenom);

void setNaiss(Personne p,char *date);

void setIDPers(Personne p,char *id);

void setPwd(Personne p,char *pwd);

void setMail(Personne p,char *mail);

void setTel(Personne p,char *tel);

void setPers(Personne p, int num,int a ,char*name,char*prenom,char*date,char*id,char*pwd,char*mail,char*tel);

void modif_name(Personne p);

void modif_prenom(Personne p);

void modif_naiss(Personne p);

void modif_pwd(Personne p);

void modif_mail(Personne p);

void modif_tel(Personne p);

Personne initPers();

Personne create_pers();

char *createIDPers(Personne p);

void affich_pers(Personne p);
    
void modif_persAdmin(Personne p);

void modif_persUser(Personne p);

void print_pers_JSON(Personne p);

void addPersAnnu_JSON(Personne p);

Personne LoadPersonne_JSON(char *ID);

void suppr_pers_JSON(char *ID);

#endif
