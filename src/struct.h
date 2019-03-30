#include "const.h"

typedef struct {
	int compteur[TAILLE_GRAPHE][3]; 	// >compte nb voisin vers chaque tier dans la liste
	int proba[TAILLE_GRAPHE][1]; 		// >nb de noeuds vers le meme tier
} insert;

// Graphe représenté par une liste d'adjacence
typedef struct { 
  	int list[TAILLE_GRAPHE][TAILLE_GRAPHE]; 		// >pointe vers 100 listes** qui pointe chacune vers 3 liste* ( qui sont les liste de voisin vers un tier1, tier2, tier3) qui pointe vers une liste
  	insert I;			// >permet de bien initialiser le graphe
} graphe;

typedef struct {
	int pere[TAILLE_GRAPHE][TAILLE_GRAPHE];
	int poids[TAILLE_GRAPHE][TAILLE_GRAPHE];
} routage;
