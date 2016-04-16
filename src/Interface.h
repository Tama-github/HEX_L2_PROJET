#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "board.h"
#include "game.h"
#include "queue.h"

/* types de menu */
 #define UNDIFINE_MENU 0
 #define INIT_MENU 1
 #define GAME_CHOICE_MENU 2
 #define IN_GAME_MENU 3

/* infos de la fenêtre */
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600
#define SCREEN_BPP 32

/* dimmenssions et position du menu */
#define MENU_WIDTH SCREEN_WIDTH/4
#define MENU_HEIGHT SCREEN_HEIGHT

/* dimenssions et position des logs*/
#define LOGS_WIDTH SCREEN_WIDTH/2
#define LOGS_HEIGHT 110
#define LOGS_POSITION_X MENU_WIDTH + 10;
#define LOGS_POSITION_Y SCREEN_HEIGHT - 125;

/* dimenssion du plateau de jeu */
#define BOARD_WIDTH 524
#define BOARD_HEIGTH 319

/* position du plateau de jeu */
#define BOARD_POSITION_X (SCREEN_WIDTH + MENU_WIDTH - BOARD_WIDTH) / 2
#define BOARD_POSITION_Y (SCREEN_HEIGHT - BOARD_HEIGTH) / 2

/* dimension des boutons */
#define BUTTON_WIDTH (MENU_WIDTH*2/3)
#define BUTTON_HEIGHT (MENU_HEIGHT/10)

/*Position des bouttons */
#define BUTTON_POSITION_X (MENU_WIDTH - BUTTON_WIDTH)/2

/* MENU 1 : initiale */
/* menu */
#define BUTTON_MENU_1_POSITION_Y (MENU_HEIGHT - BUTTON_HEIGHT*4)/2
/* play */
#define BUTTON_PLAY_1_POSITION_Y (BUTTON_MENU_1_POSITION_Y + BUTTON_HEIGHT + 5)
/* load */
#define BUTTON_LOAD_MENU_1_POSITION_Y (BUTTON_PLAY_1_POSITION_Y + BUTTON_HEIGHT + 5)
/* quit */
#define BUTTON_QUIT_MENU_1_POSITION_Y (BUTTON_LOAD_MENU_1_POSITION_Y + BUTTON_HEIGHT + 5)

/* MENU 2 : choix du type de partie*/
/* menu */
#define BUTTON_MENU_2_POSITION_Y (MENU_HEIGHT - BUTTON_HEIGHT*6)/2
/* hxh */
#define BUTTON_HXH_POSITION_Y (BUTTON_MENU_2_POSITION_Y + BUTTON_HEIGHT + 5)
/* hxia1 */
#define BUTTON_HXIA1_POSITION_Y (BUTTON_HXH_POSITION_Y + BUTTON_HEIGHT + 5)
/* hxia2 */
#define BUTTON_HXIA2_POSITION_Y (BUTTON_HXIA1_POSITION_Y + BUTTON_HEIGHT + 5)
/* undo */
#define BUTTON_UNDO_MENU_2_POSITION_Y (BUTTON_HXIA2_POSITION_Y + BUTTON_HEIGHT + 5)
/* quit */
#define BUTTON_QUIT_MENU_2_POSITION_Y (BUTTON_UNDO_MENU_2_POSITION_Y + BUTTON_HEIGHT + 5)

/* MENU 3 : en jeu*/
/* menu */
#define BUTTON_MENU_3_POSITION_Y (MENU_HEIGHT - BUTTON_HEIGHT*7)/2
/* play */
#define BUTTON_PLAY_3_POSITION_Y (BUTTON_MENU_3_POSITION_Y + BUTTON_HEIGHT + 5)
/* save */
#define BUTTON_SAVE_POSITION_Y (BUTTON_PLAY_3_POSITION_Y + BUTTON_HEIGHT + 5)
/* load */
#define BUTTON_LOAD_MENU_3_POSITION_Y (BUTTON_SAVE_POSITION_Y + BUTTON_HEIGHT + 5)
/* historic */
#define BUTTON_HISTORIC_POSITION_Y (BUTTON_LOAD_MENU_3_POSITION_Y + BUTTON_HEIGHT + 5)
/* undo */
#define BUTTON_UNDO_MENU_3_POSITION_Y (BUTTON_HISTORIC_POSITION_Y + BUTTON_HEIGHT + 5)
/* quit */
#define BUTTON_QUIT_MENU_3_POSITION_Y (BUTTON_UNDO_MENU_3_POSITION_Y + BUTTON_HEIGHT + 5)

/* Jetons à afficher */
#define TOKEN_RELATIVE_HEXAGONE_POSITION_X 4
#define TOKEN_RELATIVE_HEXAGONE_POSITION_Y 4

/* longueur maximum du text de log */
#define QUEUE_MAX_SIZE 6

typedef struct s_Board* Board;

typedef struct s_ImgHexagones {
	SDL_Surface * emptyHex;
	SDL_Surface * redHex;
	SDL_Surface * blueHex;
}* ImgHexagones;

struct s_Window {
	int menuType;

	SDL_Surface * screen;
	SDL_Surface * menu;
	SDL_Surface * board;
	SDL_Surface * logs;
	Queue textInLog;
	SDL_Surface ** text;
	ImgHexagones hex;

	/* tous les boutons */
	SDL_Surface * buttonMenu;
	SDL_Surface * buttonPlay;
	SDL_Surface * buttonLoad;
	SDL_Surface * buttonSave;
	SDL_Surface * buttonUndo;
	SDL_Surface * buttonHistoric;
	SDL_Surface * buttonQuit;
	SDL_Surface * buttonHxH;
	SDL_Surface * buttonHxIA1;
	SDL_Surface * buttonHxIA2;
};



typedef struct s_Window * Window;
typedef struct s_Game* Game;

Window createWindow ();
void closeWindow (Window window);
void setInitMenu (Window window);
void setGameChoiceMenu (Window window);
void setInGameMenu (Window window);
SDL_Surface* setImageForButton (Window window, SDL_Surface * button, char* imageHoverPath);
void refreshWindow(Window window);
int isPosOnbutton (SDL_Surface* button, int x, int y);
void displayToken (Hexagone hex, int i, Window window);
void displayBoard (Board board, Window window, Game game);
void logPlayerTurn(Hexagone hex, Game game, Queue qu);
void displayLog (Window window, TTF_Font *police, Queue qu);
void logBeginGame (Queue qu);

#endif