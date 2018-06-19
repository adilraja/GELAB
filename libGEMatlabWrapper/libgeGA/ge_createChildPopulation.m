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

function [retval] = ge_createChildPopulation(population, genome_length, grammar)
    childPopulation=ge_initPop(length(population)-1, genome_length, grammar, 0);
    j=1;
    for(i=1:length(population)/2)
        [parent1, parent2]=ge_selection(population, 2);
        [child1, child2]=ge_crossover(parent1, parent2, genome_length, grammar);%Apply crossover
        if(rand(1)<0.5)
          child1=ge_mutation(child1);
        end
        if(rand(1)<0.5)
          child2=ge_mutation(child2);
        end
        childPopulation(j)=child1;
        childPopulation(j+1)=child2;
        j=j+2;
    end
    retval=childPopulation;
end
