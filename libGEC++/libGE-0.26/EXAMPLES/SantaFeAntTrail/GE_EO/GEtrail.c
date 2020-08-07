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
	_facing_current_X=0;
	_facing_current_Y=1;
}

void resetGEtrail(int e){
	int x,y;
	for (x=0; x<GRID_WIDTH; x++){
		for (y=0; y<GRID_HEIGHT; y++){
			_working_trail[x][y]=_trail[x][y];
		}
	}
	resetGEant(_energy,_picked_up,e);
	_current_X=0;
	_current_Y=0;
	_facing_current_X=0;
	_facing_current_Y=1;
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
	while(ifs!=NULL && ch!='#'){
		fread (&ch, sizeof(char), 1, ifs);
	}
	while(x<GRID_HEIGHT){
		fread(&ch, sizeof(char), 1, ifs);
		while(ifs!=NULL && ch=='\n'){
			fread (&ch, sizeof(char), 1, ifs);
		}
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
		y++;
		if(y==GRID_WIDTH){
			x++;
			y=0;
		}
	}
	if(ifs==NULL){
	  fprintf(stderr,"Error reading trail data file");
	  exit(0);
	  }
	
	for (food=0, x=0; x<GRID_WIDTH; x++){
		for (y=0; y<GRID_HEIGHT; y++){
			food+=_trail[x][y]==FOOD;
		}
	}
	fclose(ifs);
}

void left(){
	if(_energy>0){
		_energy--;
		if(_facing_current_X < _current_X){
			_facing_current_X=_facing_current_X+1;
			_facing_current_Y=_facing_current_Y-1;
		}
		else if(_facing_current_X > _current_X){
			_facing_current_X=_facing_current_X-1;
			_facing_current_Y=_facing_current_Y+1;
		}
		else if(_facing_current_Y < _current_Y){
			_facing_current_X=_facing_current_X+1;
			_facing_current_Y=_facing_current_Y+1;
		}
		else{
			_facing_current_X=_facing_current_X-1;
			_facing_current_Y=_facing_current_Y-1;
		}
	}
}

void right(){
	if(_energy>0){
		_energy--;
		if(_facing_current_X < _current_X){
			_facing_current_X=_facing_current_X+1;
			_facing_current_Y=_facing_current_Y+1;
		}
		else if(_facing_current_X > _current_X){
			_facing_current_X=_facing_current_X-1;
			_facing_current_Y=_facing_current_Y-1;
		}
		else if(_facing_current_Y < _current_Y){
			_facing_current_X=_facing_current_X-1;
			_facing_current_Y=_facing_current_Y+1;
		}
		else{
			_facing_current_X=_facing_current_X+1;
			_facing_current_Y=_facing_current_Y-1;
		}
	}
}

void move(){
	int _old_current_X,_old_current_Y;
	if(_energy > 0){
		_energy--;
		/* Save current location */
		_old_current_X=_current_X;
		_old_current_Y=_current_Y;
		/* Update location */
		_current_X=_facing_current_X;
		_current_Y=_facing_current_Y;
		/* Apply torroidal property to current pointers */
		if(_current_X < 0){
			_current_X=_current_X+GRID_HEIGHT;
		}
		else if(_current_X >= GRID_HEIGHT){
			_current_X=_current_X-GRID_HEIGHT;
		}
		if(_current_Y < 0){
			_current_Y=_current_Y+GRID_WIDTH;
		}
		else if(_current_Y >= GRID_WIDTH){
			_current_Y=_current_Y-GRID_WIDTH;
		}
		/* Update facing pointers */
		if(_facing_current_X > _old_current_X){
			_facing_current_X=_current_X+1;
		}
		else if(_facing_current_X < _old_current_X){
			_facing_current_X=_current_X-1;
		}
		else if(_facing_current_Y > _old_current_Y){
			_facing_current_Y=_current_Y+1;
		}
		else if(_facing_current_Y < _old_current_Y){
			_facing_current_Y=_current_Y-1;
		}
		/* Check for food */
		if(_working_trail[_current_X][_current_Y]==1){
			_picked_up=_picked_up+1;
			_working_trail[_current_X][_current_Y]=0;
		}
	}
}

int food_ahead(){
	int _real_X,_real_Y;
	_real_X=_facing_current_X;
	_real_Y=_facing_current_Y;
	/* Apply torroidal property to facing pointers */
	if(_real_X < 0){
		_real_X=_real_X+GRID_HEIGHT;
	}
	else if(_real_X >= GRID_HEIGHT){
		_real_X=_real_X-GRID_HEIGHT;
	}
	if(_real_Y < 0){
		_real_Y=_real_Y+GRID_WIDTH;
	}
	else if(_real_Y >= GRID_WIDTH){
		_real_Y=_real_Y-GRID_WIDTH;
	}
	/* Return contents of calculated coordinates */
	return _working_trail[_real_X][_real_Y];
}

#endif

