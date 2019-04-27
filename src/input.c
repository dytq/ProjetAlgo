#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "input.h"

int is_quit(char * buf)
{
	if(!(strcmp(buf,"quit"))) 
	{
		free(buf);
		return -1;
	}
	return 1;
}

int input_value(int * dest)
{
	char * buf = malloc(5 * sizeof(char));		// > pour stoker l'entrée
	
	if(!(*dest = *dest ^ 1)) 					// > dest change de valeur à chaque fois qu'on appelle la fonction input_value 
	{
		printf("Entrée valeur destinataire: ");
	}
	else printf("Entrée valeur expediteur: ");
	
	scanf("%s",buf); 							// Récupération de la chaine de caractere sur le terminal
	if(is_quit(buf) == -1 ) return -1; 			// envoie signal pour quitter le programme
	int res = atoi(buf); 						// convertion chaine de caractere en entier
	free(buf);
	return res; 
}
