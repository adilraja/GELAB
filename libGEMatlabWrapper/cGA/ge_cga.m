function [pop, best, stats3, params]=ge_cga(params, runNumber)
%This function runs GE using the compact genetic algorithm.
%This function is written by Muhammad Adil Raja, 15, July, 2018

 if(exist('params', 'var')==0)
    disp('The right parameters have not been specified to run GELAB in ge_main.\n')
 end
%Load a statistics object. We are going to need it to keep track of
%various things.
stats3=ge_statistics();
    
genome_length=params.genome_length;

%Create the parent population
pop=ge_initUniqueValidPopUsingSensibleInit(params);
pop=ge_evalPop(pop, params);

%Now create the child population
childPop=ge_createChildPopulation(pop, params);
childPop=ge_genotype2phenotypeWholePop(childPop, params);
childPop=ge_evalPop(childPop, params);

%Now compute the probability distribution for cGA
[probability_matrix, genome_length]=ge_computePDFcga([pop childPop], genome_length, 1);

%Now apply replacement
parentPop=ge_replacement(pop, childPop, params);

%Now apply the main EC loop
for(i=1:params.numGens)
       tic;
       childPop = ge_cGACreateChildPopulation(probability_matrix, params);
       childPop=ge_genotype2phenotypeWholePop(childPop, params);
       childPop=ge_evalPop(childPop, params);
       %Now compute the probability distribution for cGA again
       probability_matrix2=ge_computePDFcga([parentPop childPop], genome_length, 0);
       probability_matrix=(probability_matrix+probability_matrix2)./2;%Compute the mean here assuming that the mean of two Gaussians means and variances is also Gaussian
       parentPop=ge_replacement(parentPop, childPop, params);
       disp(parentPop(1).fitness);
       %pause(3);
       stats3=ge_computeStatistics(stats3, parentPop, params);
       disp('The run-number is: ');
       disp(runNumber);
       disp('And the generation-number is: ');
       disp(i);
       stats3.timehistory=[stats3.timehistory; toc];
end
    best=pop(1);
end

