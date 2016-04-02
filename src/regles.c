#include "regles.h"

int ckeck_round(int nbtour, int idplayer){
  return(idplayer==(nbtour%2)+1);
}

int who_play(int nbtour){
  return((nbtour%2)+1);
}

int ckeck_select_hexagon(hexagone h, hexagone i){
  if(be_free_hexagon(i))
    return(adjacent_haxagon(h,i));
  return(0);
}


