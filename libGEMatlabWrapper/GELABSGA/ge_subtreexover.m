function [c_ind1, c_ind2, genome1_str, genome2_str, c_genome1_str, c_genome2_str, subtree1s, subtree1e, subtree2s, subtree2e, reason] = ge_subtreexover (ind1, ind2, params)

% if(contains(ctfroot, 'MATLAB'))
%   % MATLAB is running.
%   rng('shuffle', 'twister');
% end

grammar=params.grammar;

c_ind1=[];
c_ind2=[];
genome1_str=[]; 
genome2_str=[]; 
c_genome1_str=[];
c_genome2_str=[];
subtree1s=[];
subtree1e=[];
subtree2s=[];
subtree2e=[];
cms1=[];
cms2=[];

numWraps1=ind1.numWraps;
numWraps2=ind2.numWraps;

genome1=ind1.genome(:);
genome2=ind2.genome(:);

subtree1genome=[];
subtree2genome=[];

if(numWraps1>0)
    for(i=1:numWraps1)
        genome1=cat(1, genome1, ind1.genome(:));
    end
end
if(numWraps2>0)
    for(i=1:numWraps2)
        genome2=cat(1, genome2, ind2.genome(:));
    end
end

gl_1=length(genome1);
gl_2=length(genome2);

lhs_rep_inds_array1=ind1.lhs_rep_inds_array;
lhs_rep_array1=ind1.lhs_rep_array;

lhs_rep_inds_array2=ind2.lhs_rep_inds_array;
lhs_rep_array2=ind2.lhs_rep_array;

% [lhs_rep_inds_array1, I1]=sort(ind1.lhs_rep_inds_array);
% [lhs_rep_inds_array2, I2]=sort(ind2.lhs_rep_inds_array);


% lhs_rep_array1=ind1.lhs_rep_array;
% lhs_rep_array2=ind2.lhs_rep_array;

lhs_rep_type_array1=ind1.lhs_rep_type_array;
lhs_rep_type_array2=ind2.lhs_rep_type_array;

lhs_max_length1=lhs_rep_array1+lhs_rep_inds_array1;
lhs_max_length2=lhs_rep_array2+lhs_rep_inds_array2;

I1=find(lhs_max_length1<=length(genome1));
I2=find(lhs_max_length2<=length(genome2));

reduced_lhs_rep_type_array1=lhs_rep_type_array1(I1);
reduced_lhs_rep_type_array2=lhs_rep_type_array2(I2);

reduced_lhs_rep_inds_array1=lhs_rep_inds_array1(I1);
reduced_lhs_rep_inds_array2=lhs_rep_inds_array2(I2);

reduced_lhs_rep_array1=lhs_rep_array1(I1);
reduced_lhs_rep_array2=lhs_rep_array2(I2);

lhs_types1=unique(reduced_lhs_rep_type_array1);
lhs_types2=unique(reduced_lhs_rep_type_array2);

common_types=intersect(lhs_types1, lhs_types2);

if(isempty(common_types))
    [c_ind1, c_ind2] = ge_spcrossover (ind1, ind2, params);
    c_ind1.operator=5;
    c_ind2.operator=5;
    reason=1;
    return;
end

target_type_index=randperm(length(common_types));
target_type_index=target_type_index(1);
target_type=common_types(target_type_index(1));



if(~isempty(I1) && ~isempty(I2))
    
    genome1=genome1(:);
    genome2=genome2(:);
    
   
%     str=grammar.getMappingSequence();
%     disp(str);
    
    tI1=find(reduced_lhs_rep_type_array1==target_type);
    tI2=find(reduced_lhs_rep_type_array2==target_type);
    
    subtree1i=randi(length(tI1),1);
    subtree2i=randi(length(tI2),1);
    
    subtree1s=reduced_lhs_rep_inds_array1(tI1(subtree1i));
    subtree2s=reduced_lhs_rep_inds_array2(tI2(subtree2i));

    subtree1e=subtree1s+reduced_lhs_rep_array1(tI1(subtree1i))-1;
    subtree2e=subtree2s+reduced_lhs_rep_array2(tI2(subtree2i))-1;
    
    subtree1genome=genome1(subtree1s:subtree1e);
    subtree2genome=genome2(subtree2s:subtree2e);
    
    
    c_genome1=[genome1(1:subtree1s-1); genome2(subtree2s:subtree2e); genome1(subtree1e+1:length(genome1))];
    c_genome2=[genome2(1:subtree2s-1); genome1(subtree1s:subtree1e); genome2(subtree2e+1:length(genome2))];
    
%     genome1_str=strcat(num2str(genome1(1:subtree1s-1))', 's', num2str(subtree1genome)', 'e', num2str(genome1(subtree1e+1:length(genome1)))');
%     genome2_str=strcat(num2str(genome2(1:subtree2s-1))', 's', num2str(subtree2genome)', 'e', num2str(genome2(subtree2e+1:length(genome2)))');
%     
%     c_genome1_str=strcat(num2str(genome1(1:subtree1s-1))', 's', num2str(subtree2genome)', 'e', num2str(genome1(subtree1e+1:length(genome1)))');
%     c_genome2_str=strcat(num2str(genome2(1:subtree2s-1))', 's', num2str(subtree1genome)', 'e', num2str(genome2(subtree2e+1:length(genome2)))');
    
    c_ind1=ge_createIndividual(params, 0);
%     cms1=params.grammar.getMappingSequence();

    
    c_ind2=ge_createIndividual(params, 0);
%     cms2=params.grammar.getMappingSequence();

    c_ind1.genome=c_genome1;
    c_ind2.genome=c_genome2;

    c_ind1.left_parent=ind1.ID;
    c_ind1.right_parent=ind2.ID;

    c_ind1.constants=ind1.constants;
    c_ind2.constants=ind2.constants;

    c_ind2.left_parent=ind2.ID;
    c_ind2.right_parent=ind1.ID;
    reason=2;

   
else
    [c_ind1, c_ind2] = ge_spcrossover (ind1, ind2, params);
    reason=3;
end
    c_ind1.operator=6;
    c_ind2.operator=6;

end

