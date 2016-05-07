#ifndef _HEXAGONE_H
#define _HEXAGONE_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "constantes.h"

/* Structure représentant un hexagone. */
struct et_hexagone{
  int idPlayer; /* id du joueur qui a joue l'hexagone*/
  int x; 		/* Positionement en pixel sur l'axe des x */
  int y;		/* Positionement en pixel sur l'axe des y */
  int hold;		/* Booleen qui permet de savoir si la souris survole l'hexagone */
};

typedef struct et_hexagone* Hexagone;

/*Constructeur*/

/****************************************************
Créé et retourne un Hexagonne
@entré : x positionement en x de l'hexagone à créé
@entré : y positionement en y de l'hexagone à créé
@sortie : L'hexagonne créé

******************************************************/
Hexagone createHexagone (int x, int y);


/****************************************************
Supprime un hexagonne créé avec createHexagonne
@entré : L'hexagone a supprimer

******************************************************/
void deleteHexagone (Hexagone h);

/****************************************************
Modifie le champ idPlayer de l'hexagonne passé 
en paramettre.
@entré : h L'hexagone a modifier
@entré : id l'id du joueur qui a joué l'hexagone

******************************************************/
void setIdPlayerHexagone (Hexagone h, int id);

/****************************************************
Verifie si les coordonnées passé en paramettre sont
sur la surface de l'hexagone passé en paramettre.
@entré : h dont on verifie la surface.
@entré : x coordonnée en x du point à verifier.
@entré : y coordonnée en y du point à verifier.

******************************************************/
int isCoordOnHexagone (Hexagone h, int x, int y);

/****************************************************
Verifie si l'hexagone passé en parametre est sur le bord haut ou sur le bord gauche du plateau
@entré hex : L'hexagone à verifier
@sortie : retourne 1 si l'hexagone est sur le bord haut ou gauche du plateau, 0 si non.

******************************************************/
int isHexOnSide1 (Hexagone hex);

/****************************************************
Verifie si l'hexagone passé en parametre est sur le bord bas ou sur le bord droit du plateau
@entré hex : L'hexagone à verifier
@sortie : retourne 1 si l'hexagone est sur le bord bas ou droite du plateau, 0 si non.

******************************************************/
int isHexOnSide2 (Hexagone hex);

/****************************************************
Verifie si deux hexagones sont adjascents.
@entré h : Un hexagone
@entré i : Un autre Hexagone
@sortie : 1 si les deu hexagones sont adjascent, 0 si non.

******************************************************/
int isAdjacentHexagone (Hexagone h, Hexagone i);

#endif