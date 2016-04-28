#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "hexagone.h"



Hexagone createHexagone (int x, int y) {
  Hexagone h = (Hexagone)malloc(sizeof(struct et_hexagone*));
  if (h == NULL) exit (2);
  h->x = x;
  h->y = y;
  h->idPlayer = 0;
  h->hold = 0;
  return(h);
}

void deleteHexagone (Hexagone h) {
  free(h);
}

void setIdPlayerHexagone (Hexagone h, int id) {
  h->idPlayer = id;
}

int isCoordOnHexagone (Hexagone h, int x, int y) {
  int res = 0;
  if (x >= h->x && x <= h->x + 30 
    && y >= h->y && y <= h->y + 30) {
    res = 1;
    h->hold = 1;
  } else {
    h->hold = 0;
  }
  return res;
}

int isAdjacentHexagone (Hexagone h, Hexagone i) {
  if (h->x == i->x)
    return(i->y == h->y-1 || i->y == h->y+1);
  
  if (h->y == i->y)
    return(i->x == h->x-1 || i->x == h->x+1);

  if (h->y == i->y-1)
    return(h->x == i->x-1);
  
  if (h->y == i->y+1)
    return(h->x == i->x+1);

  return(0);
}