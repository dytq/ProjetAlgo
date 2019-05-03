#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "const.h"
#include "graph.h"
#include "connexe.h"
#include "routage.h"
#include "affiche.h"

int test_connexe(graphe* G) {
	int est_connexe = parcours_graphe(G);
	
	if(est_connexe) { return 1; }
	return 0;
}

void calcul_graphe(graphe* G) 
{
	calculTier1(G);
	calculTier2(G);
	calculTier3(G);
}

void calcul_routage(routage* R) {
	Floyd_Warshall(R, TAILLE_GRAPHE);
}

int main()
{	
	srand(time(NULL)); // > graine aléatoire 
	
	graphe* G = init_graphe(TAILLE_GRAPHE);
	
	/* Tant que le graphe n'est pas connexe on recalcul le graphe */ 
	do
	{
		calcul_graphe(G);
	} while( !test_connexe(G) );

	printf("\nLe graphe est connexe\n");
	
	routage* R = init(G, TAILLE_GRAPHE);
	calcul_routage(R);
	
	/* Gestion de la fenetre graphique: fonction bloquante */ 
	gestion_fenetre_graphique(G,R);
	
	/* Libérations des structures de données utilisées */
	libere_routage(R);	
	free(G);
	
	return 0;
}
