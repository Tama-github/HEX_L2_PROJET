#ifndef HEXAGONE
#define HEXAGONE

/*Structure de l'hexagone :
 si id_player==0 => hexagone non occupé
 si id_player==i (i>0)=> hexagone occupé par le joueur i*/



typedef struct et_hexagone* Hexagone;

/*Constructeur*/

Hexagone createHexagon (int abs, int ord);

void deleteHexagon (Hexagone h);

void setIdPlayerHexagon (Hexagone h, int id);

int isAdjacentHexagone (Hexagone h, Hexagone i);

#endif