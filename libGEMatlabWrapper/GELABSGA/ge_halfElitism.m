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

function survivedPopulation = ge_halfElitism (parentPopulation, childPopulation, params)
%     population=[parentPopulation childPopulation];
    ppopSize=length(parentPopulation);
    cpopSize=length(childPopulation);
%     disp(ppopSize);
    pfitness=zeros(ppopSize, 1);
    cfitness=zeros(cpopSize, 1);
    for(i=1:ppopSize)
      pfitness(i)=parentPopulation(i).fitness;
    end
    for(i=1:cpopSize)
        cfitness(i)=childPopulation(i).fitness;
    end
    
    if(params.lowerisbetter==1)
        [psortedFitness, pI]=sort(pfitness, 'ascend');
        [csortedFitness, cI]=sort(cfitness, 'ascend');   
    elseif(params.lowerisbetter==0)
        [psortedFitness, pI]=sort(pfitness, 'descend');
        [csortedFitness, cI]=sort(cfitness, 'descend');
    else
        disp('Please enter the right values for Lower is Better param: 0 or 1\n');
    end
    plen=ceil(ppopSize/2);
    clen=ceil(cpopSize/2);
    survivedPPopulation=parentPopulation(pI(1:plen));
    survivedCPopulation=childPopulation(cI(1:clen));
    survivedPopulation=[survivedPPopulation survivedCPopulation];
    popSize=length(survivedPopulation);
    fitness=zeros(popSize,1);
    for(i=1:popSize)
        fitness(i)=survivedPopulation(i).fitness;
    end
    
    if(params.lowerisbetter==1)
        [sortedFitness, I]=sort(fitness, 'ascend');
    elseif(params.lowerisbetter==0)
        [sortedFitness, I]=sort(fitness, 'descend');
    else
        disp('Please enter the right values for Lower is Better param: 0 or 1\n');
    end
%     length(survivedPopulation);
%     disp('The length');
    temp=survivedPopulation(I(1:params.popSize));
    survivedPopulation=temp;
%     disp(I(1));
end
