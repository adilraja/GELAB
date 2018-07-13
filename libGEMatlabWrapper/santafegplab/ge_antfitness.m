function individual=ge_antfitness(individual, data)
%ANTFITNESS    Measures the fitness of a GPLAB artificial ant.
%   ANTFITNESS(INDIVIDUAL,PARAMS,DATA,TERMINALS,VARSVALS) returns
%   the fitness of INDIVIDUAL, measured as the number of food
%   pellets eaten in the artificial ant food trail during 400
%   time steps. Also returns the results obtained in each fitness
%   case (when there is only one food trail, it is the same as the
%   fitness. Also returns other variables as global variables.
%
%   Input arguments:
%      INDIVIDUAL - the individual whose fitness is to measure (struct)
%      PARAMS - the current running parameters (struct)
%      DATA - the dataset on which to measure the fitness (struct)
%      TERMINALS - (not needed here - kept for compatibility purposes)
%      VARSVALS - (not needed here - kept for compatibility purposes)
%   Output arguments:
%      INDIVIDUAL - the individual whose fitness was measured (struct)
%
%   See also CALCFITNESS, REGFITNESS, RMSE
%
%   Copyright (C) 2003-2015 Sara Silva (sara@fc.ul.pt)
%   This file is part of the GPLAB Toolbox

global trail;
global x;
global y;
global direction;
global npellets;
global maxtime;
global ntime;

global sim;
global path;

trail=data.train_x;
x=1;
y=1;
direction='r';
npellets=0;
maxtime=400;
ntime=0;

if sim
    antpath(ntime,x,y,direction,npellets,0);
    % 0 is the setting of "looked ahead", true only if 'antif' is executed
end

% evaluate ant and count food pellets eaten:
% (repeat program until maxtime)
if(individual.valid==0)
    individual.fitness=0;%Bad fitness, (Higher is better)
    return;
end

while 1
   eval(individual.string);
   if ntime>=maxtime
      break
   end
end

% raw fitness:
individual.fitness=npellets; %higher fitness means better individual

individual.result(1)=individual.fitness;
