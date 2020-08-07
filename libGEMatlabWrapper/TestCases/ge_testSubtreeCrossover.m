function [retval, p_string1, p_string2, c_string1, c_string2, genome1_str, genome2_str, c_genome1_str, c_genome2_str, ms1, ms2, cms1, cms2, reason]=ge_testSubtreeCrossover(params)


grammar=params.grammar;

p_string1=[];
p_string2=[];
c_string1=[];
c_string2=[];
genome1_str=[];
genome2_str=[];
c_genome1_str=[];
c_genome2_str=[];
ms1=[];
ms2=[];
cms1=[];
cms2=[];

retval=0;

for(i=1:7)
    str=strcat('X(:,', num2str(i), ')');
    params.grammar.setVars(str);
end

for(i=1:9)
    str=strcat('w(', num2str(i), ')');
    params.grammar.setConsts(str);
end

individual1 = ge_createIndividual(params, 1);
ms1=params.grammar.getMappingSequence();
individual2 = ge_createIndividual(params, 1);
ms2=params.grammar.getMappingSequence();

ms1toks=strsplit(convertCharsToStrings(char(ms1)), '|');
ms2toks=strsplit(convertCharsToStrings(char(ms2)), '|');

if(isempty(ms1toks) || isempty(ms2toks))
    retval=0;
    return;
end


[c_ind1, c_ind2, genome1_str, genome2_str, c_genome1_str, c_genome2_str, subtree1s, subtree1e, subtree2s, subtree2e, reason] = ge_subtreexover(individual1, individual2, params);
[tmp grammar]=genotype2phenotype(c_ind1.genome, params.grammar);
cms1=grammar.getMappingSequence();
[tmp grammar]=genotype2phenotype(c_ind2.genome, params.grammar);
cms2=grammar.getMappingSequence();


if(isempty(subtree1s) || isempty(subtree2s))
    retval=0;
    return;
end
% ms1toks
% ms1seg=ms1toks{3:end}
ms1seg=ms1toks((subtree1s+1):subtree1e);
ms2seg=ms2toks((subtree2s+1):subtree2e);

cms1toks=strsplit(convertCharsToStrings(char(cms1)), '|');
cms2toks=strsplit(convertCharsToStrings(char(cms2)), '|');

if(isempty(cms1toks) || isempty(cms2toks))
    retval=0;
    return;
end

cms1seg=cms1toks((subtree1s+1):(subtree1s+(subtree2e-subtree2s)));
cms2seg=cms2toks((subtree2s+1):(subtree2s+(subtree1e-subtree1s)));

if(length(ms1seg)==length(cms2seg) && length(ms2seg) == length(cms1seg))
    disp('lengths are equal');
    retval=1;
end

counter1=0;
counter2=0;
if(retval==1)
    for(i=1:length(ms1seg))
        if(strcmpi(ms1seg(i), cms2seg(i)))
            counter1=counter1+1;
        end
    end
%     counter1=counter1+1;
    for(i=1:length(ms2seg))
        if(strcmpi(ms2seg(i), cms1seg(i)))
            counter2=counter2+1;
        end
    end
%     counter2=counter2+1;
end
% counter1
% counter2
if(counter1==length(ms1seg) && counter2==length(ms2seg))
    retval=2;
end

p_string1=individual1.string;
p_string2=individual2.string;

c_string1 =genotype2phenotype(c_ind1.genome, grammar);
c_string2 =genotype2phenotype(c_ind2.genome, grammar);

