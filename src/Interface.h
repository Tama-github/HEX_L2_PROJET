#include "SDL/SDL.h"
#include "SDL/SDL_image.h"


/* infos de la fenêtre */
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600
#define SCREEN_BPP 32

/* dimmenssions et position du menu */
#define MENU_WIDTH SCREEN_WIDTH/4
#define MENU_HEIGHT SCREEN_HEIGHT

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

/* play */
#define BUTTON_PLAY_POSITION_Y (MENU_HEIGHT - BUTTON_HEIGHT*5)/2
/*  */
#define BUTTON__POSITION_Y (BUTTON_PLAY_POSITION_Y + BUTTON_HEIGHT + 5)