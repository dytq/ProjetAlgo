
#define TAILLE_GRAPHE 100
#define tier1 0
#define tier2 1
#define tier3 2

#define nbTier1 8
#define nbTier2 20
#define nbTier3 72
#define ZERO 0

#define debTier1 0
#define finTier1 8
#define debTier2 8
#define finTier2 28
#define debTier3 28
#define finTier3 100

#define poidsMaxTier1 10
#define poidsMinTier1 5
#define poidsMaxTier2 20
#define poidsMinTier2 10
#define poidsMaxTier3 50
#define poidsMinTier3 15

#define noeudsMaxTier2 3
#define noeudsMaxTier3 1

typedef struct l{ //graphe représenté par une liste d'adjacence
  	int voisin;
  	int poids;
    struct l* suiv; // pointe vers prochine val
} liste; // liste des voisin

typedef struct {
	int compteur[TAILLE_GRAPHE][3]; // compte nb elem dans la liste
	int proba[TAILLE_GRAPHE][1]; // nb de noeuds max vers le meme tier
} insert;

typedef struct { //graphe représenté par une liste d'adjacence
  	liste*** list; //pointe vers 100 liste
  	insert I;
} graphe;
