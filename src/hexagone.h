#ifndef HEXAGONE
#define HEXAGONE

/*Structure de l'hexagone :
 si id_player==0 => hexagone non occupé
 si id_player==i (i>0)=> hexagone occupé par le joueur i*/

typedef struct et_hexagone{
  int id_player;
  int abscisse;
  int ordonnee;
}hexagone;


/*Constructeur*/

hexagone create_hexagon(int abs,int ord);

int be_free_hexagon(hexagone h);

void edit_hexagon(hexagone *h,int id);

int adjacent_hexagone(hexagone h, hexagone i);

#endif