#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <crypt.h>
#include <string.h>
#include "../include/chiffrement.h"

//fonction permettant de chiffrer un mot de passe
char* chiffrementMdp(char* chaine){
	char * chiffre;
	chiffre = (char*) malloc(sizeof(char)*65);
	sprintf(chiffre, "%s",(char*)crypt(chaine, "5684fsdf4s6d84fsd846od125aienfu89d5zkdfiejfmsdfjsl56fsd4f4s5df4zd4f4zd4f8d4zf4dzffdz5"));
	return(chiffre);
}
//dans le sprintf --> chaque mot de passe entre va etre remplace par la chaine de caractère ci dessus!
