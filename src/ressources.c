#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "../include/ressources.h"
#include "../include/personne.h"
#include "../include/affichageUser.h"
#include "../include/date.h"
#include "../include/parson.h"


#ifndef COLOR
    #define color(param) printf("\033[%sm",param)
#endif

//structures
struct s_ressource{                        
    char *type;
    char nom[32];//nom de la ressource
    char *ID ;//= ID de la ressource
    char *takenBy;// = ID de l'utilisateur qui a pris la ressource.
    char *dropBy;// = ID de l'utilisateur qui a déposé la ressource.
    Date date_d;//date de debut du pret
    Date date_f;//date de fin du pret
    Date creation;
};

struct s_elementl{
  int i;
  Ressource r;
  struct s_elementl *previous;
  struct s_elementl *next;
};

struct s_liste{
  int size;
  Elementl head;
  Elementl tail;
};

//fonctions :
//setters

void setType(Ressource r, char * type){
  strcpy(r->type,type);
}

void setNom(Ressource r , char * nom){
  strcpy(r->nom, nom);
}

void setDateDeb(Ressource r, Date date_d){
  r->date_d=date_d;
}


void setTakenBy(Ressource r, char * takenBy){
  strcpy(r->takenBy, takenBy);
}

void setDropBy(Ressource r, char * dropBy){
  strcpy(r->dropBy, dropBy);
}

void setCreateDate(Ressource r, Date date){
  r->creation=date;
} 

void setDateFin(Ressource r, Date date_f){
  r->date_f=date_f;
}

//getters

char * getType(Ressource r){
  return (r->type);
}

char * getNom(Ressource r){
  return(r->nom);
}

Date getDateDeb(Ressource r){
  return(r->date_d);
}

Date getDateFin(Ressource r){
  return(r->date_f);
}

Date getDateCrea(Ressource r){
  return(r->creation);
}

char * getTakenBy(Ressource r){
  return(r->takenBy);
}

char * getDropBy(Ressource r){
  return(r->dropBy);
}

char * getID_r(Ressource r){
  return(r->ID);
}


char * getRessourceDispo(Ressource r){
  if(isDispo(r) == 1){
    color("32;1");
    return "La ressource est disponible";
  }
  return getTakenBy(r);
}

char * getRessourceHave(Personne p , Ressource r){
  if(haveRessource(p, r)== 1){
    color("32;1");
    return "Cette ressource vous appartient. Vous pouvez la modifier.";
  }
  color("31;1");
  return "Cette ressource ne vous appartient pas. Vous ne pouvez pas la modifier";
}

int getPossess(Personne p, Liste ressources){
    return list_size(depotRessource(p,ressources));
}

int getEmprunt(Personne p, Liste ressources){
  return list_size(empruntRessource(p,ressources));
}

//fonctions liées à ressource
//fonction d'initialisation
Ressource initRessource(Liste ressources){
  Ressource r = (Ressource)malloc(sizeof(struct s_ressource));
  (r->type) =(char*)malloc(sizeof(char)*33);
  (r->takenBy) =(char*)malloc(sizeof(char)*33);
  (r->dropBy)=(char*)malloc(sizeof(char)*33);
  (r->date_d) =initDate();
  (r->date_f) =initDate();
  (r->creation)=initDate();
  r->ID = generateID(ressources);
  push_bl(ressources, r);
  return r;
}

int isDispo(Ressource r){
  if(strcmp(getTakenBy(r), "") == 0){
    return 1;
  }
  return 0;
}


int haveRessource(Personne p, Ressource r){
  if(strcmp(getIDPers(p), getDropBy(r)) == 0){
    return 1;
  }
  return 0;
}

//fonction qui génère un ID pour une  ressource en char*
char * generateID(Liste ressources){
  srand(time(NULL)); // initialisation de rand
  int i; 
  char* newabc = (char*)calloc(8, sizeof(char));
  for (i = 0; i < 8; ++i) {
    newabc[i] = 'a' + (rand() % 26);
  }

 if(getRessource_ID(newabc,ressources)!= NULL){
    return generateID(ressources);
  }
  return newabc;
}

/*----------------------------------------------------------------*/


