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
% ## @deftypefn {Function File} {@var{retval} =} initPopulation (@var{input1}, @var{input2})
% ##
% ## @seealso{}
% ## @end deftypefn
% 
% ## Author: Adil <adil@adil-HP-250-G3-Notebook-PC>
% ## Created: 2017-03-16

function pop = ge_initPopulation (popSize, genome_length, grammar)
    for(i=1:popSize)
        pop(i)=ge_createIndividual(genome_length, grammar);
    end
    
end
