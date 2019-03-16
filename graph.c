#include <stdlib.h>
#include <stdio.h>

//~ local
#include "graph.h"
#include "const.h"

void affiche_graphe(graphe G){
	int i, j;
	graphe tmp = G; // pour pouvoir parcourir la liste sans y toucher reelment(car pointeur)
	for(i = 0; i < TAILLE_GRAPHE; i++)
	{
		printf("Voisins de %d : \n", i);
		printf("tier1 : ");
		if(tmp.list[i][tier1] != NULL)
		{
			for(j = 0; tmp.list[i][tier1]!= NULL && j < TAILLE_GRAPHE; j++)
			{
				printf("(%d, %d) ", tmp.list[i][tier1]->voisin, tmp.list[i][tier1]->poids);
				tmp.list[i][tier1] = tmp.list[i][tier1]->suiv;
			}
		}
		printf("\n");
		
		printf("tier2 : ");
		if(tmp.list[i][tier2] != NULL)
		{
			for(j = 0; tmp.list[i][tier2]!= NULL && j < TAILLE_GRAPHE; j++)
			{
				printf("(%d, %d) ", tmp.list[i][tier2]->voisin, tmp.list[i][tier2]->poids);
				tmp.list[i][tier2] = tmp.list[i][tier2]->suiv;
			}
		}
		printf("\n");
		
		printf("tier3 : ");
		if(tmp.list[i][tier3] != NULL)
		{
			for(j = 0; tmp.list[i][tier3]!= NULL && j < TAILLE_GRAPHE; j++)
			{
				printf("(%d, %d) ", tmp.list[i][tier3]->voisin, tmp.list[i][tier3]->poids);
				tmp.list[i][tier3] = tmp.list[i][tier3]->suiv;
			}
		}
		printf("\n");
	}
}

graphe init_graphe(int n){
	graphe G;
	G.list = malloc( TAILLE_GRAPHE * sizeof(liste**) );//init juste liste de 100 lister
	
	int i,j,p = 0;
	for(i = 0; i < TAILLE_GRAPHE; i++) // ini toute les liste de voisin a NULL
	{
		G.list[i] = malloc( TAILLE_GRAPHE * sizeof(liste*) );
		for(j = 0; j < 3 ; j++)
			G.list[i][j] = NULL;
	}
	for(i = 0; i < TAILLE_GRAPHE; i++)
	{
		if( i < nbTier1 )
		{
			G.I.proba[i][0] = 0;
		}
		if( i >= debTier2 && i < finTier2)
		{
			p = rand()%2 + 2;
			G.I.proba[i][0] = p;
		}
		if( i >= debTier3 && i < finTier3)
		{
			G.I.proba[i][0] = 1;
		}
		for(j = 0; j < 3; j++)
		{
			G.I.compteur[i][j] = 0;
		}
	}
	return G;
}

liste* insere_debut(liste* L, int voisin, int poids)
{
	liste* lres;
	lres = malloc(sizeof(liste));
	if( lres == NULL){
		fprintf(stderr,"ERREUR: echec malloc\n");
		exit(EXIT_FAILURE);
	}
	lres->voisin = voisin;
	lres->poids = poids;
	lres->suiv = L;
	return lres;
}

graphe insere(graphe tmp, int i,  int j, int poidsMax, int poidsMin, int etat_i, int etat_j) {
	int k;
	k = rand()%(poidsMax - poidsMin + 1) + poidsMin;
	tmp.list[i][etat_j] = insere_debut(tmp.list[i][etat_j], j, k);
	tmp.list[j][etat_i] = insere_debut(tmp.list[j][etat_i], i, k);
	return tmp;
}

int verifSiSommetInListe(graphe G, int i, int etat_i, int j, int etat_j) {

	liste* pointeur = G.list[i][etat_j];
	while(pointeur != NULL)
	{
		if(pointeur->voisin == j)
			return 1;
		pointeur = pointeur->suiv;
	}
	
	pointeur = G.list[j][etat_i];
	while(pointeur != NULL)
	{
		if(pointeur->voisin == i)
			return 1;
		pointeur = pointeur->suiv;
	}

	return 0;
}

int test_noeuds_max(graphe G, int i, int noeudsMax, int etat) {

		if(etat == tier1)
		{
			if(G.I.compteur[i][etat] < noeudsMax)
				return 1;
		}
		else
		{
			if(G.I.compteur[i][etat] < noeudsMax &&  G.I.compteur[i][etat] < G.I.proba[i][0])
				return 1;
		}

	return 0;
}

int calcul_noeuds(graphe G, int sommet, int deb, int fin, int noeudsMax, int etat_sommet, int etat_i) {
	int distance = fin - deb;
	int pointeur[distance+1];
	int i, j = 0;
	for(i = 0; i < distance; i++)
		pointeur[i] = 0;

	for(i = deb; i < fin; i++)
	{
		if(G.I.compteur[i][etat_i] < noeudsMax 
			&& !verifSiSommetInListe(G, sommet, etat_sommet, i, etat_i) 
			&& i != sommet)
		{
			pointeur[j] = i;
			j++;
		}
	}
	int a, b;
	b = rand();
	a = b%j;
	b = pointeur[a];
	return b;
}

