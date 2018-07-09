function antright
%ANTRIGHT    Turns the GPLAB artificial ant to the right.
%   ANTRIGHT returns the number of the time step used by the ant after
%   turning. Other variables are returned as global variables. 
%
%   See also ANTFITNESS, ANTFOODAHEAD, ANTIF, ANTMOVE, ANTLEFT, ANTPROGN2, ANTPROGN3
%
%   Copyright (C) 2003-2015 Sara Silva (sara@fc.ul.pt)
%   This file is part of the GPLAB Toolbox

% Modified in October 2006:
% - removed some unnecessary global variables, added others
% - added commands to update the 'path' variable

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
   newdirection='r';
elseif strcmp(direction,'d') % facing down
   newdirection='l';
elseif strcmp(direction,'r') % facing right
   newdirection='d';
elseif strcmp(direction,'l') % facing left
   newdirection='u';
end

direction=newdirection;
ntime=ntime+1;

if sim
    antpath(ntime,x,y,direction,npellets,0);
    % 0 is the setting of "looked ahead", true only if 'antif' is executed
end
