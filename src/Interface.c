#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>

#include "Interface.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

ImgHexagones createImgHexagone () {
    ImgHexagones res = (ImgHexagones)malloc(sizeof(struct s_ImgHexagones));
    res->emptyHex = IMG_Load("Images/hex-vide.png");
    res->redHex = IMG_Load("Images/button-red22.png");
    res->blueHex = IMG_Load("Images/button-blue22.png");
    return res;
}

void deleteImgHexagone (ImgHexagones i) {
    SDL_FreeSurface(i->emptyHex);
    SDL_FreeSurface(i->redHex);
    SDL_FreeSurface(i->blueHex);
    free(i);
}

Window createWindow () {
	Window res = (Window)malloc(sizeof(struct s_Window));
	res->screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE);
    res->hex = createImgHexagone();
    res->menuType = UNDIFINE_MENU;
    res->textInLog = createQueue();

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
    Uint32 LOGS_COLOR = SDL_MapRGB(res->screen->format, 20,22,22);

    /* creations des objets graphique */
    SDL_FillRect(res->screen, NULL, BACKGROUND_COLOR);
    SDL_WM_SetCaption("HEX", NULL);

    res->menu = SDL_CreateRGBSurface(SDL_SWSURFACE, MENU_WIDTH, MENU_HEIGHT, SCREEN_BPP, 0, 0, 0, 0);
    SDL_FillRect(res->menu, NULL, MENU_COLOR);
    SDL_BlitSurface(res->menu, NULL, res->screen, &position);
    res->menu->clip_rect.x = 0;
    res->menu->clip_rect.y = 0;

    position.x = LOGS_POSITION_X;
    position.y = LOGS_POSITION_Y;
    res->logs = SDL_CreateRGBSurface(SDL_SWSURFACE, LOGS_WIDTH, LOGS_HEIGHT, SCREEN_BPP, 0, 0, 0, 0);
    SDL_FillRect(res->logs, NULL, LOGS_COLOR);
    SDL_BlitSurface(res->logs, NULL, res->screen, &position);
    res->logs->clip_rect.x = position.x;
    res->logs->clip_rect.y = position.y;

    res->text = (SDL_Surface**)malloc(sizeof(SDL_Surface*)*QUEUE_MAX_SIZE);
    int i;
    for (i = 0; i < QUEUE_MAX_SIZE; i++) {
        res->text[i] = NULL;
    }

    position.x = BOARD_POSITION_X;
    position.y = BOARD_POSITION_Y;
    res->board = IMG_Load("Images/hex.png");
    SDL_BlitSurface(res->board, NULL, res->screen, &position);
    res->board->clip_rect.x = position.x;
    res->board->clip_rect.y = position.y;

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
    deleteImgHexagone(window->hex);
    SDL_FreeSurface(window->menu);
    SDL_FreeSurface(window->board);
    SDL_FreeSurface(window->logs);
    deleteQueue(window->textInLog);
    int i;
    for (i = 0; i < QUEUE_MAX_SIZE; i++) 
        if (window->text[i] != NULL) SDL_FreeSurface(window->text[i]);
    free(window->text);
	SDL_Quit();
	free(window);
}

