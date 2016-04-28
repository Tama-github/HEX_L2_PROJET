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
#define LOGS_WIDTH SCREEN_WIDTH - MENU_WIDTH - 50
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
/* play */
#define BUTTON_PLAY_1_POSITION_Y (MENU_HEIGHT - BUTTON_HEIGHT*3)/2
/* load */
#define BUTTON_LOAD_MENU_1_POSITION_Y (BUTTON_PLAY_1_POSITION_Y + BUTTON_HEIGHT + 5)
/* quit */
#define BUTTON_QUIT_MENU_1_POSITION_Y (BUTTON_LOAD_MENU_1_POSITION_Y + BUTTON_HEIGHT + 5)

/* MENU 2 : choix du type de partie*/
/* menu */
#define BUTTON_MENU_2_POSITION_Y (MENU_HEIGHT - BUTTON_HEIGHT*5)/2
/* hxh */
#define BUTTON_HXH_POSITION_Y (BUTTON_MENU_2_POSITION_Y + BUTTON_HEIGHT + 5)
/* hxia1 */
#define BUTTON_HXIA1_POSITION_Y (BUTTON_HXH_POSITION_Y + BUTTON_HEIGHT + 5)
/* hxia2 */
#define BUTTON_HXIA2_POSITION_Y (BUTTON_HXIA1_POSITION_Y + BUTTON_HEIGHT + 5)
/* quit */
#define BUTTON_QUIT_MENU_2_POSITION_Y (BUTTON_HXIA2_POSITION_Y + BUTTON_HEIGHT + 5)

/* MENU 3 : en jeu*/
/* menu */
#define BUTTON_MENU_3_POSITION_Y (MENU_HEIGHT - BUTTON_HEIGHT*5)/2
/* play */
#define BUTTON_SAVE_POSITION_Y (BUTTON_MENU_3_POSITION_Y + BUTTON_HEIGHT + 5)
/* save */
#define BUTTON_LOAD_MENU_3_POSITION_Y (BUTTON_SAVE_POSITION_Y + BUTTON_HEIGHT + 5)
/* load */
#define BUTTON_UNDO_MENU_3_POSITION_Y (BUTTON_LOAD_MENU_3_POSITION_Y + BUTTON_HEIGHT + 5)
/* historic */
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


/****************************************************
Créer une fenêtre.
@sortie : La fenetre créé

******************************************************/
Window createWindow ();

/****************************************************
Ferme une fenetre ouverte avec createWindow
@entré window : La fenetre a fermer

******************************************************/
void closeWindow (Window window);

/****************************************************
Agence le menu initial, de la fenetre passé en paramettre
@entré window : La fenetre dont on veux modifier le menu.

******************************************************/
void setInitMenu (Window window);

/****************************************************
Agence le menu de choix de jeu, de la fenetre passé en paramettre
@entré window : La fenetre dont on veux modifier le menu.

******************************************************/
void setGameChoiceMenu (Window window);

/****************************************************
Agance le menu d'une partie, de la fenetre passé en paramettre
@entré window : La fenetre dont on veux modifier le menu.

******************************************************/
void setInGameMenu (Window window);

/****************************************************
Change l'image du boutton passé en paramettre par celui 
désigné par le chemin passé en paramettre
@entré window : La fenetre dont on veux modifier le menu.
@entré button : Le bouton dont on veux changer l'image.
@entré imageHoverPath : Le chemin de la nouvelle image.
@sortie : La nouvelle surface.

******************************************************/
SDL_Surface* setImageForButton (Window window, SDL_Surface * button, char* imageHoverPath);

/****************************************************
Rafraichi la fenêtre.
A faire après l'appelle d'une fonction qui modifie l'apparence de la fenetre.
@entré window : La fenetre a rafraichir.

******************************************************/
void refreshWindow(Window window);

/****************************************************
Calcule et retourne,
si la position passé en paramettre est sur le boutton passé en paramettre.
@entré button : Le bouton.
@entré x : Le positionnement en x de la position à verifier.
@entré y : Le positionnement en y de la position à verifier.
@sortie : 0 si la position n'est pas dans le boutton, 1 si non.

******************************************************/
int isPosOnbutton (SDL_Surface* button, int x, int y);

/****************************************************
Affiche le pion de l'hexagonne passé en paramettre en fonction du joueur qui l'a joué.
@entré window : La fenetre concerné par l'affichage.
@entré hex : L'Haxagone auquel appartiens le pions.
@entré idPlayer : L'id du joueur qui a joué l'hexagone

******************************************************/
void displayToken (Hexagone hex, int idPlayer, Window window);

/****************************************************
Gere l'affichage du plateau.
@entré window : La fenêtre concerné par l'affichage.
@entré board : Le plateau concerné.
@entré game : Le jeu auquel appartiens le plateau.

******************************************************/
void displayBoard (Board board, Window window, Game game);

/****************************************************
Affiche dans le la fenetre de log a qui c'est le tour de jouer et qui viens de jouer quoi
@entré hex : L'hexagonne joué.
@entré game : Le jeu.
@entré qu : La file de text représantant le log.
@entré i : Les coordonné en x (tableau) de l'hexagone joué.
@entré j : Les coordonné en y (tableau) de l'hexagone joué.

******************************************************/
void logPlayerTurn (Hexagone hex, Game game, Queue qu, int i, int j);

/****************************************************
Affiche l'ensemble du log.
@entré window : La fenetre concerné par l'affichage.
@entré police : La police d'affichage du text.
@entré qu : La file contenant le text de log.

******************************************************/
void displayLog (Window window, TTF_Font *police, Queue qu);

/****************************************************
Affiche le début d'une partie dans le log.
@entré qu : La file de text contenant le log.

******************************************************/
void logBeginGame (Queue qu);

/****************************************************
Affiche dans le log la chaine de caractère passé en paramettre.
@entré qu : La file de text contenant le log.
@entré c : La chaine de caractère a enfiler dans le log.

******************************************************/
void logSomething (Queue qu, char* c);

#endif