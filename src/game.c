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

typedef struct et_CellVictory {
	CellVictory * next;
	Set set;
} s_CellVictory;

CellVictory* createCellVictory (Set set) {
	CellVictory* res = (CellVictory*)malloc(sizeof(CellVictory));
	res->set = set;
	return res;
}

void deleteCellVictory (CellVictory* c) {
	deleteSet(c->set);
	free(c);
}

typedef struct et_Victory {
	int size;
	CellVictory* first;
} s_Victory;

Victory createVictory () {
	Victory res = (Victory)malloc(sizeof(struct et_Victory));
	res->size = 0;
	res->first = NULL;
	return res;
}

void deleteVictory (Victory v) {
	CellVictory* c = v->first;
	CellVictory* tmp = NULL;
	while (c != NULL) {
		tmp = c;
		c = c->next;
		deleteCellVictory(tmp);
	}
	free(v);
}

int haveVictorySet (Game game) {
	CellVictory* c = game->victory->first;
	while (c != NULL) {
		if (victorySet(c->set))
			return 1;
		c = c->next;
	}
	return 0;
}

void showVictory (Victory v) {
	CellVictory* c = v->first;
	printf("\n");
	while (c != NULL) {
		printf ("%p: %d\n", c->set, getIdPlayer(c->set));
		showSet(c->set);
		c = c->next;
	}
	printf("\n");
}

void addSetToVictory (Victory v, Set set) {
	CellVictory* c = createCellVictory(set);
	c->next = v->first;
	v->first = c;
}

Victory removeSetFromVictory (Victory v, Set set) {
	CellVictory* c = v->first;
	CellVictory* tmp = NULL;
	int stop = 0;
	while (c != NULL && !stop) {
		if (c->set == set) {
			if (tmp == NULL) {
				v->first = c->next;
			} else {
				tmp->next = c->next;
			}

			deleteCellVictory(c);
			v->size = v->size - 1;
			stop = 1;
		}
		tmp = c;
		c = c->next;
	}
	return v;
}

Game createGame () {
	Game game = (Game)malloc(sizeof(struct s_Game));
	if (game == NULL) exit (2);
	game->gameStatus = GAME_UNSET;
	game->victory = createVictory();
	game->board = createBoard();
	game->twoLastPlay[0] = NULL;
	game->twoLastPlay[1] = NULL;
	return game;
}

void deleteGame (Game game) {
	deleteBoard(game->board);
	deleteVictory(game->victory);
	free(game);
}

void setUpGameHxH (Game game) {
	if (game->gameStatus == GAME_END)
		reinitializeGame(game);
	game->turnOf = 1;
	game->gameStatus = GAME_IN_PROGRESS;
}

void nextTurn (Game game) {
	game->turnOf = (game->turnOf%2)+1;
}

void playAnHexagone (Hexagone hex, Game game) {
	hex->idPlayer = game->turnOf;
	Set tmp = createSet(hex->idPlayer);
	Set tmp2 = NULL;
	addHexagone(tmp, hex);
	addSetToVictory(game->victory, tmp);

	CellVictory* c = game->victory->first;
	while (c != NULL) {
		if (hex->idPlayer == getIdPlayer(c->set) && isHexAdjToSet(c->set, hex) && c->set != tmp) {
			tmp2 = unionSet(c->set, tmp);
			addSetToVictory(game->victory, tmp2);
			game->victory = removeSetFromVictory(game->victory, tmp);
			game->victory = removeSetFromVictory(game->victory, c->set);
			tmp = tmp2;
			c = game->victory->first;
		}
		c = c->next;
	}
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
	while (game->victory->first != NULL) {
		game->victory = removeSetFromVictory(game->victory, game->victory->first->set);
	}
	game->victory = createVictory();
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
	fprintf(f_out, "-1 -1 -1 -1 -1\n");
	CellVictory* c = game->victory->first;
	while (c != NULL) {
		displaySetInFile(c->set, f_out, game->board);
		c = c->next;
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

	while (idPlayer != -1) {
		fscanf(f_in,"%d %d %d %d %d", &idPlayer, &i, &j, &x, &y);
		if (idPlayer != -1) {
			game->board->board[i][j]->x = x;
			game->board->board[i][j]->y = y;
			game->board->board[i][j]->idPlayer = idPlayer;
		}
	}

	Set tmp;
	int d = 1;
	while (fscanf(f_in,"%d %d %d", &idPlayer, &i, &j) != EOF) {
		if (d) {
			tmp = createSet(idPlayer);
			d = 0;
		}
		if (idPlayer != -1) {
			addHexagone(tmp, game->board->board[i][j-1]);
		} else {
			addSetToVictory(game->victory, tmp);
			d = 1;
		}
	}
	return 1;
}
