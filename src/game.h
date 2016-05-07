#ifndef _GAME_H_
#define _GAME_H_

#include "constantes.h"

#include "board.h"
#include "set.h"

typedef struct s_Board* Board;
typedef struct et_CellVictory CellVictory;
typedef struct et_Victory* Victory;


/* Structure représentant un jeu */
struct s_Game {
	int gameStatus; /* Le statu du jeu. Voir les constantes pour le jeu */
	int turnOf; /* Id du joueur qui dois jouer */
	Hexagone twoLastPlay [2]; /* Tableau stockant les deux dernier coups jouer */
	Board board; /* Le plateau de jeu */
	Victory victory; /* Liste contenant des Ensemble eux mêmes étant des listes d'hexagonnes on ce sert de cet attribut pour déterminer la victoire. */
};

typedef struct s_Game* Game;

/****************************************************
Créé et retourne un Jeu
@sortie : Le Jeu créé

******************************************************/
Game createGame ();

/****************************************************
Supprime un Jeu créé avec "createGame()"
@entré game : Le Jeu à supprimer

******************************************************/
void deleteGame (Game game);

/****************************************************
Initialise le jeu pour une partie en mode Humain contre Humain
@entré game : Le Jeu à initialiser

******************************************************/
void setUpGameHxH (Game game);

/****************************************************
Passe le tour de jeu au joueur suivant
@entré game : Le Jeu à modifier

******************************************************/
void nextTurn (Game game);

/****************************************************
Joue l'hexagone passer en paramettre.
@entré hex : L'hexagone à jouer
@entré game : Le Jeu à modifier

******************************************************/
void playAnHexagone (Hexagone hex, Game game);

/****************************************************
Stocker une action pour pourvoir ce servir de undo par la suite.
@entré hex : L'hexagone à stocker
@entré game : Le Jeu à modifier

******************************************************/
void storeAPlay (Game game, Hexagone hex);

/****************************************************
Annuler les deux dernier coup jouer.
@entré game : Le Jeu à modifier
@sortie : 1 si les deux coup ont pu être annuler, 0 si non.

******************************************************/
int undoAction (Game game);

/****************************************************
Initialise le jeu à sa fin
@entré game : Le Jeu à modifier

******************************************************/
void endGame (Game game);

/****************************************************
Sauvegarde le jeu.
@entré game : Le Jeu à sauvegarder

******************************************************/
void saveGame (Game game);

/****************************************************
Charge le derneir jeu sauvegarder.
@entré game : Le Jeu où vas être stocker le jeu charger.
@sortie : si il y a eu un problème lors du chargement retourne 0. Retourne 1 si non.

******************************************************/
int loadGame (Game game);

/****************************************************
Réinitialise le jeu passer en paramètre.
@entré game : Le Jeu à réinitialiser.

******************************************************/
void reinitializeGame (Game game);

/****************************************************
Vérifie si il un joueur à gagner
@entré game : Le Jeu à verifier
@sortie : 1 si un joueur à gagner, 0 si non.

******************************************************/
int haveVictorySet (Game game);

#endif