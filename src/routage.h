#include "const.h"
/**
 * Algorithme de recherche du plus court chemin dans une graphe
 * */

/**
 * Structure de donnée pour sauvegarder la table de root (2 matrices)
 * */
typedef struct {
	int succ[TAILLE_GRAPHE][TAILLE_GRAPHE];
	int poids[TAILLE_GRAPHE][TAILLE_GRAPHE];
} routage;

/**
 * Initialisation de la table de rootage
 * @param graphe
 * @param taille du graphe
 * */
routage* init(graphe* G, int taille);

/**
 * Application de l'alogorthme Floyd Warshall
 * @param routage table de routage à remplir
 * @param taille du graphe
 * */
void Floyd_Warshall(routage* R, int taille);

void Dijkstra(routage* R,int taille);

/**
 * Libération de mémoire de la table de rootage
 * @param table de root
 * */
void libere_routage(routage* R);

/**
 * Affiche le plus court chemin entre une paire de noeuds
 * @param table de root
 * @param premier noeud de départ
 * @param dernier noeud d'arrivé
 * */
void afficher_chemin(routage* R, int deb, int fin);
