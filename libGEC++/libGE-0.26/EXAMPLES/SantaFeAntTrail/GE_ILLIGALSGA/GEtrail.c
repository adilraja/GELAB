// GEtrail.c -*- C -*-
#ifndef _GETRAIL_C_
#define _GETRAIL_C_

#include<stdio.h>
#include<stdlib.h>
#define GRID_WIDTH 32
#define GRID_HEIGHT 32
#define EMPTY 0
#define FOOD 1
#define ANT 8

extern int _energy;
extern int _picked_up;

int _trail[GRID_WIDTH][GRID_HEIGHT];
int _working_trail[GRID_WIDTH][GRID_HEIGHT];
int food;
int _current_X, _current_Y, _facing_current_X, _facing_current_Y;

void initGEtrail(int e){
  _current_X=0;
  _current_Y=0;
  _facing_current_X=1;
  _facing_current_Y=0;
}

void resetGEtrail(int e){
  int x,y;
  for (x=0; x<GRID_WIDTH; x++)
    for (y=0; y<GRID_HEIGHT; y++)
      _working_trail[x][y]=_trail[x][y];

  resetGEant(_energy,_picked_up,e);

  _current_X=0;
  _current_Y=0;
  _facing_current_X=1;
  _facing_current_Y=0;
}

void ReadTrailGEtrail(char *fname){
  int x=0, y=0;
  char ch='.';
  FILE *ifs;

  ifs=fopen(fname,"r");
  if (ifs==NULL){
    fprintf(stderr,"%s failed to open\n", fname);
    exit(0);
    }

  while (ifs!=NULL && ch!='#') 
    fread (&ch, sizeof(char), 1, ifs);
  while (y<GRID_HEIGHT){
    fread (&ch, sizeof(char), 1, ifs);
    while (ifs!=NULL && ch=='\n')
      fread (&ch, sizeof(char), 1, ifs);
    if(ch == '.' || ch == '0'){
      _trail[x][y]=0;_working_trail[x][y]=0;
      }
    else if(ch == '1'){
      _trail[x][y]=1;_working_trail[x][y]=1;
      }
    else{
      fprintf(stderr,"Wrong character in trail data file '%c'\n",ch);
      exit(0);
      }
    x++;
    if (x==GRID_WIDTH){
        y++;
        x=0;
      }
    }
  if (ifs==NULL){
    fprintf(stderr,"Error reading trail data file");
    exit(0);
    }

  for (food=0, x=0; x<GRID_WIDTH; x++)
    for (y=0; y<GRID_HEIGHT; y++)
      food+=_trail[x][y]==FOOD;
  fclose(ifs);
}

void right(){
  _energy--;
  if(_facing_current_Y<0){
      _facing_current_X=_current_X+1;
      _facing_current_Y=_current_Y;
    }
  else if(_facing_current_Y>GRID_HEIGHT){
      _facing_current_X=_current_X-1;
      _facing_current_Y=_current_Y;
    }
  else if(_facing_current_X<0){
      _facing_current_Y=_current_Y-1;
      _facing_current_X=_current_X;
    }
  else if(_facing_current_X>GRID_WIDTH){
      _facing_current_Y=_current_Y+1;
      _facing_current_X=_current_X;
    }
  else if(_facing_current_Y<_current_Y){
      _facing_current_X=_current_X+1;
      _facing_current_Y=_current_Y;
    }
  else if(_facing_current_Y>_current_Y){
      _facing_current_X=_current_X-1;
      _facing_current_Y=_current_Y;
    }
  else if(_facing_current_X<_current_X){
      _facing_current_X=_current_X;
      _facing_current_Y=_current_Y-1;
    }
  else if(_facing_current_X>_current_X){
      _facing_current_X=_current_X;
      _facing_current_Y=_current_Y+1;
    }
}

