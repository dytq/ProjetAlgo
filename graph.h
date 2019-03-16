#include "const.h"
// liste adjacence
typedef struct l{ 
  	int voisin; 
  	int poids;
    struct l* suiv; 	// > pointe vers prochine val
} liste;		// > liste des voisins

typedef struct {
	int compteur[TAILLE_GRAPHE][3]; 	// >compte nb voisin vers chaque tier dans la liste
	int proba[TAILLE_GRAPHE][1]; 		// >nb de noeuds vers le meme tier
} insert;

// Graphe représenté par une liste d'adjacence
typedef struct { 
  	liste*** list; 		// >pointe vers 100 listes** qui pointe chacune vers 3 liste* ( qui sont les liste de voisin vers un tier1, tier2, tier3) qui pointe vers une liste
  	insert I;		// > permet de bien initialiser le graphe
} graphe;


// Affiche le graphe
// @param G graphe à afficher
void affiche_graphe(graphe G);

// Génére un graphe
// @param n nombre de sommets
// @return graphe graphe generé
graphe init_graphe(int n);

// Insere élement au début
// @param L liste dans laquelle il faut inserer l elem
// @param voisin le voisin à ajouter
// @param poids le poids à ajouter
// @return L liste après ajout
liste* insere_debut(liste* L, int voisin, int poids);

// ?
// @param tmp graphe temporaire
// @param i entier un sommet de l' arc
// @param j entier l' autre sommet de l' arc
// @param poidsMax poids max de l arc
// @param poidsMin poids mmin de l arc
// @param etat_i dans quel tier est le sommet i
// @param etat_j dans quel tier est le sommet j
// @return graphe le graphe
graphe insere(graphe tmp, int i,  int j, int poidsMax, int poidsMin, int etat_i, int etat_j);

// Verifie si le sommet i est dans la liste de j et inversement( meme si ca sert a rien car quand on ajoute un voisin a un sommet on ajoute aussi le sommet au voisin ) est dans la liste
// @param G le graphe
// @param i sommet
// @param etat_i dans quel tier est le sommet i
// @param j sommet
// @param etat_j dans quel tier est le sommet j
// @return booléens
int verifSiSommetInListe(graphe G, int i, int etat_i, int j, int etat_j);

// Test si le nb de noeuds max est atteint
// @param G le graphe
// @param i sommet
// @param noeudsMax le noeuds maximum
// @param etat dans quel tier appartient le sommet i
// @return booléens
int test_noeuds_max(graphe G, int i, int noeudsMax, int etat);

// Calcul quel noeuds choisir
// @param G le graphe
// @param sommet un sommet du graphe
// @param deb debut 
// @param fin fin
// @param noeudsMax nb de noeuds max du sommet vers le meme tier
// @param etat_sommet dans quel tier appartient le sommet dans lequelle on cherche un voisin
// @param etat_i dans quel tier appartient le sommet i ( le voisin )
// @return noeuds 
int calcul_noeuds(graphe G, int sommet, int deb, int fin, int noeudsMax, int etat_sommet, int etat_i);

// calcul les arc du tier 1
// @param G le graphe
// @return un graphe géneré
graphe calculTier1(graphe G);

// calcul les arc du tier 2
// @param G le graphe
// @return un graphe géneré
graphe calculTier2(graphe G);

// calcul les arc du tier 3
// @param G le graphe
// @return un graphe géneré
graphe calculTier3(graphe G);

// Permet de libérer le graphe 
// @param G le graphe à libérer
void libere_graphe(graphe G);

