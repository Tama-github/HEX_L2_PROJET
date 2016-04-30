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
  if (h == i)
    return 0;
  
  if (h->y == i->y)
    return(i->x == h->x-HEXAGONE_LENGTH || i->x == h->x+HEXAGONE_LENGTH);

  if (h->y == i->y - BOARD_EACH_COLUMN_SHIFT || h->y == i->y + BOARD_EACH_COLUMN_SHIFT) {
    return(h->x == (i->x-BOARD_EACH_LINE_SHIFT) || h->x == (i->x + BOARD_EACH_LINE_SHIFT));
  }

  return(0);
}


int isHexOnSide1 (Hexagone hex) {
  if (hex->idPlayer == ID_PLAYER_2) {
    if (hex->y == FIRST_HEXAGONE_POSITION_Y) 
      return 1;
  } else if (hex->idPlayer == ID_PLAYER_1) {
    int i;
    int res = 0;
    for (i = 0; i < BOARD_LENGTH && !res; i++) {
      if (hex->y == FIRST_HEXAGONE_POSITION_Y + i * BOARD_EACH_COLUMN_SHIFT) {
        res = (hex->x == FIRST_HEXAGONE_POSITION_X + i * BOARD_EACH_LINE_SHIFT);
      }
    }
    return res;
  }

  return 0;
}

int isHexOnSide2 (Hexagone hex) {
  if (hex->idPlayer == ID_PLAYER_2) {
    if (hex->y == LAST_HEXAGONE_POSITION_Y)
      return 1;
  } else if (hex->idPlayer == ID_PLAYER_1) {
    int i;
    int res = 0;
    for (i = 0; i < BOARD_LENGTH && !res; i++) {
      if (hex->y == FIRST_HEXAGONE_POSITION_Y + i * BOARD_EACH_COLUMN_SHIFT) {
        res = (hex->x == LAST_HEXAGONE_POSITION_X + i * BOARD_EACH_LINE_SHIFT);
      }
    }
    return res;
  }
  return 0;
}

