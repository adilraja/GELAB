%individual = ge_createIndividual (genome_length, grammar, runGeno2Pheno)
%## Copyright (C) 2017 FGFS
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
% ## @deftypefn {Function File} {@var{retval} =} createIndividual (@var{input1}, @var{input2})
% ##
% ## @seealso{}
% ## @end deftypefn
% 
% ## Author: FGFS <fgfs@fgfs-Precision-WorkStation-T3500>
% ## Created: 2017-03-16

function individual = ge_createIndividual (params, sensibleInit)

% if(contains(ctfroot, 'MATLAB'))
%   % MATLAB is running.
%   rng('shuffle', 'twister');
% end
     initTreeDepth=randi(7,1)+3;
%     initTreeDepth=truerand(1,1,1,7)+3;
    params.grammar.setMaxDepth(initTreeDepth);
    genome_length=params.genome_length;
    grammar=params.grammar;
    terminals=string(char(grammar.getTerminals()));
    terminals = strrep(terminals,' ','');%Remove spaces from strings of terminals
    scores=zeros(length(terminals),1);
    terminals_scores=table(terminals, scores);
    
    individual=struct('genome', [], 'string', '', 'fitness', 500000, 'testFitness', 500000, 'ID', [0 0], 'left_parent', [0 0], 'right_parent', [0 0], 'valid', 0, 'treeDepth', 0, 'numWraps', 0, 'isEvaluated', 0, 'age', 0, 'result', [], 'testResult', [], 'slope', 1, 'intercept', 0, 'constants', [], 'improvable', 1, 'improvable2', 1, 'terminals_scores', []);
%    grammar.setGenotype(individual.genome, length(individual.genome));
    
    if(sensibleInit)
         
        while(~grammar.init(randi(10,1)))
%              disp('init didnt work');
        end
        individual.genome=grammar.getGenotypeIntArray();
        genome=individual.genome;
        [phenotype_string grammar lhs_rep_array lhs_rep_inds_array]=ge_getlibgeAttributes(individual.genome, grammar);
        individual.numWraps=grammar.getNumWraps();
        individual.lhs_rep_array=lhs_rep_array;
        individual.lhs_rep_inds_array=lhs_rep_inds_array;
        individual.lhs_rep_type_array=grammar.getLHSRepTypeIntArray();
        %individual.string=grammar.getPhenotypeString();
        individual.string=phenotype_string;
        individual.valid=grammar.isPhenotypeValid();%
        individual.treeDepth=grammar.getTreeDepth;
    else
        individual.genome=randi([0, 500000] , 1, genome_length);
        individual.numWraps=0;
        individual.lhs_rep_array=[];
        individual.lhs_rep_inds_array=[];
        individual.lhs_rep_type_array=[];
        %individual.string=grammar.getPhenotypeString();
        individual.string='';
        individual.valid=0;%
        individual.treeDepth=0;
    end
    individual.constants=ones(1, params.numCoefs);
    %The following flag tells us which operator was used to create the
    %individual. 0 for none, 1 for fpxover, 2, for vpxover, 3 for weave, 4
    %for tweave
    individual.operator=6;%1, 2, 3, 4, 5, 6
    individual.mutationoperator=5;
    %individual.grammar=grammar;% Trying to assign the grammar object to this struct as a field. I hope this works.   
    %s=individual.string;
    
    %individual.img=rand(300,300);
    %individual.fitness=500000;
    for(i=1:length(terminals_scores.terminals))
        c=strfind(individual.string, terminals_scores.terminals(i));
        count1=length(c);
        terminals_scores.scores(i)=count1;
    end
    individual.terminals_scores=terminals_scores;
end
