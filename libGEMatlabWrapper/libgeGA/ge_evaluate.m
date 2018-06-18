% ## Copyright (C) 2017 FGFS
% ## 
% ## This program is free software; you can redistribute it and/or modify it
% ## under the terms of the GNU General Public License as published by
% ## the Free Software Foundation; either version 3 of the License, or
% ## (at your option) any later version.
% ## 
% ## This program is distributed in the hope that it will be useful,
% ## but WITHOUT ANY WARRANTY; without even the implied warranty of
% ## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
% ## GNU General Public License for more details.
% ## 
% ## You should have received a copy of the GNU General Public License
% ## along with this program.  If not, see <http://www.gnu.org/licenses/>.
% 
% ## -*- texinfo -*- 
% ## @deftypefn {Function File} {@var{retval} =} Evaluate (@var{input1}, @var{input2})
% ##
% ## @seealso{}
% ## @end deftypefn
% 
% ## Author: FGFS <fgfs@fgfs-Precision-WorkStation-T3500>
% ## Created: 2017-03-16

function [fitness, individual] = ge_evaluate (individual, data)
    individual.isEvaluated=1;%Mark this individual as evaluated, so that it does not get re-evaluated
    var='X';
    [x, y]=size(data.train_x);
    for(i=1:y)
       val=strcat('data.train_x(:,', num2str(i),')');
       var2=strcat(var, num2str(i));
       eval([var2 '=' val ';']); 
    end
   
    %in subsequent generations. This is supposed to save evaluation time.
    if(individual.valid)%if this is a valid individual
        result=eval(individual.string);
        individual.result=result;
        individual.fitness=ge_mse(result, data.train_y)
    else
        individual.fitness=50000;
    %You ca plug in your own fitness function here.
    fitness=individual.fitness;
end
