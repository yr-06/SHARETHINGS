#ifndef __DATE_H__
#define __DATE_H__



//structure:
typedef struct date_s *Date;
//setters : 
Date setTime(char * day, char * month, char * year);
Date setDelayedTime(Date d);

//getters :
Date getDelayedTime();
Date getActualTime();

int getDayofDate(Date d);
int getMonthofDate(Date d);
int getYearofDate(Date d);

//fonctions :
Date initDate();
void affichTime(Date date);
int compareTime(Date date1, Date date2);

#endif
