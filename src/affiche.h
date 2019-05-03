/**
 * Gestion de l'Affichage sous forme de fenetre graphique  
 * */
#include "moteur_graphique.h"

/**
 * Affichage des connexions entre les noeuds
 * @param graphe
 * @param objet
 * @param cercle 
 * @param les noeuds
 * @param le début du tier
 * @param la fin du tier
 * */
void afficher_voisin(graphe* G, flame_obj_t * fo, cercle_t * c,int sommet, int deb, int fin);

/**
 * Sauvegarde des données dans le tableau cercle pour l'affichage 
 * Chaque tiers ont des couleurs différentes (tier 1 : rouge, tier2 :
 * bleu, tier 3 : vert)
 * @param cercle
 * @param le début du tier
 * @param la fin du tier
 * @param x réprésente les coordonnées en abscisse
 * @param y représente les coordonnées en ordonnée
 * */
void init_affichage_tier(cercle_t * c, int debut,int fin, int tier,int * x,int * y);

/**
 * Permet l'initialisation des objets graphiques:
 * initialisation des cercles et des connexions des noeuds*
 * @param graphe
 * @param objet
 * @param cercle
 * */
void initialisation_objets_graphique(graphe *G,flame_obj_t * fo,cercle_t * c);

/**
 * Recherche l'identifiant du cercle dans la fenetre graphique
 * @param x abscisse
 * @param y ordonnée
 * @return identifiant du cercle
 * */
int trouve_id(int x,int y);

/**
 * Affiche le plus court chemin
 * @param objet
 * @param la table de routage
 * @param cercle
 * @param l'identifiant de l'expediteur
 * @param l'identifiant du destinataire
 * @param la couleur
 * */
void affiche_chemin(flame_obj_t * fo,routage* R, cercle_t * c,int deb, int fin,enum couleur coul);

/**
 * Permet la gestion de l'interaction utilisateur et machine 
 * @param graphe
 * @param objet
 * @param la table de routage
 * @param cercle
 * */
void interaction_user(graphe * G,flame_obj_t * fo,routage * R,cercle_t * c);

/**
 * Fonction principale 
 * Gestion de la fenetre graphique 
 * @param graphe
 * @param la table de routage
 * */
void gestion_fenetre_graphique(graphe* G, routage *R);
