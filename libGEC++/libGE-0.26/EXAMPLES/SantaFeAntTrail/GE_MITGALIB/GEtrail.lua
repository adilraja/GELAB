GRID_WIDTH=32
GRID_HEIGHT=32
EMPTY=0
FOOD=1
ANT=8

_trail = {}
_working_trail = {}

function initGEtrail()
	_current_X=0
	_current_Y=0
	_facing_current_X=0
	_facing_current_Y=1
end

function resetGEtrail(e)
	for x=0,GRID_WIDTH-1 do
		for y=0,GRID_HEIGHT-1 do
			_working_trail[x][y]=_trail[x][y]
		end
	end
	resetGEant(e)
	_current_X=0
	_current_Y=0
	_facing_current_X=0
	_facing_current_Y=1
end

function ReadTrailGEtrail(fname)
	-- Create arrays
	for x=0,GRID_WIDTH-1 do
		_trail[x]={}
		_working_trail[x]={}
	end
	-- Read file onto string
	io.input(fname)
	file=io.read("*all")
	-- Skip everything up to "#"
	index=1
	while string.sub(file,index,index)~="#" do
		index=index+1
	end
	x=0 y=0
	while x<GRID_HEIGHT and index~=string.len(file) do
		index=index+1
		ch=string.sub(file,index,index)
		while ch=="\n" do
			index=index+1
			ch=string.sub(file,index,index)
		end
		if ch=="." or ch=="0" then
			_trail[x][y]=0 _working_trail[x][y]=0
		elseif ch=="1" then
			_trail[x][y]=FOOD _working_trail[x][y]=FOOD
		else
			io.write("Wrong character in trail data file ",ch,"\n")
		end
		y=y+1
		if y==GRID_WIDTH then
			x=x+1 y=0
		end
	end
	food=0
	for x=0,GRID_WIDTH-1 do
		for y=0,GRID_HEIGHT-1 do
			if _trail[x][y]==FOOD then food=food+1 end
		end
	end
end

function left()
	if _energy>0 then
		_energy=_energy-1
		if _facing_current_X < _current_X then
			_facing_current_X=_facing_current_X+1
			_facing_current_Y=_facing_current_Y-1
		elseif _facing_current_X > _current_X then
			_facing_current_X=_facing_current_X-1
			_facing_current_Y=_facing_current_Y+1
		elseif _facing_current_Y < _current_Y then
			_facing_current_X=_facing_current_X+1
			_facing_current_Y=_facing_current_Y+1
		else
			_facing_current_X=_facing_current_X-1
			_facing_current_Y=_facing_current_Y-1
		end
	end
end

function right()
	if _energy>0 then
		_energy=_energy-1
		if _facing_current_X < _current_X then
			_facing_current_X=_facing_current_X+1
			_facing_current_Y=_facing_current_Y+1
		elseif _facing_current_X > _current_X then
			_facing_current_X=_facing_current_X-1
			_facing_current_Y=_facing_current_Y-1
		elseif _facing_current_Y < _current_Y then
			_facing_current_X=_facing_current_X-1
			_facing_current_Y=_facing_current_Y+1
		else
			_facing_current_X=_facing_current_X+1
			_facing_current_Y=_facing_current_Y-1
		end
	end
end

function move()
	if _energy>0 then
		_energy=_energy-1
		-- Save current location
		_old_current_X=_current_X
		_old_current_Y=_current_Y
		-- Update location
		_current_X=_facing_current_X
		_current_Y=_facing_current_Y
		-- Apply torroidal property to current pointers
		if _current_X < 0 then
			_current_X=_current_X+GRID_HEIGHT
		elseif _current_X >= GRID_HEIGHT then
			_current_X=_current_X-GRID_HEIGHT
		end
		if _current_Y < 0 then
			_current_Y=_current_Y+GRID_WIDTH
		elseif _current_Y >= GRID_WIDTH then
			_current_Y=_current_Y-GRID_WIDTH
		end
		-- Update facing pointers
		if _facing_current_X > _old_current_X then
			_facing_current_X=_current_X+1
		elseif _facing_current_X < _old_current_X then
			_facing_current_X=_current_X-1
		elseif _facing_current_Y > _old_current_Y then
			_facing_current_Y=_current_Y+1
		elseif _facing_current_Y < _old_current_Y then
			_facing_current_Y=_current_Y-1
		end
		-- Check for food
		if _working_trail[_current_X][_current_Y]==1 then
			_picked_up=_picked_up+1
			_working_trail[_current_X][_current_Y]=0
		end
	end
end

function food_ahead()
	_real_X=_facing_current_X
	_real_Y=_facing_current_Y
	-- Apply torroidal property to facing pointers
	if _real_X < 0 then
		_real_X=_real_X+GRID_HEIGHT
	elseif _real_X >= GRID_HEIGHT then
		_real_X=_real_X-GRID_HEIGHT
	end
	if _real_Y < 0 then
		_real_Y=_real_Y+GRID_WIDTH
	elseif _real_Y >= GRID_WIDTH then
		_real_Y=_real_Y-GRID_WIDTH
	end
	-- Return contents of calculated coordinates
	return _working_trail[_real_X][_real_Y]
end

