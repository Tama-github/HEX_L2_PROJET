#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>

typedef struct s_Queue* Queue;

Queue createQueue ();
void deleteQueue (Queue f);
int emptyQ (Queue f);
void enfiler (Queue f, char* elem);
char* defiler (Queue f);
char ** getConcatChar (Queue f);
int getSize (Queue f);
