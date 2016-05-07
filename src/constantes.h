#ifndef _CONSTANTES_H_
#define _CONSTANTES_H_

/* Hexagone */
#define HEXAGONE_LENGTH 30
#define HEXAGONE_HEIGHT 29

/* Game status*/
#define GAME_UNSET 0
#define GAME_IN_PROGRESS 1
#define GAME_END 2

/* Player status */
#define UNPLAYED 0
#define ID_PLAYER_1 1
#define ID_PLAYER_2 2

/* Interface */
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

/* Board */
#define BOARD_LENGTH 11

/* Infos relatives au plateau */
#define FIRST_HEXAGONE_POSITION_X (BOARD_POSITION_X + 19)
#define FIRST_HEXAGONE_POSITION_Y (BOARD_POSITION_Y + 19)
#define LAST_HEXAGONE_POSITION_Y 409 
#define LAST_HEXAGONE_POSITION_X 619
#define BOARD_EACH_LINE_SHIFT 15
#define BOARD_EACH_COLUMN_SHIFT 25



#endif