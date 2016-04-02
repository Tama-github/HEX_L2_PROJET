#ifndef REGLES
#define REGLES
#include "hexagone.h"


/*Vérification que c'est au joueur idplayer de jouer*/
int ckeck_round(int nbtour, int idplayer);


/*Renvoie l'idplayer du joueur à qui c'est le tour de jouer*/
int who_play(int nbtour);


/*Vérifie que l'hexagone s'électionné soit bien voisin et vide d'un appartenant au joueur*/
int ckeck_select_hexagon(hexagone h, hexagone i);

#endif