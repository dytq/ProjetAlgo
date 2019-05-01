#include <stdio.h>

//~ local
#include "const.h"
#include "graph.h"
#include "moteur_graphique.h"
#include "routage.h"

void afficher_voisin(graphe* G, flame_obj_t * fo, cercle_t * c,int sommet, int deb, int fin)
{
	int j;

	for(j = deb; j < fin; j++)
	{
		if(G->list[sommet][j] != -1)
		{
			afficher_connexion(fo,c,j,G->list[sommet][j],BLANC);
		}
	}
}


void init_affichage_tier(cercle_t * c, int debut,int fin, int tier,int * x,int * y)
{
	int i;
	
	for( i = debut ; i < fin ; i ++)
	{		
		c[i].rad = TAILLE_CERCLE;
		if(tier == tier1)
		{
			colorer_cercle(&c[i],ROUGE);
			c[i].pos_x = *x * ( 3 * TAILLE_CERCLE);
			c[i].pos_y = *y * ( 3 * TAILLE_CERCLE);
			
		}
		if(tier == tier2)
		{
			colorer_cercle(&c[i],BLEU);
			c[i].pos_x = *x * ( 3 * TAILLE_CERCLE);
			c[i].pos_y = *y * ( 3 * TAILLE_CERCLE);
		}
		if(tier == tier3)
		{
			colorer_cercle(&c[i],VERT);
			c[i].pos_x = *x * ( 3 * TAILLE_CERCLE);
			c[i].pos_y = *y * ( 3 * TAILLE_CERCLE);
		}
		*x+=1;
		if(*x > 10)
		{
			*y += 1;
			*x = 1;
		}
	}
}
void initialisation_objets_graphique(graphe *G,flame_obj_t * fo,cercle_t * c)
{
	int noeud;
	
	int x = 1;
	int y = 1;
	init_affichage_tier(c,debTier1,finTier1,tier1,&x,&y);
	init_affichage_tier(c,debTier2,finTier2,tier2,&x,&y);
	init_affichage_tier(c,debTier3,finTier3,tier3,&x,&y);
	
	for (noeud = 0; noeud < TAILLE_GRAPHE; noeud++)
	{
		afficher_cercle(fo, &c[noeud]);
		afficher_voisin(G, fo, c, noeud, debTier1, finTier1);
		afficher_voisin(G, fo, c, noeud, debTier2, finTier2);
		afficher_voisin(G, fo, c, noeud, debTier3, finTier3);
	}	
}
int trouve_id(int x,int y)
{
	x -= (2 * TAILLE_CERCLE);
	y -= (2 * TAILLE_CERCLE);
	return ((y / (3 * TAILLE_CERCLE))*10) + (x / (3*TAILLE_CERCLE));
}

void affiche_chemin(flame_obj_t * fo,routage* R, cercle_t * c,int deb, int fin) {
	int i;
	int voisin[TAILLE_GRAPHE] = {-1};
	
	for(i = 0; deb != fin && i < TAILLE_GRAPHE; i++)
	{
		voisin[i] = fin;
		fin = R->pere[deb][fin];
	}
	i--;
	for(; voisin[i] != -1 && i >= 0; i--)
	{
		afficher_connexion(fo,c,deb,voisin[i],JAUNE);
		deb = voisin[i];
	}
}


void interaction_joueur(graphe * G,flame_obj_t * fo,routage * R,cercle_t * c)
{
	XEvent event;
	int cmp = 1;
	int id_1 = 0;
	int id_2 = 0;
	
	//flame_clear_display(fo);
	
	int click_x, click_y;
	
	while (1)
    {
		if (XPending(fo->display) > 0)
		{
		  XNextEvent(fo->display, &event);
		  if(recupere_clavier(event) == 'q') { break; }
		  if (event.type == ButtonPress)
		  {
				click_x = event.xkey.x;
				click_y = event.xkey.y;	
				colorer_cercle(&c[trouve_id(click_x,click_y)],JAUNE);
				afficher_cercle(fo,&c[trouve_id(click_x,click_y)]);
				if(cmp == 0) id_1 = trouve_id(click_x,click_y);
				else id_2 = trouve_id(click_x,click_y);
				cmp ++;
		  }
		if(cmp == 1)
		{
			cmp = 0;
			affiche_chemin(fo,R,c,id_1,id_2);
		}
		else
		{
			//initialisation_objets_graphique(G,fo,c);
			//usleep(100000); 
		}  
	  }
  }
}

void gestion_fenetre_graphique(graphe* G, routage *R)
{
	// > Initialisation du canvas:
	flame_obj_t * fo = init_canvas();
	
	cercle_t c[TAILLE_GRAPHE];
	
	initialisation_objets_graphique(G,fo,c);
	
	interaction_joueur(G,fo,R,c);
	flame_close(fo);
}
