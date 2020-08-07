// GEant.c -*- C -*-
#ifndef _GEANT_C_
#define _GEANT_C_

extern int _energy;
extern int _picked_up;

void initGEant(){
  _energy=615;
  _picked_up=0;
}

void resetGEant(int e){
  _energy=e;
  _picked_up=0;
}

#endif

