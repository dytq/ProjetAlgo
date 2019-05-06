#include "const.h"
#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

void parcours_sommet(graphe* G, int s, int *couleur, int *pere){
	int i;
	couleur[s] = 1;
	for(i = 0; i < TAILLE_GRAPHE ; i++)
	{
		if(i != s && couleur[i] == 0 && G->list[s][i] != -1)
		{
			pere[i] = s;
			parcours_sommet(G, i, couleur, pere);
		}
	}
	couleur[s] = 2;			
}

int parcours_graphe(graphe* G){
	int i;
	int *couleur = calloc(TAILLE_GRAPHE,sizeof(int)); // 0 est blanc, 1 gris et 2 noir
	
	int *pere = malloc(sizeof(int)*TAILLE_GRAPHE);
	for(i = 0; i < TAILLE_GRAPHE ; i++)
		pere[i] = TAILLE_GRAPHE;
	
	int compteur = 0;
	for(i = 0; i < TAILLE_GRAPHE ; i++)
	{
		if(couleur[i] == 0)
		{
			parcours_sommet(G, i, couleur, pere);
			compteur++;
		}
	}
	
	free(couleur);
	free(pere);
	return compteur;
}
