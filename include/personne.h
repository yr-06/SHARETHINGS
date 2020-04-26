#ifndef __PERSONNE__H
#define __PERSONNE__H

#include <time.h>

typedef struct tm *Date;

typedef struct s_pers *Personne;

typedef struct s_elementa *Elementa;


int getNumAccount(Personne p);

int getAutor(Personne p);

char *getName(Personne p);

char *getPrenom(Personne p);

Date getNaiss(Personne p);

char *getIDPers(Personne p);

char *getPwd(Personne p);

char *getMail(Personne p);

char *getTel(Personne p);

int getPossess(Personne p);

 //setters
void setNumAccount(Personne p, int i);

void setAutor(Personne p,FILE*f);

void setName(Personne p,char*name);

void setPrenom(Personne p,char*prenom);

void setNaiss(Personne p,Date d);

void setIDPers(Personne p,char*id);

void setPwd(Personne p,char*pwd);

void setMail(Personne p,char*mail);

void setTel(Personne p,char*tel);



void modif_name(Personne p);

void modif_prenom(Personne p);

void modif_naiss(Personne p);void modif_id(Personne p);

void modif_pwd(Personne p);

void modif_mail(Personne p);

void modif_tel(Personne p);


Personne initPers();

Personne create_pers(FILE*f);

void affich_pers(Personne p);

void modif_persAdmin(Personne p,FILE*f);

void modif_persUser(Personne p);

void print_pers_JSON(Personne p,FILE*f);

#endif
