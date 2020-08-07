%import libGEjava.*;
function [phenotype_string grammar lhs_rep_array lhs_rep_inds_array numWraps]=ge_getlibgeAttributes(genome, grammar)
%This function does the mapping from genotype to phenotype. It calls
%libGE's jar and gets its work done.
% Inputs:
%   geno: genotype (integer array)
%   grammar: A grammar (java) object, possibly returned from loadGrammar.m
%Output:
%   pheno: phenotype (string)


%-----------------------------------------------------------------
%geno was double type array so I converted it into integer type
if(~isjava(grammar))
    fprintf(1, 'grammar is not a valid java object');
    return;
end
genome = uint32(genome);

grammar.setGenotype(genome, length(genome));

% disp('hello');
phenotype_string=grammar.getPhenotypeString();
numWraps=grammar.getNumWraps();
lhs_rep_array=grammar.getLHSRepIntArray();
lhs_rep_inds_array=grammar.getLHSIndsRepIntArray();

lhs_rep_array=lhs_rep_array(:);
lhs_rep_inds_array=lhs_rep_inds_array(:);


end