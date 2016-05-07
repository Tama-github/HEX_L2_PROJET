#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "board.h"


Board createBoard () {
	Board b = (Board)malloc(sizeof(struct s_Board));
	assert(b != NULL);
	int i, j;
	int x = FIRST_HEXAGONE_POSITION_X;
	int y = FIRST_HEXAGONE_POSITION_Y;
	for (i = 0; i < BOARD_LENGTH; i++) {
		x = FIRST_HEXAGONE_POSITION_X + i*BOARD_EACH_LINE_SHIFT;
		for (j = 0; j < BOARD_LENGTH; j++) {
			b->board[i][j] = createHexagone(x, y);
			x = x + HEXAGONE_LENGTH;
		}
		y = y + BOARD_EACH_COLUMN_SHIFT;
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

Hexagone findHexagoneOnBoard (Board board, int x, int y, int *v, int *w) {
	int i,j;
	Hexagone res = NULL;
	int find = 0;
	for (i = 0; i < BOARD_LENGTH; i++) {
		for (j = 0; j < BOARD_LENGTH; j++) {
			if (isCoordOnHexagone(board->board[i][j], x, y) && !find) {
				res = board->board[i][j];
				find = 1;
				board->board[i][j]->hold = 1;
				*v=i+1;
				*w=j+1;
			} else {
				board->board[i][j]->hold = 0;
			}
		}
	}
	return res;
}



void reinitializeBoard (Board b) {
	int i, j;
	for (i = 0; i < BOARD_LENGTH; i++) {
		for (j = 0; j < BOARD_LENGTH; j++) {
			b->board[i][j]->idPlayer = UNPLAYED;
		}
	}
}
