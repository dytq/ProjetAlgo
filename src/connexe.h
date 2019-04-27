/**
 * Algorithme de recherche en profondeur
 * Les algorithmes implémentés permettent de vérifier la connexité du 
 * graphe en appliquant l'algorithme en profondeur
 * */

/**
 * Parcours du graphe par chaque sommet 
 * @param Graphe
 * @param entier
 * @param couleur 
 * @param pere
 * */
void parcours_sommet(graphe* G, int s, int *couleur, int *pere);

/**
 * parcours le graphe en profondeur pour savoir s'il est connexe
 * @param graphe
 * @return si connexe
 * */
int parcours_graphe(graphe* G);
