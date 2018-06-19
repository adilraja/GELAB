%This is the main file to run ge.
function [pop, best]=ge_main(numgens, popsize, data, genome_length)
    if(exist('numgens', 'var')==0)
        numgens=150;
    end
    if(exist('popsize', 'var')==0)
        popsize=1000;
    end
    if(exist('data', 'var')==0)
        data=ge_load_dataset('trainingDataX.txt', 'trainingDataY.txt', 'testingDataX.txt', 'testingDataY.txt');
    end
    if(exist('genomelength', 'var')==0)
        genome_length=3200;
    end
    
    %Load the grammar, you are going to need it.
    grammar=loadGrammar('sr.bnf');
    pop=ge_initPop(popsize, genome_length, grammar, 1);
    pop=ge_evalPop(pop, data);
    
    
    
    for(i=1:numgens)
       childPopulation=ge_createChildPopulation(pop, genome_length, grammar);
       childPopulation=ge_genotype2phenotypeWholePop(childPopulation);
       childPop=ge_evalPop(childPopulation, data);
       pop=ge_replacement(pop, childPop);
       
    end
end