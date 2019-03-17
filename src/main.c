#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "const.h"
#include "graph.h"
#include "affiche.h"

graphe calcul(graphe G) 
{
	G = calculTier1(G);
	G = calculTier2(G);
	G = calculTier3(G);
	return G;
}

int main()
{	
	srand(time(NULL));
	graphe G = init_graphe(TAILLE_GRAPHE);
	G = calcul(G);
	affiche_graphe(G);
	libere_graphe(G);
	return 0;
}
