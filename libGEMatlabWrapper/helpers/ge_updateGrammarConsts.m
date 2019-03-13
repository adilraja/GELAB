function params=ge_updateGrammarConsts(params)

for(i=1:params.numCoefs)
    str=strcat('w(', num2str(i), ')');
    params.grammar.setConsts(str);
end