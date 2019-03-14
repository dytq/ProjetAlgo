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
				printf("(s : %d, p : %d) ", tmp.list[i]->voisin, tmp.list[i]->poids);
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

int verifSiSommetInListe(graphe G, int i, int j) {
	graphe tmp = G;
	liste* pointeur = tmp.list[i];
	while(tmp.list[i] != NULL)
	{
		if(tmp.list[i]->voisin == j)
			return 1;
		tmp.list[i] = tmp.list[i]->suiv;
	}
	tmp.list[i] = pointeur;
	
	pointeur = tmp.list[j];
	while(tmp.list[j] != NULL)
	{
		if(tmp.list[j]->voisin == i)
			return 1;
		tmp.list[j] = tmp.list[j]->suiv;
	}
	tmp.list[j] = pointeur;
	return 0;
}
int test_noeuds_max(graphe G, int deb, int fin, int noeudsMax, int etat) {
	int i;
	for(i = deb; i < fin; i++)
	{
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
	}
	return 0;
}

int calcul_noeuds(graphe G, int sommet, int deb, int fin, int noeudsMax, int etat) {
	int distance = fin - deb;
	int pointeur[distance];
	
	int i, j = 0;
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
	a = rand()%j;
	b = pointeur[a];
	return b;
}

graphe calculTier1(graphe G, float p, int deb, int fin, int poids_min, 
	int poids_max){
	
	graphe tmp = G;
	
	int i, j, k;
	p = p*1000;
	
	for(i = deb; i < fin ; i++)
	{
		for(j = deb; j < fin; j++)
		{
			if(i != j && !verifSiSommetInListe(G, i, j))
			{
				k = rand()%1000;
				if(k < p)
				{
					k = rand()%(poids_max - poids_min + 1) + poids_min;
					tmp.list[i] = insere_debut(tmp.list[i], j, k);
					tmp.I.compteur[i][0]++;
					tmp.list[j] = insere_debut(tmp.list[j], i, k);
					tmp.I.compteur[j][0]++;
				}
			 }
		 }
	}
	return tmp;
}

graphe calculTier2(graphe G){
		
	graphe tmp = G;
	
	int i, j, k;
	int p, noeuds;
	
	for(i = nbTier1; i < nbTier1 + nbTier2 ; i++)
	{
		// pour les arc vers le tier precedent
		p = rand()%2 + 1;
		for(j = 0; j < p; j++)
		{
				noeuds = calcul_noeuds(tmp, i, ZERO, nbTier1, 100, tier1);
				k = rand()%(poidsMaxTier2 - poidsMinTier2 + 1) + poidsMinTier2;
				
				tmp.list[i] = insere_debut(tmp.list[i], noeuds, k);
				tmp.I.compteur[i][tier1]++;
				tmp.list[noeuds] = insere_debut(tmp.list[noeuds], i, k);
				tmp.I.compteur[noeuds][tier2]++;
		}
		
		// pour les arc vers le tier current

		for(j = 0; tmp.I.compteur[i][tier2] < G.I.proba[i][0]; j++)
		{
			if(test_noeuds_max(tmp, nbTier1, nbTier1 + nbTier2, noeudsMaxTier2, tier2))
			{
				noeuds = calcul_noeuds(tmp, i, nbTier1, nbTier1 + nbTier2, noeudsMaxTier2, tier2);
				k = rand()%(poidsMaxTier2 - poidsMinTier2 + 1) + poidsMinTier2;
				
				tmp.list[i] = insere_debut(tmp.list[i], noeuds, k);
				tmp.I.compteur[i][tier2]++;
				tmp.list[noeuds] = insere_debut(tmp.list[noeuds], i, k);
				tmp.I.compteur[noeuds][tier2]++;
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
			if(test_noeuds_max(tmp, debTier3, finTier3, noeudsMaxTier3, tier3))
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
	
	int deb, fin;
	deb = ZERO;
	fin = nbTier1;
	
	G = calculTier1(G, 0.75, deb, fin, poidsMinTier1, poidsMaxTier1);
	G = calculTier2(G);
	int d = debug(G, debTier2, finTier2);
	printf("debug = %d\n", d);
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