//fonctions  JSON pour ressources.c---> surtt ne pas modifier
void print_ress_JSON(Ressource r){
    char path[64];
    sprintf(path,"../data/Ressources/%s.json",getID_r(r));
    
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    char *serialized_string = NULL;
    FILE *fjson = NULL;

    fjson = fopen(path,"w+");
    
    json_object_set_string(root_object, "Type",getType(r));
    json_object_set_string(root_object, "Nom", getNom(r));
    json_object_set_string(root_object, "ID",getID_r(r));
    json_object_set_string(root_object, "Propriétaire",r->dropBy);
    
    //date de création
    json_object_set_number(root_object, "Jour de Création",getDayofDate(r->creation));
    json_object_set_number(root_object, "Mois de Création",getMonthofDate(r->creation));
    json_object_set_number(root_object, "Année de Création",getYearofDate(r->creation));

    json_object_set_number(root_object, "Statut",isDispo(r));
    json_object_set_string(root_object, "Emprunté par",getTakenBy(r));
    
    //date de début de prêt
    json_object_set_number(root_object, "Jour du début de prêt",getDayofDate(r->date_d));
    json_object_set_number(root_object, "Mois du début de prêt",getMonthofDate(r->date_d));
    json_object_set_number(root_object, "Année du début de prêt",getYearofDate(r->date_d));

    //date de fin de prêt
    json_object_set_number(root_object, "Jour de fin de prêt",getDayofDate(r->date_f));
    json_object_set_number(root_object, "Mois de fin de prêt",getMonthofDate(r->date_f));
    json_object_set_number(root_object, "Année de fin de prêt",getYearofDate(r->date_f));
    
    serialized_string = json_serialize_to_string_pretty(root_value);
    fprintf(fjson,"%s",serialized_string);
    fclose(fjson);
    json_free_serialized_string(serialized_string);
    json_value_free(root_value);
   
}//fonctionne

void addRessListe_JSON(Ressource r){
    FILE *Listef = NULL;
    Listef = fopen("../data/Ressources/Liste.dat","a");
    fprintf(Listef,"%s,%s,%s,%s \n",strtok(getID_r(r),"\n"),strtok(getType(r),"\n"),strtok(getNom(r),"\n"),strtok(r->dropBy,"\n"));
    fclose(Listef);
}//fonctionne

void updateListe_JSON(Liste ls){
	FILE * file = fopen("../data/Ressources/Liste.dat","w+");
    rewind(file);
    Elementl current_l=ls->head;
    int i;
    for(i=0;i<ls->size;i++){
        addRessListe_JSON(current_l->r);
        current_l=current_l->next;
    }
    fclose(file);
}//fonctionne

Ressource LoadRessource_JSON(char *ID){
    Ressource r =(Ressource)malloc(sizeof(struct s_ressource));
    (r->type) =(char*)malloc(sizeof(char)*33);
    (r->ID)=(char*)malloc(sizeof(char)*33);
    (r->creation)=initDate();
    (r->takenBy) =(char*)malloc(sizeof(char)*33);
    (r->dropBy)=(char*)malloc(sizeof(char)*33);
    (r->date_d)=initDate();
    (r->date_f)=initDate();

    JSON_Value *root_value;
    JSON_Object *root_object;
    char path[64];
    sprintf(path,"../data/Ressources/%s.json",ID);
    root_value = json_parse_file(path);
    root_object = json_value_get_object(root_value);
    
    setType(r,(char*)json_object_get_string (root_object,"Type"));
    setNom(r ,(char*)json_object_get_string (root_object,"Nom"));
    strcpy(r->ID,(char*)json_object_get_string (root_object,"ID"));

    //date de creation
    
    char *jc=(char *)malloc(sizeof(char)*3);
    char *mc=(char *)malloc(sizeof(char)*3);
    char *yc=(char *)malloc(sizeof(char)*5);
    sprintf(jc,"%d",(int)json_object_get_number (root_object,"Jour de Création"));
    sprintf(mc,"%d",(int)json_object_get_number (root_object,"Mois de Création")); 
    sprintf(yc,"%d", (int)json_object_get_number (root_object,"Année de Création"));
    (r->creation)=setTime(jc,mc,yc);
    
    setDropBy(r,(char*)json_object_get_string (root_object,"Propriétaire"));
    
    setTakenBy(r,(char*)json_object_get_string (root_object,"Emprunté par"));
      
    //date de début de prêt
    char *jdd=(char *)malloc(sizeof(char)*3);
    char *mdd=(char *)malloc(sizeof(char)*3);
    char *ydd=(char *)malloc(sizeof(char)*5);
    sprintf(jdd,"%d",(int)json_object_get_number (root_object,"Jour du début de prêt"));
    sprintf(mdd,"%d",(int)json_object_get_number (root_object,"Mois du début de prêt")); 
    sprintf(ydd,"%d",(int)json_object_get_number (root_object,"Année du début de prêt"));
    (r->date_d)=setTime(jdd,mdd,ydd);

    //date de fin de prêt
    char *jdf=(char *)malloc(sizeof(char)*3);
    char *mdf=(char *)malloc(sizeof(char)*3);
    char *ydf=(char *)malloc(sizeof(char)*5);
    sprintf(jdf,"%d",(int)json_object_get_number (root_object,"Jour de fin de prêt"));
    sprintf(mdf,"%d",(int)json_object_get_number (root_object,"Mois de fin de prêt")); 
    sprintf(ydf,"%d",(int)json_object_get_number (root_object,"Année de fin de prêt"));
    (r->date_f)=setTime(jdf,mdf,ydf);

    
    return r;
}//fonctionne-->tt les champs de la structure doivent être initialisé et enregistrée dasn le fichier JSON pour que le chargement soit possible