graphe calculTier1(graphe G) {
	
	graphe tmp = G;
	
	int i, j, k;
	int p = 7500;
	
	for(i = debTier1; i < finTier1 ; i++)
	{
		for(j = debTier1; j < finTier1; j++)
		{
			if(i != j && !verifSiSommetInListe(G, i, tier1, j, tier1))
			{
				k = rand()%1000;
				if(k < p)
				{ 
					tmp = insere(tmp, i, j, poidsMaxTier1, poidsMinTier1, tier1, tier1);
					tmp.I.compteur[i][0]++;
					tmp.I.compteur[j][0]++;
				}
			 }
		 }
	}
	return tmp;
}

graphe calculTier2(graphe G){
		
	graphe tmp = G;
	
	int i, j;
	int p, noeuds;
	
	for(i = debTier2; i < finTier2; i++)
	{
		// pour les arc vers le tier precedent
		p = rand()%2 + 1;
		for(j = 0; j < p; j++)
		{
				noeuds = calcul_noeuds(tmp, i, debTier1, finTier1, 100, tier2, tier1);
				tmp = insere(tmp, i, noeuds, poidsMaxTier2, poidsMinTier2, tier2, tier1);
		}
		
		// pour les arc vers le tier current

		for(j = 0; tmp.I.compteur[i][tier2] < G.I.proba[i][0]; j++)
		{
			if(test_noeuds_max(tmp, i, noeudsMaxTier2, tier2))
			{
				noeuds = calcul_noeuds(tmp, i, debTier2, finTier2, noeudsMaxTier2, tier2, tier2);
				tmp = insere(tmp, i, noeuds, poidsMaxTier2, poidsMinTier2, tier2, tier2);
				tmp.I.compteur[i][1]++;
				tmp.I.compteur[noeuds][1]++;
			}
		}
	 }
	return tmp;
}

graphe calculTier3(graphe G){
		
	graphe tmp = G;
	
	int i, j, k;
	int p, noeuds;
	
	for(i = debTier3; i < finTier3; i++)
	{
		// pour les arc vers le tier precedent
		p = 2;
		for(j = 0; j < p; j++)
		{
				noeuds = calcul_noeuds(tmp, i, debTier2, finTier2, 100, tier3, tier2);
				k = rand()%(poidsMaxTier3 - poidsMinTier3 + 1) + poidsMinTier3;
				
				tmp.list[i][tier2] = insere_debut(tmp.list[i][tier2], noeuds, k);
				tmp.I.compteur[i][tier2]++;
				tmp.list[noeuds][tier3] = insere_debut(tmp.list[noeuds][tier3], i, k);
				tmp.I.compteur[noeuds][tier3]++;
		}
		
		// pour les arc vers le tier current

		for(j = 0; tmp.I.compteur[i][tier3] < G.I.proba[i][0]; j++)
		{
			if(test_noeuds_max(tmp, i, noeudsMaxTier3, tier3))
			{
				noeuds = calcul_noeuds(tmp, i, debTier3, finTier3, noeudsMaxTier3, tier3, tier3);
				k = rand()%(poidsMaxTier3 - poidsMinTier3 + 1) + poidsMinTier3;
				
				tmp.list[i][tier3] = insere_debut(tmp.list[i][tier3], noeuds, k);
				tmp.I.compteur[i][tier3]++;
				tmp.list[noeuds][tier3] = insere_debut(tmp.list[noeuds][tier3], i, k);
				tmp.I.compteur[noeuds][tier3]++;
			}
		}
	 }
	return tmp;
}

void libere_graphe(graphe G){
	
	int i, j;
	liste* pointeur = NULL;// juste pour simplifier
	
	for(i = 0; i < TAILLE_GRAPHE; i++)
	{
		//tier1
		pointeur = G.list[i][tier1];
		for(j = 0; pointeur != NULL && j < TAILLE_GRAPHE; j++)
		{
			G.list[i][tier1] = pointeur;
			free(pointeur);
			pointeur = G.list[i][tier1]->suiv;
		}
		//tier2
		pointeur = G.list[i][tier2];
		for(j = 0; pointeur != NULL && j < TAILLE_GRAPHE; j++)
		{
			G.list[i][tier2] = pointeur;
			free(pointeur);
			pointeur = G.list[i][tier2]->suiv;
		}
		//tier3
		pointeur = G.list[i][tier3];
		for(j = 0; pointeur != NULL && j < TAILLE_GRAPHE; j++)
		{
			G.list[i][tier3] = pointeur;
			free(pointeur);
			pointeur = G.list[i][tier3]->suiv;
		}
		free(G.list[i]);
	}
	free(G.list);
}
