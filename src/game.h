#ifndef _GAME_H_
#define _GAME_H_

#define GAME_UNSET 0
#define GAME_IN_PROGRESS 1
#define GAME_END 2

#define TURN_PLAYER_1 1
#define TURN_PLAYER_2 2

typedef struct s_Game* Game;

Game createGame ();
void setUpGameHxH (Game game);
void nextTurn (Game game);
Hexagone playAnHexagone (Game game, int x, int y);

#endif