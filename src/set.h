#ifndef _SET_H_
#define _SET_H_
#include <stdlib.h>

#include "hexagone.h"
#include "board.h"

typedef struct s_Board* Board;
typedef struct et_Cell CellSet;
typedef struct et_Set* Set;

/****************************************************
Créé et retourne un ensemble
@entré idPlayer : L'id du joueur auquel l'ensemble correspondra
@sortie : L'ensemble créé.

******************************************************/
Set createSet(int idPlayer);

/****************************************************
Ajoute un élément à l'ensemble (en évitant les doublons)
@entré e : l'ensemble à remplir.
@entré h : l'hexagone à mettre dans l'ensemble.
@sortie : L'ensemble modifier

******************************************************/
Set addHexagone(Set e, Hexagone h);

/****************************************************
Supprime un ensemble créé avec createSet
@entré f : l'ensemble a suppromer.

******************************************************/
void deleteSet(Set s);

/****************************************************
Fait l'opération d'union entre deux ensembles.
@entré a : Un ensemble.
@entré b : un autre ensemble.
@sortie : Un nouvelle ensemble contenant l'union des deux ensembles passé en paramettre

******************************************************/
Set unionSet(Set a, Set b);

/****************************************************
Affiche sur la sortie standart une réprésentation de l'ensemble
@entré s : l'ensemble a afficher.

******************************************************/
void showSet(Set s);

/****************************************************
Verifier si un hexagone est adjascent avec un des hexagone contenu dans l'ensemble passé en paramettre.
@entré s : L'ensemble a vériffier
@entré hex : L'hexagone a vérifier
@sortie : 1 si l'hexagone est adjascent à un hexagone conenue dans l'ensemble, 0 si non.

******************************************************/
int isHexAdjToSet (Set set, Hexagone hex);

/****************************************************
Retourne l'id du joueur auquel appartient l'ensemble
@entré set : l'ensemble
@sortie : L'id du joueur.

******************************************************/
int getIdPlayer (Set set);

/****************************************************
Vérifie si l'ensemble est une ensemble qui contient une ligne qui traverse le plateau.
@entré set : L'ensemble à vérifier.
@sortie : 1 si l'ensemble est victorieu, 0 si non.

******************************************************/
int victorySet (Set set);

/****************************************************
Ecris dans le fichier dont l'identificatuer est passé en parametre l'ensemble.
@entré set : l'ensemble à écrire dans le fichier.
@entré f : l'identificateur du fichier où on veux écrire.
@entré boerd : le plateau du jeu auquel l'ensemble appartient

******************************************************/
void displaySetInFile (Set set, FILE* f, Board board);

#endif