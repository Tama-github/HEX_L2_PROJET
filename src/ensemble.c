#include "ensemble.h"

typedef struct et_ensemble{
  hexagone *group;
  int taille;
}celensemble;


ensemble initEnsemble(){
  ensemble e=(ensemble)malloc(sizeof(celensemble));
  e->taille=0;
  e->group=(hexagone*)malloc(sizeof(hexagone)*0);
  return(e);
}

ensemble ajouterHexagone(ensemble e, hexagone h){
  e->group=realloc(e->group,sizeof(hexagone)*(e->taille+1));
  int i;
  for(i=0;i<e->taille;i++){ 
    if(e->group[i]==h)
      break;
  }
  if(i==e->taille){
    e->group[e->taille]=h;
    e->taille++;
  }
  return(e);
}

ensemble unionEnsemble(ensemble a, ensemble b){
  ensemble f=(ensemble)malloc(sizeof(celensemble));
  f->group=(hexagone*)malloc(sizeof(hexagone)*(a->taille+b->taille));
  f=a;
  int i;
  for (i=0;i<b->taille;i++){
    f=ajouterHexagone(f,b->group[i]);
  }
  return(f);
}