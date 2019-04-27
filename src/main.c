#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "const.h"
#include "graph.h"
#include "affiche.h"
#include "connexe.h"
#include "routage.h"

void test_connexe(graphe* G) {
	int connexe = parcours_graphe(G);
	if(connexe == 1)
		printf("\nLe graphe est connexe\n");
	else
		printf("\nLe graphe n'est pas connexe\n");
}

void calcul_graphe(graphe* G) 
{
	calculTier1(G);
	calculTier2(G);
	calculTier3(G);
}

void calcul_routage(routage* R) {
	hash(R, TAILLE_GRAPHE);
}

int input_keyboard(char * msg)
{
	char * buf;
	buf = malloc(4 * sizeof(char));
	printf("%s",msg); 
	scanf("%s",buf);
	int res = atoi(buf);
	free(buf);
	return res;
}
int main()
{	
	srand(time(NULL));
	graphe* G = init_graphe(TAILLE_GRAPHE);
	
	calcul_graphe(G);
	test_connexe(G);
		
	routage* R = init(G, TAILLE_GRAPHE);
	calcul_routage(R);
	
	int expediteur = input_keyboard("\nNoeuds émetteur du message: ");
	int destinataire = input_keyboard("\nNoeuds destinataire: ");
	
	affiche_chemin(R,expediteur,destinataire);
	
	libere_routage(R);
	free(G);
	return 0;
}
