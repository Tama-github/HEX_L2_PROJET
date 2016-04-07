#ifndef _BOARD_H_
#define _BOARD_H_

#include "hexagone.h"
#include "Interface.h"

#define BOARD_LENGTH 11

#define FIRST_HEXAGONE_POSITION_X (BOARD_POSITION_X + 19)
#define FIRST_HEXAGONE_POSITION_Y (BOARD_POSITION_Y + 19)
#define HEXAGONE_LENGTH 30
#define HEXAGONE_HEIGHT 29
#define BOARD_EACH_LINE_SHIFT 15
#define BOARD_EACH_COLUMN_SHIFT 25

struct s_Board {
	Hexagone board [BOARD_LENGTH][BOARD_LENGTH];
};

typedef struct s_Board* Board;

Board createBoard ();
void deleteBoard (Board b);
Hexagone findHexagoneOnBoard (Board board, int x, int y);

#endif
