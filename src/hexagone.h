#ifndef _HEXAGONE_H
#define _HEXAGONE_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"


/*Structure de l'hexagone :
 si id_player==0 => hexagone non occupé
 si id_player==i (i>0)=> hexagone occupé par le joueur i*/

struct et_hexagone{
  int idPlayer;
  int x;
  int y;
  int hold;
};

typedef struct et_hexagone* Hexagone;

/*Constructeur*/

Hexagone createHexagone (int x, int y);

void deleteHexagone (Hexagone h);

void setIdPlayerHexagone (Hexagone h, int id);

int isCoordOnHexagone (Hexagone h, int x, int y);

int isAdjacentHexagone (Hexagone h, Hexagone i);

#endif