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
% ## @deftypefn {Function File} {@var{retval} =} replacement (@var{input1}, @var{input2})
% ##
% ## @seealso{}
% ## @end deftypefn
% 
% ## Author: Adil <adil@adil-HP-250-G3-Notebook-PC>
% ## Created: 2017-03-16

function survivedPopulation = ge_replacement (parentPopulation, childPopulation, params)
    population=[parentPopulation childPopulation];
    popSize=length(population);
    disp(popSize);
    for(i=1:popSize)
      fitness(i)=population(i).fitness;
    end
    if(params.lowerisbetter==1)
        [sortedFitness, I]=sort(fitness, 'ascend');
    elseif(params.lowerisbetter==0)
        [sortedFitness, I]=sort(fitness, 'descend');
    else
        disp('Please enter the right values for Lower is Better param: 0 or 1\n');
    end
    survivedPopulation=population(I(1:params.popSize));
    disp(I(1));
end
