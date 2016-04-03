#ifndef _BOARD_H_
#define _BOARD_H_

#include "hexagone.h"

#define BOARD_LENGTH 11

#define FIRST_HEXAGONE_POSITION_X 319
#define FIRST_HEXAGONE_POSITION_Y 160
#define HEXAGONE_LENGTH 30
#define HEXAGONE_HEIGHT 25
#define BOARD_EACH_LINE_SHIFT 15



typedef struct s_Board* Board;

Board createBoard ();
void deleteBoard (Board b);
Hexagone findHexagoneOnBoard (Board board, int x, int y);

#endif
