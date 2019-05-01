/**
 * Decomposition en affichage si on veut faire un affichage graphique 
 * */
#include "moteur_graphique.h"
#include "routage.h"

void afficher_voisin(graphe* G, flame_obj_t * fo, cercle_t * c,int sommet, int deb, int fin);

void init_affichage_tier(cercle_t * c, int debut,int fin, int tier,int * x,int * y);

void initialisation_objets_graphique(graphe *G,flame_obj_t * fo,cercle_t * c);

int trouve_id(int x,int y);

void interaction_joueur(graphe * G,flame_obj_t * fo,routage * R,cercle_t * c);

void gestion_fenetre_graphique(graphe* G, routage *R);
