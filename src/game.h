#ifndef _GAME_H_
#define _GAME_H_

#define GAME_UNSET 0
#define GAME_IN_PROGRESS 1
#define GAME_END 2

#define ID_PLAYER_1 1
#define ID_PLAYER_2 2

#include "board.h"

typedef struct s_Board* Board;

struct s_Game {
	int gameStatus;
	int turnOf;
	Board board;
};

typedef struct s_Game* Game;

Game createGame ();
void setUpGameHxH (Game game);
void nextTurn (Game game);
void playAnHexagone (Hexagone hex, Game game);

#endif