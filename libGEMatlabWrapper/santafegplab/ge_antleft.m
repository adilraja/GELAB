function antleft
%ANTLEFT    Turns the GPLAB artificial ant to the left.
%   ANTLEFT(SIM) returns the number of the time step used by the ant after
%   turning. Other variables are returned as global variables.
%
%   See also ANTFITNESS, ANTFOODAHEAD, ANTIF, ANTMOVE, ANTRIGHT, ANTPROGN2, ANTPROGN3
%
%   Copyright (C) 2003-2015 Sara Silva (sara@fc.ul.pt)
%   This file is part of the GPLAB Toolbox

%global trail;
global x;
global y;
global direction;
global npellets;
%global maxtime;
global ntime;

global sim;
global path;

% new direction:
if strcmp(direction,'u') % facing up
   newdirection='l';
elseif strcmp(direction,'d') % facing down
   newdirection='r';
elseif strcmp(direction,'r') % facing right
   newdirection='u';
elseif strcmp(direction,'l') % facing left
   newdirection='d';
end

direction=newdirection;
ntime=ntime+1;

if sim
    antpath(ntime,x,y,direction,npellets,0);
    % 0 is the setting of "looked ahead", true only if 'antif' is executed
end
