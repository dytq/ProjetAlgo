#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "const.h"
#include "graph.h"
#include "affiche.h"

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

	free(G);
	return 0;
}
