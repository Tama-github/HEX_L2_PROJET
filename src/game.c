#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "game.h"



Game createGame () {
	Game game = (Game)malloc(sizeof(struct s_Game*));
	game->gameStatus = GAME_UNSET;
	game->board = createBoard();
	game->twoLastPlay[0] = NULL;
	game->twoLastPlay[1] = NULL;
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

void playAnHexagone (Hexagone hex, Game game) {
	hex->idPlayer = game->turnOf;
	nextTurn(game);
}

void storeAPlay (Game game, Hexagone hex) {
	game->twoLastPlay[game->turnOf%2] = hex;
}

int undoAction (Game game) {
	if (game->twoLastPlay[0] != NULL && game->twoLastPlay[1] != NULL) {
		game->twoLastPlay[0]->idPlayer = 0;
		game->twoLastPlay[1]->idPlayer = 0;
		game->twoLastPlay[0] = NULL;
		game->twoLastPlay[1] = NULL;
		return 1;
	}
	return 0;
}



