#ifndef _BOARD_H_
#define _BOARD_H_

#include "hexagone.h"
#include "Interface.h"
#include "constantes.h"

struct s_Board {
	Hexagone board [BOARD_LENGTH][BOARD_LENGTH];
};

typedef struct s_Board* Board;

Board createBoard ();
void deleteBoard (Board b);
Hexagone findHexagoneOnBoard (Board board, int x, int y, int *i, int *j);
void reinitializeBoard (Board b);

#endif
