#include "ensemble.h"

typedef struct et_Set{
  Hexagone *group;
  int size;
}celSet;


Set createSet(){
  Set e=(Set)malloc(sizeof(celSet));
  e->group=(Hexagone*)malloc(sizeof(Hexagone)*0);
  return(e);
}

Set addHexagone(Set e, Hexagone h){
  e->group=realloc(e->group,sizeof(Hexagone)*(e->size+1));
  int i;
  for(i=0;i<e->size;i++){ 
    if(e->group[i]==h)
      break;
  }
  if(i==e->size){
    e->group[e->size]=h;
    e->size++;
  }
  return(e);
}

void deleteSet(Set s){
  int i;
  for(i=0;i<s->size;i++){
    free(s->group[i]);
  }
  free(s);
}

Set unionSet(Set a, Set b){
  Set f=createSet();
  int i;
  for (i=0;i<a->size;i++){
    f=addHexagone(f,a->group[i]);
  }
  for (i=0;i<b->size;i++){
    f=addHexagone(f,b->group[i]);
  }
  printf("%d\n",f->size);
  deleteSet(a);
  deleteSet(b);
  return(f);
}


void showSet(Set s){
  int i;
  for(i=0;i<s->size;i++){
    printf("Hexagonenumero=%d, x=%d,y=%d \n",i,s->group[i]->x,s->group[i]->y);
    
  }
}

