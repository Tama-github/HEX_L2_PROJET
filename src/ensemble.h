#ifndef ENSEMBLE
#define ENSEMBLE
#include "hexagone.h"
#include <stdlib.h>


typedef struct et_ensemble* ensemble;

ensemble initEnsemble();

ensemble ajouterHexagone(ensemble e, hexagone h);

ensemble unionEnsemble(ensemble a, ensemble b);

#endif