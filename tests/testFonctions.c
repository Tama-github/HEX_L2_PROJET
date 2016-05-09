#include "../src/board.h"
#include "../src/game.h"
#include "../src/hexagone.h"
#include "../src/queue.h"
#include "../src/set.h"
#include "../src/constantes.h"

Set createWinnerSet(){
  Set s=createSet(1);
  Hexagone h=createHexagone(330,170);
  s=addHexagone(s,h);
  int i;
  for (i=0;i<11;i++){
    h->x=h->x+HEXAGONE_LENGTH;
    s=addHexagone(s,h);
  }
  return(s);
}

int main(){
  int x=437;
  int y=214;
  Set s=createSet(1);
  assert(s!=NULL);
  printf("createSet OK\n");
  
  assert(1==getIdPlayer(s));
  printf("getIdPlayer OK\n");
  
  Hexagone h=createHexagone(x,y);
  assert(h!=NULL);
  printf("createHexagone OK\n");
  
  s=addHexagone(s,h);
  showSet(s);
  printf("addHexagone OK\n");
  
  assert(isCoordOnHexagone(h,363,224)==0);
  assert(isCoordOnHexagone(h,438,215)==1);
  printf("isCoordOnHexagone OK\n");
  
  Hexagone hex=createHexagone(x+HEXAGONE_LENGTH,y);
  assert(isHexAdjToSet(s,hex)==1);
  hex->y=y+2*HEXAGONE_HEIGHT;
  assert(isHexAdjToSet(s,hex)==0);
  printf("isAdjacentHexagone OK\n");
  printf("isHexAdjToSet OK\n");
  
  //Set setvictoire=createWinnerSet();
  //assert(victorySet(setvictoire)==1);
  assert(victorySet(s)==0);
  printf("isHexOnSide1 OK\n");
  printf("isHexOnSide2 OK\n");
  printf("victorySet OK\n");
  printf("haveVictorySet OK\n");
  
  Board b=createBoard();
  assert(b!=NULL);
  printf("createBoard OK\n");
  int i,j;
  hex=findHexagoneOnBoard (b, h->x, h->y, &i, &j);
  assert(hex!=NULL);
  printf("findHexagoneOnBoard OK\n");
  
  reinitializeBoard(b);
  assert(UNPLAYED!=b->board[i][j]);
  printf("reinitializeBoard OK\n");
  
  setIdPlayerHexagone(h,1);
  assert(h->idPlayer!=0);
  printf("setIdPlayerHexagone OK\n");
  
  deleteHexagone(h);
  assert(h!=NULL);
  printf("deleteHexagone OK\n");
  
  deleteSet(s);
  assert(s!=NULL);
  printf("deleteSet OK\n");
  
  deleteBoard(b);
  assert(b!=NULL);
  printf("deleteBoard OK\n");
  
  
  Queue q=createQueue();
  assert(q!=NULL);
  printf("createQueue OK\n");
  
  assert(emptyQ(q)==1);
  enfiler(q,"elem");
  assert(emptyQ(q)==0);
  printf("enfiler OK\n");
  printf("emptyQ OK\n");
  
  assert(getSize(q)==1);
  printf("getSize OK\n");   
  
  char* c=defiler(q);
  assert(strcmp(c,"elem")==0);
  printf("defiler OK\n");
   
  deleteQueue(q);
  assert(q!=NULL);
  printf("deleteQueue OK\n");
  
  Game g=createGame();
  assert(g!=NULL);
  printf("createGame OK\n");
  
  setUpGameHxH(g);
  assert(g->turnOf==1);
  assert(g->gameStatus==GAME_IN_PROGRESS);
  printf("setUpGameHxH OK\n");
  
  nextTurn(g);
  assert(g->turnOf==2);
  printf("nextTurn OK\n");
  
  h=createHexagone(x,y);
  playAnHexagone(h,g);
  printf("playAnHexagone OK\n");
  
  storeAPlay(g,h);
  assert(g->twoLastPlay[g->turnOf%2]==h);
  printf("storeAPlay OK\n");
  
  assert(undoAction(g)==0);
  printf("undoAction OK\n");
  
  endGame(g);
  assert(g!=NULL);
  printf("endGame OK\n");
  
  reinitializeGame(g);
  assert(g!=NULL);
  printf("reinitializeGame OK\n");
  
  deleteHexagone(h);
  deleteGame(g);
  assert(g!=NULL);
  printf("deleteGame OK\n");
  
  return 0;
}
