#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "board.h"
#include "game.h"

struct s_Game {
	int gameStatus;
	int turnOf;
	Board board;
};

Game createGame () {
	Game game = (Game)malloc(sizeof(struct s_Game*));
	game->gameStatus = GAME_UNSET;
	game->board = createBoard();
	return game;
}

void deleteGame (Game game) {
	deleteBoard(game->board);
	free(game);
}

void setUpGameHxH (Game game) {
	game->turnOf = 1;
	game->gameStatus = GAME_IN_PROGRESS;
}

void nextTurn (Game game) {
	game->turnOf = (game->turnOf%2)+1;
}

Hexagone playAnHexagone (Game game, int x, int y) {
	Hexagone hexToPlay;
	hexToPlay = findHexagoneOnBoard(game->board, x, y);
	if (hexToPlay != NULL) {
		nextTurn(game);
	}
	return hexToPlay;
}


