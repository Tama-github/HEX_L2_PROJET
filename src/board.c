#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "board.h"


struct s_Board {
	Hexagone board [BOARD_LENGTH][BOARD_LENGTH];
};

Board createBoard () {
	Board b = (Board)malloc(sizeof(struct s_Board));
	int i, j;
	int x = FIRST_HEXAGONE_POSITION_X;
	int y;
	for (i = 0; i < BOARD_LENGTH; i++) {
		y = FIRST_HEXAGONE_POSITION_Y + i*BOARD_EACH_LINE_SHIFT;
		for (j = 0; j < BOARD_LENGTH; j++) {
			b->board[i][j] = createHexagone(x, y);
			y = y + HEXAGONE_LENGTH;
		}
		x = x + HEXAGONE_HEIGHT;
	}
	return b;
}

void deleteBoard (Board b) {
	int i, j;
	for (i = 0; i < BOARD_LENGTH; i++) {
		for (j = 0; j < BOARD_LENGTH; j++) {
			deleteHexagone(b->board[i][j]);
		}
	}
	free(b);
}

Hexagone findHexagoneOnBoard (Board board, int x, int y) {
	int i, j;
	Hexagone res = NULL;
	int find = 0;
	for (i = 0; i < BOARD_LENGTH && !find; i++) {
		for (j = 0; j < BOARD_LENGTH && !find; j++) {
			if (isCoordOnHexagone(board->board[i][j], x, y)) {
				res = board->board[i][j];
				find = 1;
			}
		}
	}
	return res;
}
