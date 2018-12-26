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

function [retval] = ge_createChildPopulation(population, params)
    childPopulation=ge_initPop(params, 0);
    j=1;
    for(i=1:length(population)/2)
        [parent1, parent2]=feval(params.selectionFunction, population, params);
        dice=rand(1);
        if(dice<params.weavep)
            [child1, child2] = ge_weave(parent1, parent2, params);
        elseif(dice<(params.weavep+params.tweavep))
            [child1, child2] = ge_tightweave(parent1, parent2, params);
        elseif(dice<(params.weavep+params.tweavep+params.spxoverp))
            [child1, child2]=ge_spcrossover(parent1, parent2, params);%Apply crossover
        else
            [child1, child2]=ge_vpcrossover(parent1, parent2, params);%Apply crossover
        end
        dice=rand(1);
        if(dice<params.pmutationp)
            child1=ge_pmutation(child1, params);
            child2=ge_pmutation(child2, params);
        elseif(dice<(params.pmutationp+params.fpmutationp))
            child1=ge_fpmutation(child1, params);
            child2=ge_fpmutation(child2, params);
        else
            child1=ge_fbmutation(child1, params);
            child2=ge_fbmutation(child2, params);
        end
        childPopulation(j)=child1;
        childPopulation(j+1)=child2;
        j=j+2;
    end
    retval=childPopulation;
end