void setInitMenu (Window window) {
	freeButtons(window);
	window->menuType = INIT_MENU;
	SDL_Rect position;
	position.x = BUTTON_POSITION_X;

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

    window->buttonMenu = NULL;
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

    position.y = BUTTON_QUIT_MENU_2_POSITION_Y;
    window->buttonQuit = IMG_Load("Images/Bouton-quiter-normal.jpg");
    SDL_BlitSurface(window->buttonQuit, NULL, window->screen, &position);
    window->buttonQuit->clip_rect.x = position.x;
    window->buttonQuit->clip_rect.y = position.y;

    window->buttonUndo = NULL;
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

    window->buttonPlay = NULL;
    window->buttonHistoric = NULL;
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

void displayToken (Hexagone hex, int idPlayer, Window window) {
    SDL_Rect position;
    position.x = hex->x + TOKEN_RELATIVE_HEXAGONE_POSITION_X;
    position.y = hex->y + TOKEN_RELATIVE_HEXAGONE_POSITION_Y;
    if (idPlayer == ID_PLAYER_1) {
        SDL_BlitSurface(window->hex->blueHex, NULL, window->screen, &position);
    } else if (idPlayer == ID_PLAYER_2) {
        SDL_BlitSurface(window->hex->redHex, NULL, window->screen, &position);
    } else if (idPlayer == UNPLAYED) {
        position.x = hex->x;
        position.y = hex->y;
        SDL_BlitSurface(window->hex->emptyHex, NULL, window->screen, &position);
    }
}



void displayLog (Window window, TTF_Font *police, Queue qu) {
    if (emptyQ(qu)) return;

    char** txt = getConcatChar(qu);
    SDL_Color color = {255,255,255};
    SDL_Rect pos;
    pos.x = LOGS_POSITION_X;
    pos.y = LOGS_POSITION_Y;
    SDL_BlitSurface(window->logs, NULL, window->screen, &pos);
    int i;
    for (i = 0; i < getSize(qu) && i < QUEUE_MAX_SIZE; i++) {
        if (window->text[i] != NULL) SDL_FreeSurface(window->text[i]);
        window->text[i] = TTF_RenderText_Blended(police, txt[i], color);
        assert(window->text[i] != NULL);
        window->text[i]->clip_rect.x = pos.x;
        window->text[i]->clip_rect.x = pos.y;
        SDL_BlitSurface(window->text[i], NULL, window->screen, &pos);
        pos.y = pos.y+17;
    }
}

void logBeginGame (Queue qu) {
    char* txt = (char*)malloc(sizeof(char)*50);
    assert(txt != NULL);
    txt[0] = '\0';
    strcat(txt, "Debut de la partie, le joueur bleu commence.");
    txt[44] = '\0';
    enfiler(qu, txt);
}

void logPlayerTurn(Hexagone hex, Game game, Queue qu, int i, int j) {
    char * txt = (char*)malloc(sizeof(char)*150);
    txt[0]='\0';
    if (game->turnOf == ID_PLAYER_1) {
        sprintf(txt, "Le Joueur rouge a jouer en (%d, %d) .C'est au joueur bleu de jouer.", i, j);
    } else if (game->turnOf == ID_PLAYER_2) {
        sprintf(txt, "Le Joueur bleu a jouer en (%d, %d) .C'est au joueur rouge de jouer.", i, j);
    }
    enfiler(qu, txt);
    if (getSize(qu) > QUEUE_MAX_SIZE) {
        free(defiler(qu));
    }
}

void logSomething (Queue qu, char* c) {
    char * txt = (char*)malloc(sizeof(char)*150);
    txt[0] = '\0';
    if (strlen(c) < 150) {
        strcat(txt, c);
        enfiler(qu, txt);
    }
    while (getSize(qu) > QUEUE_MAX_SIZE) {
        free(defiler(qu));
    }
}

void displayBoard (Game game, Window window) {
    int i, j;
    SDL_Rect position;
    position.x = BOARD_POSITION_X;
    position.y = BOARD_POSITION_Y;
    SDL_BlitSurface(window->board, NULL, window->screen, &position);

    for (i = 0; i < BOARD_LENGTH; i++) {
        for (j = 0; j < BOARD_LENGTH; j++) {
            if (game->board->board[i][j]->hold == 1 && game->board->board[i][j]->idPlayer == UNPLAYED) {
                displayToken(game->board->board[i][j], game->turnOf, window);
            } else if (game->board->board[i][j]->idPlayer == ID_PLAYER_1) {
                displayToken(game->board->board[i][j], ID_PLAYER_1, window);
            } else if (game->board->board[i][j]->idPlayer == ID_PLAYER_2) {
                displayToken(game->board->board[i][j], ID_PLAYER_2, window);
            } else {
                displayToken(game->board->board[i][j], UNPLAYED, window);
            }
        }
    }
}

/*SDL_Surface* isPositionOnButton (Window window, int x, int y) {
	SDL_Surface* res = NULL;
	

	return res;
}*/