void suppr_ress_JSON(char *ID){
    char path[64];
    sprintf(path,"../data/Ressources/%s.json",ID);
    remove(path);
}//fonctionne

Liste LoadListe_JSON(Liste ls){
    char line[160];
 
    FILE*f = fopen("../data/Ressources/Liste.dat","r");
    rewind(f);
    if(f!= NULL){
        while (!feof(f)){
            if(fgets(line,160,f)!=NULL){
                Ressource r=LoadRessource_JSON(strtok(line,","));
                ls=push_bl(ls,r);
           }else{
               continue;
            }
        }
    }else{
        fprintf(stderr, "Erreur :Impossible d'ouvrir le fichier.\n");
		exit(EXIT_FAILURE);
    }
    return ls;
}//fonctionne
/*----------------------------------------------------------------*/


//fonctions sur les listes
//fonction initialisation liste
Liste new_list(){
  Liste l =(Liste)malloc(sizeof(struct s_liste));
  if(l== NULL){
    fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
    exit(EXIT_FAILURE);
  }
  l->size= 0;
	return l;
}

//permet de savoir si une liste est vide
int is_empty_list(Liste l){
	if(l->size== 0)
		return 1;

	return 0;
}

//permet de savoir la taille d'une liste
int list_size(Liste l){
	if(is_empty_list(l))
		return 0;

	return l->size;
}

//affiche les infos liées à une ressource
void affich_ress(Ressource r){
    color("37;1");
    printf("\nVoici le récapitulatif des données liées à cette ressource:\n");
    color("37;1");
    printf("Type: %s\n", getType(r));
    printf("Nom: %s\n", getNom(r));
    printf("ID: %s\n", getID_r(r));
    printf("Propriétaire: %s\n",getDropBy(r));
		printf("Créée le: ");
    affichTime(getDateCrea(r));
    printf("\n");
    printf("\n");
   
    if(isDispo(r)==0){
        printf("Statut: Emprunté\n");
        printf("Emprunté par: %s\n", getTakenBy(r));
       printf("Date de début du pret: ");
        affichTime(getDateDeb(r));
        printf("\n");
        printf("Date de fin du pret: ");
        affichTime(getDateFin(r));
        printf("\n");
    }else{
         printf("Statut: Disponible\n\n");
    }
}

//permet d'afficher une liste
void print_list(Liste l){
  if(is_empty_list(l)){
      color("31;1");
      printf("Rien à afficher, la liste est vide.\n");
      color("37");
	  return;
	}
	Elementl temp = l->head;
	while(temp != NULL){
      affich_ress(temp->r);
	  temp = temp->next;
	}
	printf("\n");
}

