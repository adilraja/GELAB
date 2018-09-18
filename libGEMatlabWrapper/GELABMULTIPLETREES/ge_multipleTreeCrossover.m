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
% ## @deftypefn {Function File} {@var{retval} =} Crossover (@var{input1}, @var{input2})
% ##
% ## @seealso{}
% ## @end deftypefn
% 
% ## Author: FGFS <fgfs@fgfs-Precision-WorkStation-T3500>
% ## Created: 2017-03-16

function [c_multiTree1, c_multiTree2] = ge_multipleTreeCrossover (multiTree1, multiTree2, params)

temp_ind1=randperm(length(multiTree1.ind));
temp_ind2=randperm(length(multiTree2.ind));

c_multiTree1=ge_createMultipleTreeIndividual(params, 0);
c_multiTree2=ge_createMultipleTreeIndividual(params, 0);

for(i=1:length(temp_ind1))
    parent1=multiTree1.ind(i);
    parent2=multiTree2.ind(i);
    [child1, child2]=ge_crossover(parent1, parent2, params.genome_length, params.grammar);%Apply crossover
    c_multiTree1.ind(i)=child1;
    c_multiTree2.ind(i)=child2;
end

% genome1=ensembleind1.genome(:);
% genome2=ind2.genome(:);
% gl1=length(genome1);
% gl2=length(genome2);
% y=genome_length;
% 
%   c1=floor(rand(1)*(gl1-1))+1;
%   c2=floor(rand(1)*(gl2-1))+1;
% %  y2=y/2;
% 
% %Crossover scheme for variable length genome.
%   c_genome1= [genome1(1:c1); genome2(c2+1:gl2)];
% 
% 
%   c_genome2= [genome2(1:c2); genome1(c1+1:gl1)];
% 
%   c_ind1=ge_createIndividual(genome_length, grammar, 0);
%   c_ind2=ge_createIndividual(genome_length, grammar, 0);
% 
%   c_ind1.genome=c_genome1;
%   c_ind2.genome=c_genome2;
%   
% %   c_ind1.grammar.setGenotype(c_ind1.genome, length(c_ind1.genome));
% %   c_ind2.grammar.setGenotype(c_ind2.genome, length(c_ind2.genome));
% c_ind1.left_parent=ind1.ID;
% c_ind1.right_parent=ind2.ID;
% 
% c_ind2.left_parent=ind2.ID;
% c_ind2.right_parent=ind1.ID;

end
