#ifndef _GAME_H_
#define _GAME_H_

#define GAME_UNSET 0
#define GAME_IN_PROGRESS 1
#define GAME_END 2

#define UNPLAYED 0
#define ID_PLAYER_1 1
#define ID_PLAYER_2 2

#include "board.h"

typedef struct s_Board* Board;

struct s_Game {
	int gameStatus;
	int turnOf;
	Hexagone twoLastPlay [2];
	Board board;
};

typedef struct s_Game* Game;

Game createGame ();
void deleteGame (Game game);
void setUpGameHxH (Game game);
void nextTurn (Game game);
void playAnHexagone (Hexagone hex, Game game);
void storeAPlay (Game game, Hexagone hex);
int undoAction (Game game);
void endGame (Game game);
void saveGame (Game game);
int loadGame (Game game);
void reinitializeGame (Game game);

#endif