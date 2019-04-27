#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <string.h>

#include "const.h"
#include "graph.h"
#include "affiche.h"
#include "connexe.h"
#include "routage.h"

void test_connexe(graphe* G) {
	int connexe = parcours_graphe(G);
	if(connexe == 1)
		printf("\nLe graphe est connexe\n");
	else
		printf("\nLe graphe n'est pas connexe\n");
}

void calcul_graphe(graphe* G) 
{
	calculTier1(G);
	calculTier2(G);
	calculTier3(G);
}

void calcul_routage(routage* R) {
	hash(R, TAILLE_GRAPHE);
}

int is_quit(char * buf)
{
	if(strcmp(buf,"quit") == 1) 
	{
		free(buf);
		return -1;
	}
	return 1;
}

int input_value(int * dest)
{
	char * buf = malloc(5 * sizeof(char));
	if(!(*dest = *dest ^ 1)) printf("Entrée valeur destinataire: ");
	else printf("Entrée valeur expéditeur: ");
	scanf("%s",buf);
	if(is_quit(buf) == -1 ) return -1;
	int res = atoi(buf);
	free(buf);
	return res;
}

void input_keyboard(routage * R)
{
	int in,out;
	int is_dest = 0;
	while(1)
		if((in = input_value(&is_dest)) != -1  && (out = input_value(&is_dest)) != -1) 
		{
			affiche_chemin(R,in,out);
		} else break;
}
int main()
{	
	srand(time(NULL));
	graphe* G = init_graphe(TAILLE_GRAPHE);
	
	calcul_graphe(G);
	test_connexe(G);
		
	routage* R = init(G, TAILLE_GRAPHE);
	calcul_routage(R);
	
	input_keyboard(R);
	
	libere_routage(R);
	free(G);
	return 0;
}