void left(){
  _energy--;
  if(_facing_current_Y<0){
      _facing_current_X=_current_X-1;
      _facing_current_Y=_current_Y;
    }
  else if(_facing_current_Y>GRID_HEIGHT){
      _facing_current_X=_current_X+1;
       _facing_current_Y=_current_Y;
    }
  else if(_facing_current_X<0){
      _facing_current_Y=_current_Y+1;
       _facing_current_X=_current_X;
    }
  else if(_facing_current_X>GRID_WIDTH){
      _facing_current_Y=_current_Y-1;
       _facing_current_X=_current_X;
    }
  else if(_facing_current_Y<_current_Y){
      _facing_current_X=_current_X-1;
      _facing_current_Y=_current_Y;
    }
  else if(_facing_current_Y>_current_Y){
      _facing_current_X=_current_X+1;
      _facing_current_Y=_current_Y;
    }
  else if(_facing_current_X<_current_X){
      _facing_current_X=_current_X;
      _facing_current_Y=_current_Y+1;
    }
  else if(_facing_current_X>_current_X){
      _facing_current_X=_current_X;
      _facing_current_Y=_current_Y-1;
    }
}

void move(){
  int old_current_X,old_current_Y;
  old_current_X=_current_X;
  old_current_Y=_current_Y;
  _energy--;
  if( (_facing_current_X<GRID_WIDTH) && !(_facing_current_X<0) 
       && (_facing_current_Y<GRID_HEIGHT) && !(_facing_current_Y<0)){
      _current_X=_facing_current_X;
      _current_Y=_facing_current_Y;
      if(_working_trail[_current_X][_current_Y]==1){
	  _picked_up++;
	  _working_trail[_current_X][_current_Y]=0;
	}
      if(old_current_X<_current_X){
	  _facing_current_X=_current_X+1;
	  _facing_current_Y=_current_Y;
	}
      if(old_current_X>_current_X){
	  _facing_current_X=_current_X-1;
	  _facing_current_Y=_current_Y;
	}
      if(old_current_Y<_current_Y){
	  _facing_current_Y=_current_Y+1;
	  _facing_current_X=_current_X;
	}
      if(old_current_Y>_current_Y){
	  _facing_current_Y=_current_Y-1;
	  _facing_current_X=_current_X;
	}
    } 
  else{
      if(_facing_current_X>GRID_WIDTH-1){
	  _current_X=0;
	  _facing_current_X=1;
	}
      else if(_facing_current_X<0){
	  _current_X=GRID_WIDTH-1;
	  _facing_current_X=GRID_WIDTH-2;
	}
      else{
	  if(_facing_current_Y>GRID_HEIGHT-1){
	      _current_Y=0;
	      _facing_current_Y=1;
	    }
	  else if(_facing_current_Y<0){
	      _current_Y=GRID_HEIGHT-1;
	      _facing_current_Y=GRID_HEIGHT-2;
	    }
	}
      if(_working_trail[_current_X][_current_Y]==1){
	  _picked_up++;
	  _working_trail[_current_X][_current_Y]=0;
	}
    }
  _working_trail[_current_X][_current_Y]=8;
}

int food_ahead(){
  int is_there=0;
  if( (_facing_current_X<GRID_WIDTH) && !(_facing_current_X<0) 
       && (_facing_current_Y<GRID_HEIGHT) && !(_facing_current_Y<0)){
    if(_working_trail[_facing_current_X][_facing_current_Y]==1){
      is_there=1;
      }
    else{
      is_there=0;
      }
    }
  else{
    if(_facing_current_X>GRID_WIDTH-1){
      if(_working_trail[0][_current_Y]==1) is_there=1;
      else is_there=0;
      }
    else if(_facing_current_X<0){
      if(_working_trail[GRID_WIDTH-1][_current_Y]==1) is_there=1;
      else is_there=0;
      }
    else{
      if(_facing_current_Y>GRID_HEIGHT-1){
        if(_working_trail[_current_X][0]==1) is_there=1;
        else is_there=0;
        }
      else if(_facing_current_Y<0){
        if(_working_trail[_current_X][GRID_HEIGHT-1]==1) is_there=1;
        else is_there=0;
        }
      }
    }
  return is_there;
}

#endif

