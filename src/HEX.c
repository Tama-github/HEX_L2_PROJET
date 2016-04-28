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
    int i, j;
    int confirmQ = 0;
    int confirmM = 0;
    int confirmS = 0;
    int confirmL = 0;
    int err;

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
    
    /*initialisation of the font*/
    police = TTF_OpenFont("police/arial.ttf", 14);

    /*
     * Initialisation of the window
     */
    window = createWindow ();
    setInitMenu(window);
    refreshWindow(window);

    /* Manage of events */
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
                    /* Manage on menu's clic */
                    if (isPosOnbutton(window->menu, event.button.x, event.button.y)) {
                        if (isPosOnbutton(window->buttonMenu, event.button.x, event.button.y)) {
                            if (game->gameStatus == GAME_IN_PROGRESS && confirmM == 0) {
                                confirmM = 1;
                                logSomething(window->textInLog, "Cliquer une seconde fois sur le bouton menu si vous voulez vraiment retourner sur le menu.\0");
                            } else if (game->gameStatus == GAME_IN_PROGRESS && confirmM == 1) {
                                setInitMenu(window);
                                reinitializeGame (game);
                            } else
                                setInitMenu(window);
                        } else if (isPosOnbutton(window->buttonPlay, event.button.x, event.button.y)) {
                            setGameChoiceMenu(window);
                        } else if (isPosOnbutton(window->buttonLoad, event.button.x, event.button.y)) {
                            if ((confirmL && game->gameStatus == GAME_IN_PROGRESS) || game->gameStatus != GAME_IN_PROGRESS) {
                                err = loadGame(game);
                                if (err == 1) {
                                    logSomething(window->textInLog, "La partie a bien ete charge.\0");
                                    setUpGameHxH(game);
                                    setInGameMenu(window);
                                } else if (err == 0) {
                                    logSomething(window->textInLog, "Aucune sauvegarde disponible.");
                                }
                            } else if (game->gameStatus == GAME_IN_PROGRESS){
                                confirmL = 1;
                                logSomething(window->textInLog, "Si vous chargez une partie en jeu, votre progression sera perdu.\0");
                                logSomething(window->textInLog, "Cliquez une seconde fois sur charger pour valider votre choix.\0");
                            } 
                        } else if (isPosOnbutton(window->buttonSave, event.button.x, event.button.y)) {
                            if (confirmS) {
                                saveGame(game);
                                logSomething(window->textInLog, "La partie a ete sauvegarde.\0");
                            } else {
                                confirmS = 1;
                                logSomething(window->textInLog, "Si vous sauvegarder, vous ecraserez la sauvegarde existante.\0");
                                logSomething(window->textInLog, "Cliquez une seconde fois sur le bouton sauvegarder pour confirmer la sauvegarde.\0");
                            }
                        } else if (isPosOnbutton(window->buttonUndo, event.button.x, event.button.y)) {
                            if (undoAction(game))
                                logSomething(window->textInLog, "Les deux derniers coups ont ete annule.\0");
                            else
                                logSomething(window->textInLog, "Vous ne pouvez pas annuler deux fois consecutivement. Ou en debut de partie\0");
                        } else if (isPosOnbutton(window->buttonHistoric, event.button.x, event.button.y)) {
                            /* This button is depreciat */
                        } else if (isPosOnbutton(window->buttonQuit, event.button.x, event.button.y)) {
                            if (confirmQ) 
                                stop = 1;
                            else {
                                confirmQ = 1;
                                logSomething(window->textInLog, "Cliquer une seconde fois sur le bouton quitter si vous voulez vraiment quitter le jeu.\0");
                            }
                        } else if (isPosOnbutton(window->buttonHxH, event.button.x, event.button.y)) {
                            setUpGameHxH(game);
                            setInGameMenu(window);
                            logBeginGame (window->textInLog);
                        } else if (isPosOnbutton(window->buttonHxIA2, event.button.x, event.button.y)) {
                            //event
                        } else if (isPosOnbutton(window->buttonHxIA1, event.button.x, event.button.y)) {
                            //event
                        }
                    /* Manage on board's clic */
                    } else if (isPosOnbutton(window->board, event.button.x, event.button.y) && game->gameStatus == GAME_IN_PROGRESS) {
                        if ((hex = findHexagoneOnBoard(game->board, event.button.x, event.button.y, &i, &j)) != NULL && hex->idPlayer == 0) {
                            displayToken(hex, game->turnOf, window);
                            playAnHexagone(hex, game);
                            logPlayerTurn(hex, game, window->textInLog, i, j);
                            storeAPlay(game, hex);
                        }
                    }

                    /* Manage on critical actions */
                    if (!isPosOnbutton(window->buttonQuit, event.button.x, event.button.y)) {
                        confirmQ = 0;
                    } 
                    if (!isPosOnbutton(window->buttonMenu, event.button.x, event.button.y)) {
                        confirmM = 0;
                    }
                    if (!isPosOnbutton(window->buttonSave, event.button.x, event.button.y)) {
                        confirmS = 0;
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
                    if ((hex = findHexagoneOnBoard(game->board, event.button.x, event.button.y, &i, &j)) != NULL) {
                        displayToken(hex, game->turnOf, window);
                    }
                }
                break;
        }
        displayBoard(game->board, window, game);
        refreshWindow(window);
    }
    //deleteGame(game);
    closeWindow(window);
	return 0;
}