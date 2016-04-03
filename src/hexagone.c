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

Hexagone createHexagone (int abs, int ord) {
  Hexagone h = (Hexagone)malloc(sizeof(struct et_hexagone*));
  h->abscisse = abs;
  h->ordonnee = ord;
  h->id_player = 0;
  return(h);
}

void deleteHexagone (Hexagone h) {
  free(h);
}

void setIdPlayerHexagone (Hexagone h, int id) {
  h->id_player = id;
}

int isCoordOnHexagone (Hexagone h, int x, int y) {
  int res = 0;
  if (x >= h->abscisse && x <= h->abscisse + 30 
    && y >= h->ordonnee && y <= h->ordonnee + 30) {
    res = 1;
  }
  return res;
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