/* Gestion des entrées */ 

/**
 * Fonction qui permet de vérifié si l'utilisateur veut quitter
 * @param chaine de caractere représentant l'entrée clavier
 * @return -1 si veut quitter et 1 sinon
 * */
int is_quit(char * buf);

/**
 * Permet de récupérer les valeurs données en entrées du terminal
 * @param dest permet de savoir si le noeuds est destinaire ou pas (change de valeur à chaque appelle de fonction (prend 1 puis 0 etc..)
 * @param buf
 * @return -1 pour quitter ou le noeuds que l'utilisateur à donnée en entrée
 * */
int input_value(int * dest,char * buf);
