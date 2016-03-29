#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "Interface.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"



Window createWindow () {
	Window res = (Window)malloc(sizeof(struct s_Window));
	res->screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE);
    
    res->menuType = UNDIFINE_MENU;

	SDL_Rect position;
    position.x = 0;
    position.y = 0;

    if (res->screen == NULL ) {
        fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n", SDL_GetError());
        exit(1);
    }

    /* color */
    Uint32 BACKGROUND_COLOR = SDL_MapRGB(res->screen->format, 200, 200, 200);
    Uint32 MENU_COLOR = SDL_MapRGB(res->screen->format, 255, 255, 255);

    /* creations des objets graphique */
    SDL_FillRect(res->screen, NULL, BACKGROUND_COLOR);
    SDL_WM_SetCaption("HEX", NULL);

    res->menu = SDL_CreateRGBSurface(SDL_SWSURFACE, MENU_WIDTH, MENU_HEIGHT, SCREEN_BPP, 0, 0, 0, 0);
    SDL_FillRect(res->menu, NULL, MENU_COLOR);
    SDL_BlitSurface(res->menu, NULL, res->screen, &position);


    position.x = BOARD_POSITION_X;
    position.y = BOARD_POSITION_Y;
    res->board = IMG_Load("Images/hex.png");
    SDL_BlitSurface(res->board, NULL, res->screen, &position);
    res->buttonMenu = NULL;
    res->buttonPlay = NULL;
    res->buttonLoad = NULL;
    res->buttonQuit = NULL;
    res->buttonSave = NULL;
    res->buttonUndo = NULL;
    res->buttonHistoric = NULL;
    res->buttonHxH = NULL;
    res->buttonHxIA1 = NULL;
    res->buttonHxIA2 = NULL;

    return res;
} 

void freeButtons (Window window) {
	if (window->buttonMenu != NULL) 
    SDL_FreeSurface(window->buttonMenu);
	if (window->buttonPlay != NULL)
    SDL_FreeSurface(window->buttonPlay);
	if (window->buttonLoad != NULL)
    SDL_FreeSurface(window->buttonLoad);
	if (window->buttonSave != NULL)
    SDL_FreeSurface(window->buttonSave);
	if (window->buttonUndo != NULL)
    SDL_FreeSurface(window->buttonUndo);
	if (window->buttonHistoric != NULL)
    SDL_FreeSurface(window->buttonHistoric);
	if (window->buttonQuit != NULL)
    SDL_FreeSurface(window->buttonQuit);
	if (window->buttonHxH != NULL)
    SDL_FreeSurface(window->buttonHxH);
	if (window->buttonHxIA1 != NULL)
    SDL_FreeSurface(window->buttonHxIA1);
	if (window->buttonHxIA2 != NULL)
    SDL_FreeSurface(window->buttonHxIA2);
    
    SDL_Rect pos;
    pos.x = 0;
    pos.y = 0;
    SDL_BlitSurface(window->menu, NULL, window->screen, &pos);
}

void closeWindow (Window window) {

	freeButtons(window);
    SDL_FreeSurface(window->menu);
    SDL_FreeSurface(window->board);
	SDL_Quit();
	free(window);
}

void setInitMenu (Window window) {
	freeButtons(window);
	window->menuType = INIT_MENU;
	SDL_Rect position;
	position.x = BUTTON_POSITION_X;
    position.y = BUTTON_MENU_1_POSITION_Y;
    window->buttonMenu = IMG_Load("Images/Bouton-menu-normal.jpg");
    SDL_BlitSurface(window->buttonMenu, NULL, window->screen, &position);
    window->buttonMenu->clip_rect.x = position.x;
    window->buttonMenu->clip_rect.y = position.y;

    position.y = BUTTON_PLAY_1_POSITION_Y;
    window->buttonPlay = IMG_Load("Images/Bouton-jouer-normal.jpg");
    SDL_BlitSurface(window->buttonPlay, NULL, window->screen, &position);
    window->buttonPlay->clip_rect.x = position.x;
    window->buttonPlay->clip_rect.y = position.y;

    position.y = BUTTON_LOAD_MENU_1_POSITION_Y;
    window->buttonLoad = IMG_Load("Images/Bouton-charger-normal.jpg");
    SDL_BlitSurface(window->buttonLoad, NULL, window->screen, &position);
    window->buttonLoad->clip_rect.x = position.x;
    window->buttonLoad->clip_rect.y = position.y;

    position.y = BUTTON_QUIT_MENU_1_POSITION_Y;
    window->buttonQuit = IMG_Load("Images/Bouton-quiter-normal.jpg");
    SDL_BlitSurface(window->buttonQuit, NULL, window->screen, &position);
    window->buttonQuit->clip_rect.x = position.x;
    window->buttonQuit->clip_rect.y = position.y;

    window->buttonSave = NULL;
    window->buttonUndo = NULL;
    window->buttonHistoric = NULL;
    window->buttonHxH = NULL;
    window->buttonHxIA1 = NULL;
    window->buttonHxIA2 = NULL;
}

