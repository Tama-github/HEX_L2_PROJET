#ifndef ENSEMBLE
#define ENSEMBLE
#include "hexagone.h"
#include <stdlib.h>


typedef struct et_Set* Set;

Set createSet();

Set addHexagone(Set e, Hexagone h);

void deleteSet(Set s);

Set unionSet(Set a, Set b);

void showSet(Set s);

#endif