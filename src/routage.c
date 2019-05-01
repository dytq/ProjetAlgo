#include "const.h"
#include "graph.h"
#include "routage.h"

#include <stdlib.h> // rand ()

#include <stdio.h> // printf ()

#define inf 9999


routage* init(graphe* G, int taille) {
	int i, j;
	routage* R = malloc(sizeof(routage));
	
	
	for(i = 0; i < taille; ++i)
	{
		for(j = 0; j < taille; ++j)
		{
			R->poids[i][j] = G->list[i][j];
			if(R->poids[i][j] != -1)
			{
				R->pere[i][j] = i;
			}
			else
			{
				R->poids[i][j] = inf;
			}
		}
	}
	
	for(i = 0; i < taille; ++i)
	{
		R->poids[i][i] = 0;
		R->pere[i][i] = i;
	}
	return R;
}

void Floyd_Warshall(routage* R, int taille) {
	int i, j, k;
	
	for(k = 0; k < taille; k++)
	{
		for(i = 0; i < taille; i++)
		{
			for(j = 0; j < taille; j++)
			{
				if(R->poids[i][k] != inf && R->poids[k][j] != inf			
					&& (R->poids[i][j] > (R->poids[i][k] + R->poids[k][j])) ) 
				{
					R->poids[i][j] = R->poids[i][k] + R->poids[k][j];
					R->pere[i][j] = k;
				}
				
			}
		}
	}
}

void affichage(routage* R, int taille) {
	int i, j;
	printf("Matrice :\n");
	
	for(i = 0; i < taille; ++i)
	{
		for(j = 0; j < taille; ++j)
		{
			printf("|%3d|", R->poids[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	printf("Pere :\n");
	for(i = 0; i < taille; ++i)
	{
		for(j = 0; j < taille; ++j)
		{
			printf("|S%2d|", R->pere[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void libere_routage(routage* R) {
	
	free(R);
 }

void afficher_chemin(routage* R, int deb, int fin) {
	int i;
	int voisin[TAILLE_GRAPHE] = {-1};

	for(i = 0; deb != fin && i < TAILLE_GRAPHE; i++)
	{
		voisin[i] = fin;
		fin = R->pere[deb][fin];
	}
	i--;
	printf("\nListe :\n%d", deb);
	for(; voisin[i] != -1 && i >= 0; i--)
	{
		printf(" -> %d", voisin[i]);
	}
	printf("\n");
}
