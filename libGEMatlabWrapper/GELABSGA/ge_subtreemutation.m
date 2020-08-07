%function individual = ge_subtreemutation(individual, params). This function
%implements fixed bounds mutation. Muhammad Adil Raja, 3rd July, 2019.
function individual = ge_subtreemutation(individual, params)

% if(contains(ctfroot, 'MATLAB'))
%   % MATLAB is running.
%   rng('shuffle', 'twister');
% end

    temp_ind=ge_createIndividual(params, 1);
    [phenotype_string grammar lhs_rep_array lhs_rep_inds_array numWraps]=genotype2phenotype(individual.genome, params.grammar);
    individual.string=phenotype_string;
    individual.lhs_rep_array=lhs_rep_array;
    individual.lhs_rep_inds_array=lhs_rep_inds_array;
    individual.lhs_rep_type_array=params.grammar.getLHSRepTypeIntArray();
    operator=individual.operator;
    [individual2, temp_child]=ge_subtreexover(individual, temp_ind, params);%Apply crossover
    c_ind1=ge_createIndividual(params, 0);
    c_ind1.genome=individual2.genome(:);
    c_ind1.left_parent=individual2.left_parent;
    c_ind1.right_parent=individual2.right_parent;
    c_ind1.constants=individual2.constants;
    c_ind1.operator=operator;
    c_ind1.mutationoperator=5;
    individual=c_ind1;
end