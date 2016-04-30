#include "set.h"

typedef struct et_Cell {
  CellSet * next;
  Hexagone hex;
} s_Cell;

CellSet * createCellSet (Hexagone hex) {
  CellSet * res = (CellSet*)malloc(sizeof(CellSet));
  res->next = NULL;
  res->hex = hex;
  return res;
}

void deleteCellSet (CellSet* c) {
  free(c);
}

typedef struct et_Set{
  CellSet *first;
  int idPlayer;
  int size;
} s_Set;

Set createSet(int idPlayer){
  Set e = (Set)malloc(sizeof(struct et_Set));
  e->idPlayer = idPlayer;
  e->size = 0;
  e->first = NULL;
  return(e);
}

void deleteSet(Set s){
  CellSet* tmp = NULL;
  CellSet* c = s->first;
  while (c != NULL) {
    tmp = c;
    c = c->next;
    deleteCellSet(tmp);
  }
  free(s);
}

Set addHexagone(Set e, Hexagone h){
  CellSet * c = e->first;
  CellSet * add;
  while (c != NULL) {
    if (c->hex == h) 
      break;
    c = c->next;
  }
  if(c == NULL){
    add = createCellSet(h);
    add->next = e->first;
    e->first = add;
  }
  return(e);
}

int getIdPlayer (Set set) {
  return (set->idPlayer);
}

Set unionSet(Set a, Set b){
  Set f = createSet(a->idPlayer);
  CellSet* c = a->first;
  while (c != NULL) {
    f = addHexagone(f, c->hex);
    c = c->next;
  }

  c = b->first;
  while (c != NULL) {
    f = addHexagone(f, c->hex);
    c = c->next;
  }
  return(f);
}

int isHexAdjToSet (Set set, Hexagone hex) {
  CellSet* c = set->first;
  while (c != NULL) {
    if (isAdjacentHexagone(c->hex, hex))
      return 1;
    c = c->next;
  }
  return 0;
}

void showSet(Set s){
  CellSet* c = s->first;
  while (c != NULL) {
    printf("x=%d,y=%d \n", c->hex->x, c->hex->y);
    c = c->next;
  }
}

int victorySet (Set set) {
  CellSet* c = set->first;
  int a1 = 0, a2 = 0;
  while (c != NULL && (!a1 || !a2)) {
    if (!a1)
      a1 = isHexOnSide1(c->hex);
    if (!a2)
      a2 = isHexOnSide2(c->hex);
    c = c->next;
  }
  return (a1 && a2);
}

void displaySetInFile (Set set, FILE* f, Board board) {
  CellSet* c = set->first;
  int i, j;
  while (c != NULL) {
    findHexagoneOnBoard(board, c->hex->x, c->hex->y, &i, &j);
    fprintf(f, "%d %d %d\n",set->idPlayer, i, j);
    c = c->next;
  }
  fprintf(f, "-1 -1 -1\n");
}

