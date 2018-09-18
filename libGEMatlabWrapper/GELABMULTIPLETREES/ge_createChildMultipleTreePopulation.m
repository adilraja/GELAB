% ## Copyright (C) 2017 Adil
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
% ## @deftypefn {Function File} {@var{retval} =} createChildPopulation (@var{input1}, @var{input2})
% ##
% ## @seealso{}
% ## @end deftypefn
% 
% ## Author: Adil <adil@adil-HP-250-G3-Notebook-PC>
% ## Created: 2017-03-16

function [retval] = ge_createChildMultipleTreePopulation(population, params)
    childPopulation=ge_initMultipleTreePop(params, 0);
    j=1;
    for(i=1:length(population)/2)
        [parent1, parent2]=ge_multipleTreeSelection(population, params);
        [c_multiTree1, c_multiTree2]=ge_multipleTreeCrossover(parent1, parent2, params);%Apply crossover
        if(rand(1)<0.5)
          c_multiTree1=ge_multipleTreeMutation(c_multiTree1, params);
        end
        if(rand(1)<0.5)
          c_multiTree2=ge_multipleTreeMutation(c_multiTree2, params);
        end
        childPopulation(j)=c_multiTree1;
        childPopulation(j+1)=c_multiTree2;
        j=j+2;
    end
    retval=childPopulation;
end
