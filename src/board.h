#ifndef _BOARD_H_
#define _BOARD_H_

#include "hexagone.h"
#include "Interface.h"
#include "constantes.h"

/*La structure représentant le plateau de jeu*/
struct s_Board {
	Hexagone board [BOARD_LENGTH][BOARD_LENGTH];
};

typedef struct s_Board* Board;


/****************************************************
Créé et retourne un Plateau
@sortie : Le plateau créé

******************************************************/
Board createBoard ();

/****************************************************
Supprime un Plateau créé avec "createBoard()"
@entré b : Le plateau à supprimer

******************************************************/
void deleteBoard (Board b);

/****************************************************
Trouve l'hexagone correspondant au coordonné donné en entré
@entré board : le plateau sur lequel on veux l'hexagone
@entré x : Les coordonnées en pixel sur l'axe des abscisses
@entré y : Les coordonnées en pixel sur l'axe des ordonnées
@sortie i : contiendra l'indice de première redirection de l'endroit où est contenue l'hexagone trouvé dans le plateau 
			(le plateau est un tableau a deux dimenssion i représentera la première dimenssion)
@sortie j : contiendra l'indice de seconde redirection de l'endroit où est contenue l'hexagone trouvé dans le plateau 
			(le plateau est un tableau a deux dimenssion j représentera la seconde dimenssion)
@sortie : L'hexagone trouvé ou null si l'hexagone n'a pas été trouvé.

******************************************************/
Hexagone findHexagoneOnBoard (Board board, int x, int y, int *i, int *j);

/****************************************************
Réinitialise le plateau. (Remet chaque hexagone au statut "UNPLAYED")
@entré b : Le plateau à réinitialiser

******************************************************/
void reinitializeBoard (Board b);

#endif
