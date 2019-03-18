#include <stdio.h>
//~ local
#include "const.h"
#include "graph.h"

graphe afficher_tier(graphe tmp,int sommet,const int tier)
{
	int j;
	printf("tier%d : ",tier + 1);
	if(tmp.list[sommet][tier] != NULL)
	{
		for(j = 0; tmp.list[sommet][tier]!= NULL && j < TAILLE_GRAPHE; j++)
		{
			printf("(%d, %d) ", tmp.list[sommet][tier]->voisin, tmp.list[sommet][tier]->poids);
			tmp.list[sommet][tier] = tmp.list[sommet][tier]->suiv;
		}
	}
	return tmp;
}

void affiche_graphe(graphe G){
	int sommet, i;
	graphe tmp = G; // pour pouvoir parcourir la liste sans y toucher reelment(car pointeur)
	for(sommet = 0; sommet < TAILLE_GRAPHE; sommet++)
	{
		printf("Voisins de %d : \n", sommet);
		for(i = 0; i < 3; i++)
		{
			tmp = afficher_tier(tmp, sommet, i);
			printf("\n");
		}
	}
}
