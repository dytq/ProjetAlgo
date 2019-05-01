/**
 * Bibliothèque de gestion d'un graphe 
 * 
 * Description:
 * Cette bibliothèque permet de dessiner des cercles et des lignes.
 * Elle a été créer afin de manipuler des graphes simplements.
 * 
 * @version_alpha : 
 * C'est une version fork de flame11 based on X11 by Yaspr
 * -> https://github.com/yaspr/flame11
 * 
 * @autor : 
 * Dedarally Taariq
 * -> https://github.com/D-54/Graph_Bibliotheque
 * 
 * @version : 
 * 1.0 mai 2019
 * */

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <inttypes.h>

#include "flame.h"
#include "moteur_graphique.h"

#include "pi.h"

#define A_STEP 0.01


void remplir_cercle(flame_obj_t *fo, cercle_t *b)
{
	flame_set_color(fo, b->r, b->g,b->b);
	for (double angle = 0.0; angle < 2 * PI; angle += A_STEP)
	{
		flame_draw_line(fo, b->pos_x, b->pos_y, b->pos_x + b->rad * cos(angle), b->pos_y + b->rad * sin(angle));
	}
}

void afficher_cercle(flame_obj_t *fo, cercle_t *b)
{
	flame_set_color(fo, b->r, b->g,b->b);
	for (double angle = 0.0; angle < 2 * PI; angle += A_STEP)
	{
		flame_draw_point(fo, b->pos_x + b->rad * cos(angle), b->pos_y + b->rad * sin(angle)); 
	}
}

void afficher_ligne(flame_obj_t *fo,int x1,int y1,int x2,int y2)
{
	flame_draw_line(fo, x1, y1,x2,y2);
}

char recupere_clavier(XEvent event)
{
	char c;
	if (event.type == KeyPress)
	{
		c = XLookupKeysym(&event.xkey, 0);
		return c;
	}
	return -1;
}

flame_obj_t * init_canvas()
{
	return flame_open("Graphe",TAILLE_ECRAN_HAUTEUR,TAILLE_ECRAN_LARGEUR);
}

void colorer_cercle(cercle_t * c,enum couleur coul)
{
	switch(coul)
	{
		case ROUGE : 
		{
			c->r = 255;
			c->g = 0;
			c->b = 0;
			break;
		}
		case BLEU :
		{
			c->r = 0;
			c->g = 0;
			c->b = 255;
			break;
		}
		case VERT :
		{
			c->r = 0;
			c->g = 255;
			c->b = 0;
			break;
		}
		case BLANC : 
		{
			c->r = 255;
			c->g = 255;
			c->b = 255;
			break;
		}
		case JAUNE :
		{
			c->r = 255;
			c->g = 255;
			c->b = 0;
			break;
		}
		default:
		{
			perror("switch");
			exit(EXIT_FAILURE);
		}
	}
}

void afficher_connexion(flame_obj_t *fo,cercle_t * c,int id_1,int id_2,enum couleur coul)
{
	if(coul == BLANC) flame_set_color(fo, 255, 255, 255);
	if(coul == ROUGE) flame_set_color(fo, 255, 0, 0);
	if(coul == GRIS) flame_set_color(fo, 200, 200, 200);
	afficher_ligne(fo,c[id_1].pos_x,c[id_1].pos_y,c[id_2].pos_x,c[id_2].pos_y);
}
