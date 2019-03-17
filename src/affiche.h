//>Decomposition en affichage si on veut faire un affichage graphique 

// Affiche le graphe
// @param G graphe à afficher
void affiche_graphe(graphe G);

// Affiche les voisins de chaque sommets selon le tier 
// @param tmp le graphe 
// @param sommet entier du sommet
// @param tier le tier 
// @return graphe
graphe afficher_tier(graphe tmp,int sommet,const int tier);
