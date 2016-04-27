#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>

typedef struct s_Queue* Queue;

/****************************************************
Créé une file..
@sortie : La file créé.

******************************************************/
Queue createQueue ();

/****************************************************
Detruit une file créé avec createQueue.
@entré f : La file a détruire.

******************************************************/
void deleteQueue (Queue f);

/****************************************************
Dit si la file est vide.
@entré f : la file a verifier.
@sortie : 1 si la file est vide, 0 si non.

******************************************************/
int emptyQ (Queue f);

/****************************************************
Enfile un element dans la file passé en paramette.
@entré f : La file.
@entré elem : L'element à enfiler.

******************************************************/
void enfiler (Queue f, char* elem);

/****************************************************
Defile un element de la file passé en paramettre et le retourne.
@entré f : La file.
@sortie : L'element défilé.

******************************************************/
char* defiler (Queue f);

/****************************************************
Retourne dans un tableau tout le contenu de la file et le retourne.
@entré f : la file.
@sortie : Le tableau d'élements.

******************************************************/
char ** getConcatChar (Queue f);

/****************************************************
Donne la taille de la file.
@entré f : la file.
@sortie : la taille de la file.

******************************************************/
int getSize (Queue f);
