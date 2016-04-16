#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>


#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "Interface.h"
#include "game.h"
#include "board.h"
#include "hexagone.h"

int main (int argc, char * argv[]) {
    TTF_Font *police = NULL;
	Window window; 
    Game game;
    Hexagone hex;
    game = createGame();

	int stop = 0;
	SDL_Event event;
	if( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
        fprintf(stderr,"Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    if (TTF_Init() == -1) {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(2);
    }

    /* Clean up on exit */
    atexit(SDL_Quit);
    
    /*initialisation de la police*/
    police = TTF_OpenFont("police/arial.ttf", 14);

    /*
     * Initialisation de la fenêtre
     */
    window = createWindow ();
    setInitMenu(window);
    refreshWindow(window);

    /* Gestion des evenements */
    SDL_EnableKeyRepeat(10,10);
    while(!stop){
        if (window->menuType == INIT_MENU) {
            setInitMenu(window);
        } else if (window->menuType == GAME_CHOICE_MENU) {
            setGameChoiceMenu(window);
        } else if (window->menuType == IN_GAME_MENU) {
            setInGameMenu(window);
        }
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                stop = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    printf("CLICK : x:%d  y:%d\n", event.button.x, event.button.y);
                    /* Gestion des clic menu */
                    if (isPosOnbutton(window->menu, event.button.x, event.button.y)) {
                        if (isPosOnbutton(window->buttonMenu, event.button.x, event.button.y)) {
                            setInitMenu(window);
                        } else if (isPosOnbutton(window->buttonPlay, event.button.x, event.button.y)) {
                            setGameChoiceMenu(window);
                        } else if (isPosOnbutton(window->buttonLoad, event.button.x, event.button.y)) {
                            //event
                        } else if (isPosOnbutton(window->buttonSave, event.button.x, event.button.y)) {
                            //event
                        } else if (isPosOnbutton(window->buttonUndo, event.button.x, event.button.y)) {
                            //event
                        } else if (isPosOnbutton(window->buttonHistoric, event.button.x, event.button.y)) {
                            //event
                        } else if (isPosOnbutton(window->buttonQuit, event.button.x, event.button.y)) {
                            stop = 1;
                        } else if (isPosOnbutton(window->buttonHxH, event.button.x, event.button.y)) {
                            setUpGameHxH(game);
                            setInGameMenu(window);
                            logBeginGame (window->textInLog);
                        } else if (isPosOnbutton(window->buttonHxIA2, event.button.x, event.button.y)) {
                            //event
                        } else if (isPosOnbutton(window->buttonHxIA1, event.button.x, event.button.y)) {
                            //event
                        }
                    /* Gestion des clic plateau */
                    } else if (isPosOnbutton(window->board, event.button.x, event.button.y) && game->gameStatus == GAME_IN_PROGRESS) {
                        if ((hex = findHexagoneOnBoard(game->board, event.button.x, event.button.y)) != NULL && hex->idPlayer == 0) {
                            displayToken(hex, game->turnOf, window);
                            playAnHexagone(hex, game);
                            logPlayerTurn(hex, game, window->textInLog);
                        }
                    }
                    displayLog (window, police, window->textInLog);
                }
                break;
            case SDL_MOUSEMOTION:
                if (isPosOnbutton(window->menu, event.button.x, event.button.y)) {
                    if (isPosOnbutton(window->buttonMenu, event.button.x, event.button.y)) {
                        window->buttonMenu = setImageForButton(window, window->buttonMenu, "Images/Bouton-menu-hover.jpg");
                    } else if (isPosOnbutton(window->buttonPlay, event.button.x, event.button.y)) {
                        window->buttonPlay = setImageForButton(window, window->buttonPlay, "Images/Bouton-jouer-hover.jpg");
                    } else if (isPosOnbutton(window->buttonLoad, event.button.x, event.button.y)) {
                        window->buttonLoad = setImageForButton(window, window->buttonLoad, "Images/Bouton-charger-hover.jpg");
                    } else if (isPosOnbutton(window->buttonSave, event.button.x, event.button.y)) {
                        window->buttonSave = setImageForButton(window, window->buttonSave, "Images/Bouton-sauver-hover.jpg");
                    } else if (isPosOnbutton(window->buttonUndo, event.button.x, event.button.y)) {
                        window->buttonUndo = setImageForButton(window, window->buttonUndo, "Images/Bouton-annuler-hover.jpg");
                    } else if (isPosOnbutton(window->buttonHistoric, event.button.x, event.button.y)) {
                        window->buttonHistoric = setImageForButton(window, window->buttonHistoric, "Images/Bouton-historique-hover.jpg");
                    } else if (isPosOnbutton(window->buttonQuit, event.button.x, event.button.y)) {
                        window->buttonQuit = setImageForButton(window, window->buttonQuit, "Images/Bouton-quiter-hover.jpg");
                    } else if (isPosOnbutton(window->buttonHxH, event.button.x, event.button.y)) {
                        window->buttonHxH = setImageForButton(window, window->buttonHxH, "Images/Bouton-hxh-hover.jpg");
                    } else if (isPosOnbutton(window->buttonHxIA2, event.button.x, event.button.y)) {
                        window->buttonHxIA2 = setImageForButton(window, window->buttonHxIA2, "Images/Bouton-hxia2-hover.jpg");
                    } else if (isPosOnbutton(window->buttonHxIA1, event.button.x, event.button.y)) {
                        window->buttonHxIA1 = setImageForButton(window, window->buttonHxIA1, "Images/Bouton-hxia1-hover.jpg");
                    }
                } else if (isPosOnbutton(window->board, event.button.x, event.button.y) && game->gameStatus == GAME_IN_PROGRESS) {
                    if ((hex = findHexagoneOnBoard(game->board, event.button.x, event.button.y)) != NULL) {
                        displayToken(hex, game->turnOf, window);
                    }
                }
                break;
        }
        
        displayBoard(game->board, window, game);
        refreshWindow(window);
    }

    closeWindow(window);
	return 0;
}