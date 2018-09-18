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

function child_population = ge_cGACreateChildPopulation(probability_matrix, params)
   
    individual=ge_createIndividual (params.genome_length, params.grammar, 0);
    population=repmat(individual, [1, params.popSize]);
    pop_genomes=randn(params.genome_length, params.popSize);
    pop_genomes=floor(pop_genomes.*probability_matrix(:, 2)+probability_matrix(:,1));
    for(i=1:length(population))
        population(i).genome=pop_genomes(:, i);
    end
    child_population=population;
end
