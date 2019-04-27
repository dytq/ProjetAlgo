#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "input.h"

#define in_graph(a) (((a) < 0) || ((a) > 100)) ? -1 : (a)

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
	int res;
	
	if(!(*dest = *dest ^ 1)) 					// > dest change de valeur à chaque fois qu'on appelle la fonction input_value 
	{
		printf("Entrée valeur destinataire: ");
	}
	else printf("Entrée valeur expediteur: ");
	
	do{
		scanf("%s",buf); 										// Récupération de la chaine de caractere sur le terminal
		if(is_quit(buf) == -1 ) return -1; 						// envoie signal pour quitter le programme
		res = atoi(buf); 										// convertion chaine de caractere en entier
		if(in_graph(res) == -1) printf("erreur reessayer:");	// si non valide alors afficher erreur à l'utilisateur
		
	} while(in_graph(res) == -1);   // Tant que valide
	
	free(buf);
	return res; 
}
