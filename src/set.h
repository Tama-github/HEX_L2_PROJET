#ifndef _SET_H_
#define _SET_H_
#include <stdlib.h>

#include "hexagone.h"
#include "board.h"

typedef struct s_Board* Board;
typedef struct et_Cell CellSet;
typedef struct et_Set* Set;

Set createSet(int idPlayer);

Set addHexagone(Set e, Hexagone h);

void deleteSet(Set s);

Set unionSet(Set a, Set b);

void showSet(Set s);

int isHexAdjToSet (Set set, Hexagone hex);

int getIdPlayer (Set set);

int victorySet (Set set);

void displaySetInFile (Set set, FILE* f, Board board);

#endif