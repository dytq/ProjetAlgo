#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lib.h"

// init variable

void affiche_graphe(graphe G){
	int i, j;
	graphe tmp = G; // pour pouvoir parcourir la liste sans y toucher reelment(car pointeur)
	for(i = 0; i < TAILLE_GRAPHE; i++)
	{
		
		if(tmp.list[i] != NULL)
		{
			printf("Voisins de %d : \n", i);
			
			for(j = 0; tmp.list[i]!= NULL && j < TAILLE_GRAPHE; j++)
			{
				printf("(%d, %d) ", tmp.list[i]->voisin, tmp.list[i]->poids);
				tmp.list[i] = tmp.list[i]->suiv;
			}
			
			printf("\n");
		}
	}
}

graphe init_graphe(int n){
	graphe G;
	G.list = malloc( TAILLE_GRAPHE * sizeof(liste*) );//init juste liste de 100 lister
	
	int i,j,p = 0;
	for(i = 0; i < TAILLE_GRAPHE; i++) // ini toute les liste de voisin a NULL
	{
		G.list[i] = NULL;
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

graphe insere(graphe tmp, int i, int j, int poidsMax, int poidsMin) {
	int k;
	k = rand()%(poidsMax - poidsMin + 1) + poidsMin;
	tmp.list[i] = insere_debut(tmp.list[i], j, k);
	tmp.list[j] = insere_debut(tmp.list[j], i, k);
	return tmp;
}

int verifSiSommetInListe(graphe G, int i, int j) {

	liste* pointeur = G.list[i];
	while(pointeur != NULL)
	{
		if(pointeur->voisin == j)
			return 1;
		pointeur = pointeur->suiv;
	}
	
	pointeur = G.list[j];
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

int calcul_noeuds(graphe G, int sommet, int deb, int fin, int noeudsMax, int etat) {
	int distance = fin - deb;
	int pointeur[distance+1];
	int i, j = 0;
	for(i = 0; i < distance; i++)
		pointeur[i] = 0;

	for(i = deb; i < fin; i++)
	{
		if(G.I.compteur[i][etat] < noeudsMax 
			&& !verifSiSommetInListe(G, sommet, i) 
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
			if(i != j && !verifSiSommetInListe(G, i, j))
			{
				k = rand()%1000;
				if(k < p)
				{
					tmp = insere(tmp, i, j, poidsMaxTier1, poidsMinTier1);
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
				noeuds = calcul_noeuds(tmp, i, debTier1, finTier1, 100, tier1);
				tmp = insere(tmp, i, noeuds, poidsMaxTier2, poidsMinTier2);
		}
		
		// pour les arc vers le tier current

		for(j = 0; tmp.I.compteur[i][tier2] < G.I.proba[i][0]; j++)
		{
			if(test_noeuds_max(tmp, i, noeudsMaxTier2, tier2))
			{
				noeuds = calcul_noeuds(tmp, i, debTier2, finTier2, noeudsMaxTier2, tier2);
				tmp = insere(tmp, i, noeuds, poidsMaxTier2, poidsMinTier2);
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
				noeuds = calcul_noeuds(tmp, i, debTier2, finTier2, 100, tier2);
				k = rand()%(poidsMaxTier3 - poidsMinTier3 + 1) + poidsMinTier3;
				
				tmp.list[i] = insere_debut(tmp.list[i], noeuds, k);
				tmp.I.compteur[i][tier2]++;
				tmp.list[noeuds] = insere_debut(tmp.list[noeuds], i, k);
				tmp.I.compteur[noeuds][tier3]++;
		}
		
		// pour les arc vers le tier current

		for(j = 0; tmp.I.compteur[i][tier3] < G.I.proba[i][0]; j++)
		{
			if(test_noeuds_max(tmp, i, noeudsMaxTier3, tier3))
			{
				noeuds = calcul_noeuds(tmp, i, debTier3, finTier3, noeudsMaxTier3, tier3);
				k = rand()%(poidsMaxTier3 - poidsMinTier3 + 1) + poidsMinTier3;
				
				tmp.list[i] = insere_debut(tmp.list[i], noeuds, k);
				tmp.I.compteur[i][tier3]++;
				tmp.list[noeuds] = insere_debut(tmp.list[noeuds], i, k);
				tmp.I.compteur[noeuds][tier3]++;
			}
		}
	 }
	return tmp;
}

int debug(graphe G, int deb, int fin) {
	liste* pointeur = NULL;
	int i, n, res = 0;
	for(i = deb; i < fin ; i++)
	{
		pointeur = G.list[i];
		while(G.list[i] != NULL)
		{
			n = G.list[i]->voisin;
			if(G.list[n] != NULL &&  G.list[n]->voisin == i)
			{
				res += 1;
			}
			G.list[i] = G.list[i]->suiv;
		}
		G.list[i] = pointeur;
	}
	return res;	
}

graphe calcul(graphe G) { // juste pour tester

	
	G = calculTier1(G);
	G = calculTier2(G);
	G = calculTier3(G);
	return G;
}

void libere_graphe(graphe G){
	
	int i, j;
	liste* pointeur = NULL;// juste pour simplifier
	
	for(i = 0; i < TAILLE_GRAPHE; i++)
	{
		pointeur = G.list[i];
		for(j = 0; pointeur != NULL && j < TAILLE_GRAPHE; j++)
		{
			G.list[i] = pointeur;
			free(pointeur);
			pointeur = G.list[i]->suiv;
		}
	}
	free(G.list);
}

int main(){
	// Test
	
	srand(time(NULL));
	
	graphe G = init_graphe(TAILLE_GRAPHE);
	G = calcul(G);
	affiche_graphe(G);
	libere_graphe(G);
	
	return 0;
}
