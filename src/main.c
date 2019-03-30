#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "const.h"
#include "graph.h"
#include "affiche.h"
#include "connexe.h"


void calcul(graphe* G) 
{
	calculTier1(G);
	calculTier2(G);
	calculTier3(G);
}

int main()
{	
	srand(time(NULL));
	graphe* G = init_graphe(TAILLE_GRAPHE);
	
	calcul(G);
	affiche_graphe(G);
	
	int connexe = parcours_graphe(G);
	if(connexe == 1)
		printf("\nLe graphe est connexe\n");
	else
		printf("\nLe graphe n'est pas connexe\n");

	free(G);
	return 0;
}
