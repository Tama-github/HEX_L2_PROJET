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

int main (int argc, char * argv[]) {

	SDL_Surface * screen = NULL;
	SDL_Surface * menu = NULL;

	/* tous les boutons */
	/*SDL_Surface * button-menu = NULL;
	SDL_Surface * button-start = NULL;
	SDL_Surface * button-load = NULL;
	SDL_Surface * button-save = NULL;
	SDL_Surface * button-undo = NULL;
	SDL_Surface * button-historic = NULL;
	SDL_Surface * button-quit = NULL;
	SDL_Surface * button-hxh = NULL;
	SDL_Surface * button-hxia1 = NULL;
	SDL_Surface * button-hxia2 = NULL;*/

	SDL_Rect position;
    position.x = 0;
    position.y = 0;

	int stop = 0;
	SDL_Event event;
	if( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
        fprintf(stderr,"Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    /* Clean up on exit */
    atexit(SDL_Quit);
    
    /*
     * Initialisation de la fenêtre
     */
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE);
    
    if ( screen == NULL ) {
        fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n", SDL_GetError());
        exit(1);
    }

    /* couleurs */
    Uint32 BACKGROUND_COLOR = SDL_MapRGB(screen->format, 200, 200, 200);
    Uint32 MENU_COLOR = SDL_MapRGB(screen->format, 225, 225, 225);
    //Uint32 BUTTON_COLOR = SDL_MapRGB(screen->format, 200, 200, 255);

    SDL_FillRect(screen, NULL, BACKGROUND_COLOR);
    SDL_WM_SetCaption("HEX", NULL);

    

    /* Initialisation des objets de la fenêtre */
    //menu_init(menu, );
    menu = SDL_CreateRGBSurface(SDL_SWSURFACE, MENU_WIDTH, MENU_HEIGHT, SCREEN_BPP, 0, 0, 0, 0);
    SDL_FillRect(menu, NULL, MENU_COLOR);
    SDL_BlitSurface(menu, NULL, screen, &position);

    SDL_Flip(screen);
	SDL_FreeSurface(menu);

    /* Gestion des evenements */
    SDL_EnableKeyRepeat(10,10);
    while(!stop){
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                stop = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    printf("CLICK : x:%d  y:%d\n", event.button.x, event.button.y);
                }
                break;
            case SDL_MOUSEMOTION:
                printf("MOVE : x:%d  y:%d\n", event.motion.x, event.motion.y);
                break;
        }
    }

    SDL_Quit();
	return 0;
}