void setGameChoiceMenu (Window window) {
	freeButtons(window);
	window->menuType = GAME_CHOICE_MENU;
	SDL_Rect position;
	position.x = BUTTON_POSITION_X;
    position.y = BUTTON_MENU_2_POSITION_Y;
    window->buttonMenu = IMG_Load("Images/Bouton-menu-normal.jpg");
    SDL_BlitSurface(window->buttonMenu, NULL, window->screen, &position);
    window->buttonMenu->clip_rect.x = position.x;
    window->buttonMenu->clip_rect.y = position.y;

    position.y = BUTTON_HXH_POSITION_Y;
    window->buttonHxH = IMG_Load("Images/Bouton-hxh-normal.jpg");
    SDL_BlitSurface(window->buttonHxH, NULL, window->screen, &position);
    window->buttonHxH->clip_rect.x = position.x;
    window->buttonHxH->clip_rect.y = position.y;

    position.y = BUTTON_HXIA1_POSITION_Y;
    window->buttonHxIA1 = IMG_Load("Images/Bouton-hxia1-normal.jpg");
    SDL_BlitSurface(window->buttonHxIA1, NULL, window->screen, &position);
    window->buttonHxIA1->clip_rect.x = position.x;
    window->buttonHxIA1->clip_rect.y = position.y;

    position.y = BUTTON_HXIA2_POSITION_Y;
    window->buttonHxIA2 = IMG_Load("Images/Bouton-hxia2-normal.jpg");
    SDL_BlitSurface(window->buttonHxIA2, NULL, window->screen, &position);
    window->buttonHxIA2->clip_rect.x = position.x;
    window->buttonHxIA2->clip_rect.y = position.y;

    position.y = BUTTON_UNDO_MENU_2_POSITION_Y;
    window->buttonUndo = IMG_Load("Images/Bouton-annuler-normal.jpg");
    SDL_BlitSurface(window->buttonUndo, NULL, window->screen, &position);
    window->buttonUndo->clip_rect.x = position.x;
    window->buttonUndo->clip_rect.y = position.y;

    position.y = BUTTON_QUIT_MENU_2_POSITION_Y;
    window->buttonQuit = IMG_Load("Images/Bouton-quiter-normal.jpg");
    SDL_BlitSurface(window->buttonQuit, NULL, window->screen, &position);
    window->buttonQuit->clip_rect.x = position.x;
    window->buttonQuit->clip_rect.y = position.y;

    window->buttonPlay = NULL;
    window->buttonLoad = NULL;
    window->buttonSave = NULL;
    window->buttonHistoric = NULL;
}

void setInGameMenu (Window window) {
	freeButtons(window);
	window->menuType = IN_GAME_MENU;
	SDL_Rect position;
	position.x = BUTTON_POSITION_X;
    position.y = BUTTON_MENU_3_POSITION_Y;
    window->buttonMenu = IMG_Load("Images/Bouton-menu-normal.jpg");
    SDL_BlitSurface(window->buttonMenu, NULL, window->screen, &position);
    window->buttonMenu->clip_rect.x = position.x;
    window->buttonMenu->clip_rect.y = position.y;

    position.y = BUTTON_PLAY_3_POSITION_Y;
    window->buttonPlay = IMG_Load("Images/Bouton-jouer-normal.jpg");
    SDL_BlitSurface(window->buttonPlay, NULL, window->screen, &position);
    window->buttonPlay->clip_rect.x = position.x;
    window->buttonPlay->clip_rect.y = position.y;

    position.y = BUTTON_SAVE_POSITION_Y;
    window->buttonSave = IMG_Load("Images/Bouton-sauver-normal.jpg");
    SDL_BlitSurface(window->buttonSave, NULL, window->screen, &position);
    window->buttonSave->clip_rect.x = position.x;
    window->buttonSave->clip_rect.y = position.y;

    position.y = BUTTON_LOAD_MENU_3_POSITION_Y;
    window->buttonLoad = IMG_Load("Images/Bouton-charger-normal.jpg");
    SDL_BlitSurface(window->buttonLoad, NULL, window->screen, &position);
    window->buttonLoad->clip_rect.x = position.x;
    window->buttonLoad->clip_rect.y = position.y;

    position.y = BUTTON_HISTORIC_POSITION_Y;
    window->buttonHistoric = IMG_Load("Images/Bouton-historique-normal.jpg");
    SDL_BlitSurface(window->buttonHistoric, NULL, window->screen, &position);
    window->buttonHistoric->clip_rect.x = position.x;
    window->buttonHistoric->clip_rect.y = position.y;

    position.y = BUTTON_UNDO_MENU_3_POSITION_Y;
    window->buttonUndo = IMG_Load("Images/Bouton-annuler-normal.jpg");
    SDL_BlitSurface(window->buttonUndo, NULL, window->screen, &position);
    window->buttonUndo->clip_rect.x = position.x;
    window->buttonUndo->clip_rect.y = position.y;

    position.y = BUTTON_QUIT_MENU_3_POSITION_Y;
    window->buttonQuit = IMG_Load("Images/Bouton-quiter-normal.jpg");
    SDL_BlitSurface(window->buttonQuit, NULL, window->screen, &position);
    window->buttonQuit->clip_rect.x = position.x;
    window->buttonQuit->clip_rect.y = position.y;

    window->buttonHxH = NULL;
    window->buttonHxIA1 = NULL;
    window->buttonHxIA2 = NULL;
}

void refreshWindow (Window window) {
	SDL_Flip(window->screen);
}

SDL_Surface* setImageForButton (Window window, SDL_Surface * button, char* imageHoverPath) {
    SDL_Rect pos;
    pos.x = button->clip_rect.x;
    pos.y = button->clip_rect.y;
	button = IMG_Load(imageHoverPath);
	button->clip_rect.x = pos.x;
    button->clip_rect.y = pos.y;
    SDL_BlitSurface(button, NULL, window->screen, &pos);
	return button;
}

int isPosOnbutton (SDL_Surface* button, int x, int y) {
	int res = 0;
	SDL_Rect pos;
	if (button != NULL) {
		pos = button->clip_rect;
	}
	if (button != NULL && 
		x >= pos.x && x <= (pos.x + pos.w) &&
		y >= pos.y && y <= (pos.y + pos.h)) {
		res = 1;
	}
	return res;
}

/*SDL_Surface* isPositionOnButton (Window window, int x, int y) {
	SDL_Surface* res = NULL;
	

	return res;
}*/



