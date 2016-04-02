#include "hexagone.h"

hexagone create_hexagon(int abs,int ord){
  hexagone h;
  h.abscisse=abs;
  h.ordonnee=ord;
  h.id_player=0;
  return(h);
}

int be_free_hexagon(hexagone h){
  return(h.id_player==0);
}

void edit_hexagon(hexagone *h,int id){
  h->id_player=id;
}

int adjacent_hexagone(hexagone h, hexagone i){
  if(h.abscisse==i.abscisse)
    return(i.ordonnee==h.ordonnee-1 || i.ordonnee==h.ordonnee+1);
  
  if(h.ordonnee==i.ordonnee)
    return(i.abscisse==h.abscisse-1 || i.abscisse==h.abscisse+1);
  
  if(h.ordonnee==i.ordonnee-1)
    return(h.abscisse==i.abscisse-1);
  
  if(h.ordonnee==i.ordonnee+1)
    return(h.abscisse==i.abscisse+1);

  return(0);
}