//ajouter un élèment en bout de liste: 
Liste push_bl(Liste l,Ressource r){
	Elementl element = malloc(sizeof(struct s_elementl));
  if(element == NULL){
      fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
	  exit(EXIT_FAILURE);
	}

	element->r=r;
	element->next=NULL;
	element->previous = NULL;

	if(is_empty_list(l)){
		l->head= element;
		l->tail= element;
	}
	else{
		l->tail->next = element;
		element->previous = l->tail;
		l->tail= element;
	}
  l->size++;
  return l;
}

//ajoute un élèment en début de liste
Liste push_fl(Liste l,Ressource r){
	Elementl element = malloc(sizeof(struct s_elementl));
	if(element == NULL){
		fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}

	
	element->r =r;
	element->next = NULL;
	element->previous = NULL;

	if(is_empty_list(l)){   
        l->head = element;
		l->tail= element;
	}
	else{
		l->head->previous = element;
		element->next = l->head;
		l->head=element;
	}
  l->size++;
	return l;
}

//supprime un élèment en bout de liste
Liste pop_bl(Liste l){
	if(is_empty_list(l)){
    color("31;1");
		printf("Rien à supprimer, la liste est déjà vide.\n");
    color("37");
		return new_list();
	}

	if(l->head == l->tail){
		free(l);
        l=new_list();
        return l;
	}

	Elementl temp = l->tail;

	l->tail=l->tail->previous;
	l->tail->next = NULL;
	temp->next = NULL;
	temp->previous= NULL;
    
    free(temp->r);
    free(temp);
	temp = NULL;

	l->size--;

	return l;
}//-->good color

//supprimer un élèment en début de liste
Liste pop_fl(Liste l){
	if(is_empty_list(l)){
    color("31;1");
		printf("Rien à supprimer, la liste est déjà vide.\n");
    color("37");
		return new_list();
	}

	if(l->head == l->tail){
		free(l);
		l =new_list();
		return l;
	}

	Elementl temp = l->head;

	l->head = l->head->next;
	l->head->previous = NULL;
	temp->next = NULL;
	temp->previous= NULL;

	free(temp);
	temp = NULL;

	l->size--;

	return l;
}//-->good color

//permet de vider une liste
Liste clear_list(Liste l){
	while(!is_empty_list(l))
		l = pop_bl(l);

	return new_list();
}

//insère une ressource à un indice précis de la liste
Liste insert_at_l(int i,Ressource r, Liste ls){
    assert((i<=ls->size)&&(i>=0));
    int t=(ls->size)-1;
    if(i==0){
        return (push_fl(ls,r));
    }
   if(i==t){
       return (push_bl(ls,r));
    }else{
        Elementl l=(Elementl)malloc(sizeof(struct s_elementl));
        l->r=initRessource(ls);
        l->r=r;
        int j=0;
        Elementl current_l=ls->head;
        for(j=0;j<i;j++){
            current_l=current_l->next;
        }
        current_l->previous->next=l;
        l->previous=current_l->previous;
        current_l->previous=l;
        l->next=current_l;
        ls->size++;
        return ls;
    }
}

//supprime à un indice précis de la liste
Liste remove_at_l(int i,Liste ls){
    assert((i<ls->size)&&(i>=0));
    int t=(ls->size)-1;
    if(i==0){
        return (pop_fl(ls));
    }
    if(i==t){
        return (pop_bl(ls));
    }else{
         int j=0;
            Elementl current_l=ls->head;
            for(j=0;j<i;j++){
                current_l=current_l->next;
            }
            current_l->previous->next=current_l->next;
            current_l->next->previous=current_l->previous;
            free(current_l);
            ls->size--;
            return ls;
    }
}


Elementl getHead(Liste l){
	return (l->head);
}

Ressource getCurrentRessource(Elementl e){
	return(e->r);
}

Elementl getNext(Elementl e){
	return(e->next);
}


//permet de savoir si une ressource existe
int ress_existing(Liste ls, Ressource r){
    Elementl current_l=ls->head;
    int j=ls->size;
    int i;
    for (i=0;i<j;i++){
        if(strcmp(getID_r(r),getID_r(current_l->r))==0){
            return 1;
         }
         if(strcmp(getType(r),getType(current_l->r))==0){
             if (strcmp(getNom(r),getNom(current_l->r))==0){
                    if(strcmp(getDropBy(r),getDropBy(current_l->r))==0){
                      return 2;
                 }
             }
         }
        
         current_l=current_l->next;
    }
    return 0;
}  

