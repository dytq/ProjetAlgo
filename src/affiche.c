#include <stdio.h>
//~ local
#include "const.h"
#include "graph.h"

void afficher_tier(graphe* G, int sommet, int deb, int fin)
{
	int j;

	for(j = deb; j < fin; j++)
	{
		if(G->list[sommet][j] != -1)
		{
			printf("(%d,%d) ", j, G->list[sommet][j]);
		}
	}
	printf("\n");
}

void affiche_graphe(graphe* G){
	
	int sommet, i;
	
	for(sommet = 0; sommet < TAILLE_GRAPHE; sommet++)
	{
		printf("Voisins de %d : \n", sommet);
		
		printf("tier1 : ");
		afficher_tier(G, sommet, debTier1, finTier1);
		printf("tier2 : ");
		afficher_tier(G, sommet, debTier2, finTier2);
		printf("tier3 : ");
		afficher_tier(G, sommet, debTier3, finTier3);
	}
}
