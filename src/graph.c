#include <stdlib.h>
#include <stdio.h>

//~ local
#include "graph.h"
#include "const.h"

graphe* init_graphe(){
	graphe* G = malloc(sizeof(graphe));
	
	int i, j, p = 0;
	
	// struct liste
	for(i = 0; i < TAILLE_GRAPHE; i++) // ini toute le tableau a -1
	{
		for(j = 0; j < TAILLE_GRAPHE; j++)
		{
			G->list[i][j] = -1;
		}
	}
	
	// struct Insert
	int found = 0;
	int cmp2;
	while(!found)
	{
		cmp2 = 0;
		for(i = 0; i < TAILLE_GRAPHE; i++)
		{
			if( i < nbTier1 )
			{
				G->I.proba[i][0] = 0;
			}
			if( i >= debTier2 && i < finTier2)
			{
				p = rand()%2 + 2;
				G->I.proba[i][0] = p;
			}
			if( i >= debTier3 && i < finTier3)
			{
				G->I.proba[i][0] = 1;
			}
			for(j = 0; j < 3; j++)
			{
				G->I.compteur[i][j] = 0;
			}
		}
		
		for(i = debTier2; i < finTier2; i++)
		{
			cmp2 += G->I.proba[i][0] = p;
		}
		
		if( cmp2 % 2 == 0 )
		{
			found = 1;
		}
	}
	return G;
}

int verifSiSommetInListe(graphe* G, int i, int j) {

	if(G->list[i][j]!= -1)
		return 1;
	return 0;
}

int test_noeuds_max(graphe* G, int i, int noeudsMax, int etat) {

		if(etat == tier1)
		{
			if(G->I.compteur[i][etat] < noeudsMax)
				return 1;
		}
		else
		{
			if(G->I.compteur[i][etat] < noeudsMax &&  G->I.compteur[i][etat] < G->I.proba[i][0])
				return 1;
		}

	return 0;
}

int calcul_noeuds(graphe* G, int sommet, int deb, int fin, int noeudsMax, int etat_sommet, int etat_i) {
	
	int distance = fin - deb;
	int pointeur[distance+1];
	int i, j = 0;
	
	for(i = 0; i < distance; i++)
		pointeur[i] = 0;

	for(i = deb; i < fin; i++)
	{
		if(G->I.compteur[i][etat_i] < noeudsMax 
			&& !verifSiSommetInListe(G, sommet, i) 
			&& i != sommet)
		{
			pointeur[j] = i;
			j++;
		}
	}
	if(j != 0)
	{
		int a, b;
		b = rand();
		a = b % j;
		b = pointeur[a];
		return b;
	}
	return -1;
}

void calculTier1(graphe* G) {
	
	
	int i, j, k;
	int p = 7500;
	
	for(i = debTier1; i < finTier1 ; i++)
	{
		for(j = debTier1; j < finTier1; j++)
		{
			if(i != j && !verifSiSommetInListe(G, i, j))
			{
				k = rand()%1000;
				if(k < p)
				{ 
					k = rand()%(poidsMaxTier2 - poidsMinTier2 + 1) + poidsMinTier2;
					
					G->list[i][j] = k;
					G->list[j][i] = k;
					G->I.compteur[i][0]++;
					G->I.compteur[j][0]++;
				}
			 }
		 }
	}
}

void calculTier2(graphe* G){
		
	
	int i, j;
	int p, noeuds, k;
	
	for(i = debTier2; i < finTier2; i++)
	{
		// pour les arc vers le tier precedent
		p = rand()%2 + 1;
		for(j = 0; j < p; j++)
		{
				noeuds = calcul_noeuds(G, i, debTier1, finTier1, 100, tier2, tier1);
				k = rand()%(poidsMaxTier2 - poidsMinTier2 + 1) + poidsMinTier2;
				if(noeuds != -1)
				{
					G->list[i][noeuds] = k;
					G->list[noeuds][i] = k;
				}
		}
		
		// pour les arc vers le tier current
		for(j = 0; G->I.compteur[i][tier2] < G->I.proba[i][0] && j < G->I.proba[i][0]; j++)
		{
			if(test_noeuds_max(G, i, noeudsMaxTier2, tier2))
			{
				noeuds = calcul_noeuds(G, i, debTier2, finTier2, noeudsMaxTier2, tier2, tier2);
				k = rand()%(poidsMaxTier2 - poidsMinTier2 + 1) + poidsMinTier2;
				if(noeuds != -1)
				{
					G->list[i][noeuds] = k;
					G->list[noeuds][i] = k;
					
					G->I.compteur[i][1]++;
					G->I.compteur[noeuds][1]++;
				}
			}
		}
	 }
}

void calculTier3(graphe* G){
	
	int i, j, k;
	int p, noeuds;
	
	for(i = debTier3; i < finTier3; i++)
	{
		// pour les arc vers le tier precedent
		p = 2;
		for(j = 0; j < p; j++)
		{
				noeuds = calcul_noeuds(G, i, debTier2, finTier2, 100, tier3, tier2);
				k = rand()%(poidsMaxTier3 - poidsMinTier3 + 1) + poidsMinTier3;
				
				if(noeuds != -1)
				{
					G->list[i][noeuds] = k;
					G->I.compteur[i][tier2]++;
					
					G->list[noeuds][i] = k;
					G->I.compteur[noeuds][tier3]++;
				}
		}
		
		// pour les arc vers le tier current
		for(j = 0; G->I.compteur[i][tier3] < G->I.proba[i][0] && j < G->I.proba[i][0]; j++)
		{
			if(test_noeuds_max(G, i, noeudsMaxTier3, tier3))
			{
				noeuds = calcul_noeuds(G, i, debTier3, finTier3, noeudsMaxTier3, tier3, tier3);
				k = rand()%(poidsMaxTier3 - poidsMinTier3 + 1) + poidsMinTier3;
				
				if(noeuds != -1)
				{
					G->list[i][noeuds] = k;
					G->I.compteur[i][tier3]++;
					
					G->list[noeuds][i] = k;
					G->I.compteur[noeuds][tier3]++;
				}
			}
		}
	 }
}
