#include "flame.h"

#define TAILLE_ECRAN_HAUTEUR 500
#define TAILLE_ECRAN_LARGEUR 500

#define TAILLE_CERCLE 15

/* Définir la couleur 8 bits */
typedef unsigned char byte;

/* Structure de données d'un cercle */

typedef struct cercle_s {

  double pos_x; 
  double pos_y;
  
  double rad;
  
  //Couleur du cercle
  byte r;
  byte g;
  byte b;
  
} cercle_t;

enum couleur{
	ROUGE,
	VERT,
	BLEU,
	BLANC,
	JAUNE,
	GRIS,
	NOIR
};

/* Permet d'afficher un cercle rempli*/
void remplir_cercle(flame_obj_t *fo, cercle_t *b);

/* Permet d'afficher un cercle */
void afficher_cercle(flame_obj_t *fo, cercle_t *b);

/* Permet d'afficher les connexions */
void afficher_ligne(flame_obj_t *fo,int x1,int y1,int x2,int y2);

/* Permet de récuperer les entrées du clavier */
char recupere_clavier(XEvent event);

/* Colorier un cercle */ 
void colorer_cercle(cercle_t * c,enum couleur coul);

/* Initialise la fenetre graphique */ 
flame_obj_t * init_canvas();
/* Permet d'afficher les connexion entre les objets symbolisé par un trait */ 
void afficher_connexion(flame_obj_t *fo,cercle_t * c,int id_1,int id_2,enum couleur coul);
