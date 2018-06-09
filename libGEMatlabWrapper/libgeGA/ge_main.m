%This is the main file to run ge.
function [pop, best]=ge_main(numgens, popsize, data)
    
    %Load the grammar, you are going to need it.
    grammar=loadGrammar('sr.bnf');
    pop=ge_initPop(popsize, grammar);
    pop=ge_evalPop(pop, data);
    
    for(i=1:numgens)
       childPopulation=createChildPopulation(population);
       childPopulation=ge_evalPop(childPopulation, data);
       population=ge_replacement(population, childPopulation);
    end
end