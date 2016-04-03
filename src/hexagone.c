#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "hexagone.h"

struct et_hexagone{
  int id_player;
  int abscisse;
  int ordonnee;
};

Hexagone createHexagon (int abs, int ord) {
  Hexagone h = (Hexagone)malloc(sizeof(struct et_hexagone*));
  h->abscisse = abs;
  h->ordonnee = ord;
  h->id_player = 0;
  return(h);
}

void deleteHexagon (Hexagone h) {
  free(h);
}

void setIdPlayerHexagon (Hexagone h, int id) {
  h->id_player = id;
}

int isAdjacentHexagone (Hexagone h, Hexagone i) {
  if (h->abscisse == i->abscisse)
    return(i->ordonnee == h->ordonnee-1 || i->ordonnee == h->ordonnee+1);
  
  if (h->ordonnee == i->ordonnee)
    return(i->abscisse == h->abscisse-1 || i->abscisse == h->abscisse+1);
  
  if (h->ordonnee == i->ordonnee-1)
    return(h->abscisse == i->abscisse-1);
  
  if (h->ordonnee == i->ordonnee+1)
    return(h->abscisse == i->abscisse+1);

  return(0);
}