//permet de supprimer une ressource grace à l'indice dans une liste
void removeRessource(Ressource r,Liste l){
  if(isDispo(r)==1){
      
    remove_at_l(getIndex(r,l), l);
    return;
  }
  color("31;1");
  printf("La ressource est empruntée, vous ne pouvez pas la supprimer\n");
  color("37");
}//-->good c

//getters sur les listes

//fonction qui récupère l'indice d'une ressource dans une liste de ressources.
int getIndex(Ressource r, Liste l){
	int pos = 0;
	Elementl current = l->head;
	for(int i = 0; i<(l->size);i++){
		if(r == current->r){
			pos = i;
		}
		current=current->next;
	}
	return pos;
}

//retourne la liste de ressources déposées
Liste depotRessource(Personne p,Liste ressources){ 
	Liste depot = new_list();
	Elementl current = ressources->head;
	for(int i=0; i<list_size(ressources);i++){
	  if(haveRessource(p, current->r)== 1){
	    push_bl(depot, current->r);
	  }
	  current = current-> next;
	}
	return depot;
}

//retourne la liste de ressources empruntées
Liste empruntRessource(Personne p,Liste ressources){ 
	Liste emprunt = new_list();
	Elementl current = ressources->head;
	for(int i=0; i<list_size(ressources);i++){
	  if(strcmp(getTakenBy(current->r), getIDPers(p))==0){
	    push_bl(emprunt, current->r);
	  }
	  current = current-> next;
	}
	return emprunt;
}

//permet de pouvoir sélectionner une ressource qui nous appartient
void gererDropRessource(Personne p, Liste l){
  int choix;
  color("36;1");
  printf("Vous avez %d ressource(s) déposée(s).\n", getPossess(p, l));
  color("36;1");
  printf("Selectionnez un des numéros suivants. \n");
  color("37;1");
  printf("(-1) Revenir en arrière.\n");

  Liste depots = depotRessource(p, l);
  Elementl current = depots->head;
  for(int i =0; i<list_size(depots); i++){
    printf("( %d) %s\n",i,getNom(current->r));
    current = current ->next;
  }

  scanf("%d", &choix);
  if(choix == -1){
    welcomeUser(p, l);
    return;
  }
  Ressource r = getRessource(choix, depots);
  if(r == NULL || haveRessource(p, r) == 0){
    color("31;1");
    printf("Numéro incorrect. Réessayez!");
    color("37");
    gererDropRessource(p, l);
    return;
  }
  modifRessource(p, r,l);
}//-->good c


//permet de gérer les ressources empruntées
void gererTakeRessource(Personne p, Liste l){
  int choix;
  color("36;1");
  printf("Vous avez %d ressource(s) empruntée(s).\n", getEmprunt(p, l));
  color("36;1");
  printf("Selectionnez un des numéros suivants. \n");
  color("37;1");
  printf("(-1) Revenir en arrière.\n");

  Liste emprunts = empruntRessource(p, l);
  Elementl current = emprunts->head;
  for(int i =0; i<list_size(emprunts); i++){
    printf("( %d) %s\n",i,getNom(current->r));
    current = current ->next;
  }

  scanf("%d", &choix);
  if(choix == -1){
    welcomeUser(p, l);
    return;
  }
  Ressource r = getRessource(choix, emprunts);
  if(r == NULL || isDispo(r) == 1){
    color("31;1");
    printf("Numéro incorrect. Réessayez!\n");
    color("37");
    gererTakeRessource(p, l);
    return;
  }
  infoTakeRessource(p,r,l);
}//-->good c


