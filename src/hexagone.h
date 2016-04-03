#ifndef HEXAGONE
#define HEXAGONE

/*Structure de l'hexagone :
 si id_player==0 => hexagone non occupé
 si id_player==i (i>0)=> hexagone occupé par le joueur i*/



typedef struct et_hexagone* Hexagone;

/*Constructeur*/

Hexagone createHexagone (int abs, int ord);

void deleteHexagone (Hexagone h);

void setIdPlayerHexagone (Hexagone h, int id);

int isCoordOnHexagone (Hexagone h, int x, int y);

int isAdjacentHexagone (Hexagone h, Hexagone i);

#endif