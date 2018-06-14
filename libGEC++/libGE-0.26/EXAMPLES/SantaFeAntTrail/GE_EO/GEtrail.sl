variable GRID_WIDTH=32;
variable GRID_HEIGHT=32;
variable EMPTY=0;
variable FOOD=1;
variable ANT=8;

variable _trail = Integer_Type [GRID_WIDTH,GRID_HEIGHT];
variable _working_trail = Integer_Type [GRID_WIDTH,GRID_HEIGHT];
variable food;
variable _current_X, _current_Y, _facing_current_X, _facing_current_Y;

define initGEtrail(){
	_current_X=0;
	_current_Y=0;
	_facing_current_X=0;
	_facing_current_Y=1;
}

define resetGEtrail(e){
	variable x,y;
	for (x=0; x<GRID_WIDTH; x++){
		for (y=0; y<GRID_HEIGHT; y++){
			_working_trail[x,y]=_trail[x,y];
		}
	}
	resetGEant(e);
	_current_X=0;
	_current_Y=0;
	_facing_current_X=0;
	_facing_current_Y=1;
}

define ReadTrailGEtrail(fname){
	variable x=0, y=0;
	variable ifs;
	ifs=fopen(fname,"r");
	if (ifs==NULL){
		verror ("%s failed to open", fname);
	}
	variable ch='.';
	while(ifs!=NULL and ch!='#'){
		fread (&ch, Char_Type, 1, ifs);
	}
	while(x<GRID_HEIGHT){
		fread (&ch, Char_Type, 1, ifs);
		while(ifs!=NULL and ch=='\n'){
			fread (&ch, Char_Type, 1, ifs);
		}
		if(ch == '.' or ch == '0'){
			_trail[x,y]=0;_working_trail[x,y]=0;
		}
		else if(ch == '1'){
			_trail[x,y]=1;_working_trail[x,y]=1;
		}
		else{
			verror ("Wrong character in trail data file '%c'",ch);
		}
		y++;
		if(y==GRID_WIDTH){
			x++;
			y=0;
		}
	}
	if(ifs==NULL){
		verror("Error reading trail data file");
	}
	for(food=0, x=0; x<GRID_WIDTH; x++){
		for(y=0; y<GRID_HEIGHT; y++){
			food+=_trail[x,y]==FOOD;
		}
	}
	fclose(ifs);
}

define left(){
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

define right(){
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

define move(){
	variable _old_current_X,_old_current_Y;
	if(_energy > 0){
		_energy--;
		% Save current location
		_old_current_X=_current_X;
		_old_current_Y=_current_Y;
		% Update location
		_current_X=_facing_current_X;
		_current_Y=_facing_current_Y;
		% Apply torroidal property to current pointers
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
		% Update facing pointers
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
		% Check for food
		if(_working_trail[_current_X,_current_Y]==1){
			_picked_up=_picked_up+1;
			_working_trail[_current_X,_current_Y]=0;
		}
	}
}

define food_ahead(){
	variable _real_X,_real_Y;
	_real_X=_facing_current_X;
	_real_Y=_facing_current_Y;
	% Apply torroidal property to facing pointers
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
	% Return contents of calculated coordinates
	return _working_trail[_real_X,_real_Y];
}

