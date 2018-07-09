function food=antfoodahead
%ANTFOODAHEAD    Tests if there is food ahead of the GPLAB artificial ant.
%   ANTFOODAHEAD returns true if there is food ahead of the artificial ant;
%   returns false otherwise.
%
%   Output arguments:
%      FOOD - whether there is food ahead (boolean)
%
%   See also ANTFITNESS, ANTMOVE, ANTIF, ANTRIGHT, ANTLEFT, ANTPROGN2, ANTPROGN3
%
%   Copyright (C) 2003-2015 Sara Silva (sara@fc.ul.pt)
%   This file is part of the GPLAB Toolbox

global trail;
global x;
global y;
global direction;
%global npellets;
%global maxtime;
%global ntime;

[newx,newy]=antnewpos(x,y,direction,trail);
food=(trail(newx,newy)==1);
