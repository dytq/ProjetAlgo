#include "const.h"
/**
 * Algorithme de recherche du plus court chemin dans une graphe
 * */
 
typedef struct {
	int pere[TAILLE_GRAPHE][TAILLE_GRAPHE];
	int poids[TAILLE_GRAPHE][TAILLE_GRAPHE];
} routage;

routage* init(graphe* G, int taille);

void hash(routage* R, int taille);

void affichage(routage* R, int taille);

void libere_routage(routage* R);

void affiche_chemin(routage* R, int deb, int fin);
