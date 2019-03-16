#include "const.h"
// Graphe représenté par une liste adjacence
typedef struct l{ 
  	int voisin; 
  	int poids;
    struct l* suiv; 	// > pointe vers prochine val
} liste;			 	// > liste des voisins

typedef struct {
	int compteur[TAILLE_GRAPHE][3]; 	// >compte nb elem dans la liste
	int proba[TAILLE_GRAPHE][1]; 		// >nb de noeuds max vers le meme tier
} insert;

// Graphe représenté par une liste d'adjacence
typedef struct { 
  	liste*** list; 		// >pointe vers 100 listes
  	insert I;
} graphe;


// Affiche le graphe
// @param G graphe à afficher
void affiche_graphe(graphe G);

// Génére un graphe
// @param n nombre de sommets
// @return graphe graphe generé
graphe init_graphe(int n);

// Insere élement au début
// @param L le sommet pour ajouter
// @param voisin le voisin à ajouter
// @param poids le poids à ajouter
// @return L liste après ajout
liste* insere_debut(liste* L, int voisin, int poids);

// ?
// @param tmp graphe temporaire
// @param i entier ?
// @param j entier ?
// @param poidsMax ?
// @param poidsMin ?
// @param etat_i ?
// @param etat_j ?
// @return graphe ?
graphe insere(graphe tmp, int i,  int j, int poidsMax, int poidsMin, int etat_i, int etat_j);

// Verifie si le sommet est dans la liste
// @param G le graphe
// @param i ?
// @param etat_i ?
// @param j ?
// @param etat_j ?
// @return booléens
int verifSiSommetInListe(graphe G, int i, int etat_i, int j, int etat_j);

// Test si noeuds max
// @param G le graphe
// @param i ?
// @param noeudsMax le noeuds maximum
// @param etat ?
// @return booléens
int test_noeuds_max(graphe G, int i, int noeudsMax, int etat);

// Calcul_noeuds
// @param G le graphe
// @param sommet un sommet du graphe
// @param deb debut 
// @param fin fin
// @param noeudsMax ?
// @param etat_sommet ?
// @param etat_i ?
int calcul_noeuds(graphe G, int sommet, int deb, int fin, int noeudsMax, int etat_sommet, int etat_i);

// ?
// @param G le graphe
// @return un graphe géneré
graphe calculTier1(graphe G);

// ?
// @param G le graphe
// @return un graphe géneré
graphe calculTier2(graphe G);

// ?
// @param G le graphe
// @return un graphe géneré
graphe calculTier3(graphe G);

// Permet de libérer le graphe 
// @param G le graphe à libérer
void libere_graphe(graphe G);