//fonction pour emprunter une ressource
void takeRessource(Personne p, Liste l){
  int choix;
  Elementl current = l->head;

  color("36;1");
  printf("Selectionnez un des numéros suivants. \n");
  color("37;1");
  printf("(-1) Revenir en arrière.\n");
  for(int i =0; i<list_size(l); i++){
    if(isDispo(current-> r) == 1){
      printf("( %d) %s\n",i,getNom(current->r));
    } 
    current = current ->next;
  }
  scanf("%d", &choix);
  if(choix == -1){
    welcomeUser(p, l);
    return;
  }
  Ressource r = getRessource(choix, l);
  if(r == NULL || isDispo(r) == 0){
    color("31;1");
    printf("Numéro incorrect. Réessayez!");
    color("37;1");
    takeRessource(p, l);
    return;
  }
  color("32;1");
  printf("Vous venez d'emprunter %s pour 6 semaines. \n", getNom(r));
  color("37;1");
  setTakenBy(r, getIDPers(p));

  setDateFin(r, getDelayedTime());
  setDateDeb(r, getActualTime());
  print_ress_JSON(r);

  welcomeUser(p, l);
}//-->good c


//fonction qui récupère une ressource à partir d'un indice dans une liste de ressources.
Ressource getRessource(int index, Liste l){
	Elementl current = l->head;
  if(index>=list_size(l) || index <0){
    return NULL;
  }
	for(int i = 0;i<index; i++){
		current=current->next;
	}
	return current->r;

}

void searchRessourceByDate(Personne p, Liste ressources){
  int choix, day, month, year;
  char * sday;
  char * smonth;
  char * syear;

  sday =(char*)malloc(sizeof(char)*16);
  smonth =(char*)malloc(sizeof(char)*16);
  syear =(char*)malloc(sizeof(char)*16);

  color("36;1");
  printf("Entrez une nouvelle date au format JJ/MM/AAAA :\n");
  color("37;1");
  scanf("%02d/%02d/%4d",&day,&month,&year);
  
  viderBuffer();

  sprintf(sday, "%d", day);
  sprintf(smonth, "%d", month);
  sprintf(syear, "%d", year);

  Date date = setTime(sday, smonth, syear);

  Liste search = getRessource_Date(date, ressources);
  if(list_size(search) == 0){
    color("31;1");
    printf("Désolé rien ne correspond à votre recherche... Réessayez!\n");
    color("37;1");
    searchRessource(p, ressources);
    return;
  }
  color("36;1");
  printf("Voici les ressources trouvées: \n");
  color("37;1");
  printf("(-1) Revenir en arrière.\n");
  Elementl current = search->head;
  for(int i =0; i<list_size(search); i++){
    printf("( %d) %s\n",i,getNom(current->r));
    current = current ->next;
  }
  scanf("%d", &choix);
  if(choix == -1){
    welcomeUser(p, ressources);
    return;
  }

  Ressource r = getRessource(choix, search);
  if(r == NULL){
    color("31;1");
    printf("Numéro incorrect. Réessayez!");
    color("37;1");
    searchRessource(p, ressources);
    return;
  }
  affich_ress(r);
  welcomeUser(p,  ressources);
}//-->good c

//fonction qui permet de rechercher une ressource par le/la type/nom/date
void searchRessource(Personne p, Liste ressources){
  int choix;
  char * nom_type;
  Liste search;
  color("36;1");
  printf("Rechercher une ressource par: \n");
  color("37;1");
  printf("(0) Revenir en arrière\n");
  printf("(1) Nom.\n");
  printf("(2) Type.\n");
  printf("(3) Date.\n");
  color("36;1");
  printf("Selectionner votre choix de recherche: \n");
  color("37;1");
  scanf("%d",&choix);
  if(choix == 3){
    viderBuffer();
    searchRessourceByDate(p, ressources);
    return;
  }
  if (choix == 0){
    viderBuffer();
    welcomeUser(p,ressources);
    return;
  }
  if(choix != 1 && choix != 2){
    searchRessource(p, ressources);
    return;
  }
  color("37;1");
  printf("Entrer votre recherche: \n");
  viderBuffer();
  nom_type =(char*)malloc(sizeof(char)*128);
  strcpy(nom_type, "");
  char c = ' '; 
  while(strlen(nom_type)<128 && c != '\n'){
    scanf("%c", &c);
    if(c!='\n'){
      sprintf(nom_type, "%s%c", nom_type, c);
    }
  }
  switch(choix){
    case 1: 
      search = getRessource_Nom(nom_type, ressources);
      break;

    case 2:
      search = getRessource_Type(nom_type, ressources);
      break;

    default:
      break;
  }
  
  if(list_size(search)==0){
    color("31;1");
    printf("Désolé rien ne correspond à votre recherche... Réessayez !\n");
    color("37;1");
    searchRessource(p, ressources);
    return;
  }
  color("36;1");
  printf("Voici les ressources trouvées\n");
  color("37;1");
  printf("(-1) Revenir en arrière.\n");
  Elementl current = search->head;
  for(int i =0; i<list_size(search); i++){
    printf("( %d) %s\n",i,getNom(current->r));
    current = current ->next;
  }
  scanf("%d", &choix);
  if(choix == -1){
    welcomeUser(p, ressources);
    return;
  }

  Ressource r = getRessource(choix, search);
  if(r == NULL){
    color("31;1");
    printf("Numéro incorrect. Réessayez!");
    color("37;1");
    searchRessource(p, ressources);
    return;
  }
  affich_ress(r);
  welcomeUser(p, ressources);
}//-->good c


