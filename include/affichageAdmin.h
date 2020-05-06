#ifndef __AFFICHAGEADMIN_H__
#define __AFFICHAGEADMIN_H__

void welcomeMenuAdmin(Personne p);

//Operation Done
void messAccountCreated();
void messModifDone();

//Notifications
void messEmptyAnnu_print();
void messSeeAnnu();
void messCannotSuppr();
void messAskAdmin();
void messSatisfied();
void messWarnID();

//Messages d'erreur
void messErrorMail();
void messErrorTel();
void messErrorRedirection();


#endif
