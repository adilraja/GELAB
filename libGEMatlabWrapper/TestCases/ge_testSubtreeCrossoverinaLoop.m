function [counter, reasons]=ge_testSubtreeCrossoverinaLoop(params)

libGEpath=strcat(fileparts(which('loadGrammar.m')), '/libGEjar/libGEjava.jar');
% clear java;
javaaddpath(libGEpath);

reasons=zeros(100000,1);
if(~exist('params', 'var'))
    params2=load('keijzerparams.mat');
    params=params2.params;
end


rng;
params.grammar=loadGrammar(params);
params.initMaxDepth=3;
params.grammar.setMaxDepth(7);

counter=0;

for(i=1:100000)
    [retval, p_string1, p_string2, c_string1, c_string2, genome1_str, genome2_str, c_genome1_str, c_genome2_str, ms1, ms2, cms1, cms2, reason]=ge_testSubtreeCrossover(params);
    if(retval==2)
        counter=counter+1;
    end
    reasons(i)=reason;
end