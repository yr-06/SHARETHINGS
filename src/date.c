#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/date.h"

struct date_s{
    int tm_mday;
    int tm_mon;
    int tm_year;
};

//initialisation de la date
Date initDate(){
    return (Date)malloc(sizeof(struct date_s));
}

//Permet de retourner une date
Date setTime(char * day, char * month, char * year){
  Date date = initDate();
  int tm_mday = atoi(day);
  int tm_mon = atoi(month);
  int tm_year = atoi(year);

  date->tm_mday=tm_mday;
  date->tm_mon=tm_mon;
  date->tm_year=tm_year;
  
  return date;
}

//fonction qui ajoute un délai à la date de début de pret 
Date setDelayedTime(Date d){
    d->tm_mon+=1;
    d->tm_mday+=15;

    if(d->tm_mday>31){
        d->tm_mday-=31;
        d->tm_mon++;
    }
    return d;
}

// Recuperation de la date et l'heure actuelle.
Date getActualTime(){
  Date date;

  time_t temps;
  struct tm tm;

  time(&temps);
  tm=*localtime(&temps);

  char * day = (char*)malloc(sizeof(char)*3);
  char * month = (char*)malloc(sizeof(char)*3);
  char * year = (char*)malloc(sizeof(char)*5);

  strftime(day, 3, "%d",&tm);
  strftime(month, 3, "%m",&tm);
  strftime(year, 5, "%Y",&tm);

  date = setTime(day, month, year);

  return date;
}

//fonction qui affiche la date
void affichTime(Date date){
  printf("%.2d/%.2d/%d", date->tm_mday,(date->tm_mon),(date->tm_year));
}

Date getDelayedTime(){
  Date d = getActualTime();
  d = setDelayedTime(d);
  return d;
}

int compareTime(Date time1, Date time2){
  if((time1->tm_mday) != (time2->tm_mday))
    return 0;
  if((time1->tm_mon) != (time2->tm_mon))
    return 0;
  if((time1->tm_year) != (time2->tm_year))
    return 0;
  return 1;
}

int getDayofDate(Date d){
    return d->tm_mday;
}
int getMonthofDate(Date d){
    return d->tm_mon;
}
int getYearofDate(Date d){
    return d->tm_year;
}

