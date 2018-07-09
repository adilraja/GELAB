function antmove
%ANTMOVE    Moves the GPLAB artificial ant forward one step.
%   ANTMOVE returns the number of the time step used by the ant after
%   moving. Other variables are returned as global variables.
%
%   See also ANTFITNESS, ANTFOODAHEAD, ANTIF, ANTRIGHT, ANTLEFT, ANTPROGN2, ANTPROGN3
%
%   Copyright (C) 2003-2015 Sara Silva (sara@fc.ul.pt)
%   This file is part of the GPLAB Toolbox

global trail;
global x;
global y;
global direction;
global npellets;
%global maxtime;
global ntime;

global sim;
global path;
    
% new coordinates:
[newx,newy]=antnewpos(x,y,direction,trail);

% if there's food, eat it:
if trail(newx,newy)==1
    trail(newx,newy)=0;
    npellets=npellets+1;
end

x=newx;
y=newy;
ntime=ntime+1;

if sim
   antpath(ntime,x,y,direction,npellets,0);
   % 0 is the setting of "looked ahead", true only if 'antif' is executed
end
