#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "game.h"



Game createGame () {
	Game game = (Game)malloc(sizeof(struct s_Game*));
	if (game == NULL) exit (2);
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

void endGame (Game game) {
	deleteGame(game);
	game = createGame();
}

void reinitializeGame (Game game) {
	game->gameStatus = GAME_UNSET;
	game->twoLastPlay[0] = NULL;
	game->twoLastPlay[1] = NULL;
	reinitializeBoard(game->board);
}

void saveGame (Game game) {
	FILE* f_out = fopen("saves/save.txt", "w");
	if (f_out == NULL) {
		fprintf(stderr, "problème d'ouverture du fichier\n");
		exit(1);
	}
	fprintf(f_out,"%d\n", game->turnOf);
	int i, j;
	for (i = 0; i < BOARD_LENGTH; i++) {
		for (j = 0; j < BOARD_LENGTH; j++) {
			if (game->board->board[i][j]->idPlayer != UNPLAYED) {
				fprintf(f_out, "%d %d %d %d %d\n", game->board->board[i][j]->idPlayer, i, j, game->board->board[i][j]->x, game->board->board[i][j]->y);
			}
		}
	}
	fclose(f_out);
}

int loadGame (Game game) {
	FILE* f_in = fopen("saves/save.txt", "r");
	if (f_in == NULL) {
		return 0;
	}
	int idPlayer, i, j, x, y;
	fscanf(f_in, "%d", &idPlayer);
	game->turnOf = idPlayer;

	while (fscanf(f_in,"%d %d %d %d %d", &idPlayer, &i, &j, &x, &y) != EOF) {
		game->board->board[i][j]->x = x;
		game->board->board[i][j]->y = y;
		game->board->board[i][j]->idPlayer = idPlayer;
	}

	return 1;
}