//fonction qui permet de récuperer une ressource avec un ID
Ressource getRessource_ID (char * ID, Liste l){
  Elementl current = l->head;
  for(int i =0; i<list_size(l); i++){
    if(strcmp(getID_r(current->r), ID) == 0){
      return current->r;
    } 
    current = current ->next;
  }
  return NULL;
}

//fonction qui permet de récuperer une ressource avec un type
Liste getRessource_Type (char * type, Liste l){
  Liste trouvees = new_list();
  Elementl current = l->head;
  for(int i =0; i<list_size(l); i++){
    if(strcmp(getType(current->r), type) == 0){
      push_bl(trouvees, current->r);
    } 
    current = current ->next;
  }
  return trouvees;
}

//fonction qui permet de récupérer une ressource avec un nom
Liste getRessource_Nom (char * nom, Liste l){
  Liste trouvees = new_list();
  Elementl current = l->head;
  for(int i =0; i<list_size(l); i++){
    if(strcmp(getNom(current->r), nom) == 0){
      push_bl(trouvees, current->r);
    } 
    current = current ->next;
  }
  return trouvees;
}

//fonction qui permet de récupérer une ressource avec une date
Liste getRessource_Date(Date date, Liste l){
  Liste trouvees = new_list();
  Elementl current = l->head;
  for(int i =0; i<list_size(l); i++){
    if(compareTime(getDateCrea(current->r), date) == 1){
      push_bl(trouvees, current->r);

    } else if(compareTime(getDateDeb(current->r), date) == 1){
      push_bl(trouvees, current->r);

    } else if(compareTime(getDateFin(current->r), date) == 1){
      push_bl(trouvees, current->r);
    } 
    current = current ->next;
  }
  return trouvees;
}

void afficherActions(Personne p, Liste l){
  int choix, day, month, year;
  Elementl current = l->head;

  char * sday;
  char * smonth;
  char * syear;

  sday =(char*)malloc(sizeof(char)*16);
  smonth =(char*)malloc(sizeof(char)*16);
  syear =(char*)malloc(sizeof(char)*16);

  color("36;1");
  printf("Entrer une nouvelle date au format JJ/MM/AAAA :\n");
  color("37;1");
  scanf("%02d/%02d/%4d",&day,&month,&year);
  
  viderBuffer();

  sprintf(sday, "%d", day);
  sprintf(smonth, "%d", month);
  sprintf(syear, "%d", year);

  Date date = setTime(sday, smonth, syear);
  color("36;1");
  printf("Actions à la date: ");
  color("37;1");//à voir
  affichTime(date);
  printf("\n");
  for(int i =0; i<list_size(l); i++){
    if(compareTime(getDateCrea(current->r), date) == 1){
      printf("Depôt de la ressource > %s\n", getNom(current->r));
    }
    if(compareTime(getDateDeb(current->r), date) == 1){
       printf("Emprunt de la ressource > %s\n", getNom(current->r));
    } 
    if(compareTime(getDateFin(current->r), date) == 1){
      printf("Fin d'emprunt de la ressource %s\n", getNom(current->r));
    }
    current = current ->next;
  }
  color("37;1");
  printf("Selectionner votre choix: \n");
  printf("(0) Revenir en arrière.\n");
  scanf("%d", &choix);
  switch(choix){
    case 0:
    default:
      welcomeUser(p, l);
      break;
  }
}


