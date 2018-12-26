function params=ge_fiddleParams()
%This function keeps all the fiddle params of the GE system and returns a
%variable params. Muhammad Adil Raja, 9th July 2018

params.numRuns=input('Please enter the number of runs.\n');
params.numGens=input('Please enter the number of generations.\n');
params.popSize=input('Please enter the population size.\n');
params.bnfFile=input('Please enter the name of the BNF file.\n', 's');
%params.grammar=loadGrammar(bnfFile);

trainx_filename=input('Please enter the training data file name for input variables.\n', 's');
trainy_filename=input('Please enter the training data file name for target variable.\n', 's');

test_yes_no=input('Do you want to specify test data? [Y/N]', 's');
if(strcmpi(test_yes_no, 'n'))
    params.data=ge_load_dataset(trainx_filename, trainy_filename);
else
    testx_filename=input('Please enter the test data file name for input variables.\n', 's');
    testy_filename=input('Please enter the test data file name for target variable.\n', 's');
    params.data=ge_load_dataset(trainx_filename, trainy_filename, testx_filename, testy_filename);
end
[x, numMultipleTrees]=size(params.data.train_y);
params.numMultipleTrees=numMultipleTrees;
params.adaptiveProbs=input('Do you want to use adaptive operator probabilities? (0 or 1/ no or yes)\n');

hybrid_yes_no=input('Do you want to perform hybrid optimization? [Y/N]', 's');

if(strcmpi(hybrid_yes_no, 'y'))
   params.hybrid=1;
   params.fitnessFunction='ge_hybrid';
   
   numCoefs=input('Please enter the number of coefficients for hybrid optimzation.\nPlease make sure that symbols for those coefficients should be provided in the grammar file as w(1),. w(2), ..., w(n).\n');
   params.numCoefs=numCoefs;
   UB=input('Please specify the upper bound for coefficients.\n');
   params.UB=abs(UB);
   params.LB=-1*UB;
   optialgo=input('Please specify which algorithm you want to use for optimization.\n(1) for simulated annealing.\n(2) for genetic algorithms.\n(3) for swarm optimization.\n(4) for least squares using Levenberg Marquardt.\n(5) Unconstrained optimization using Qausi-Newton method.\n');
   switch optialgo
       case 1
           params.hybridAlgorithm='sa';
       case 2
           params.hybridAlgorithm='ga';
       case 3
           params.hybridAlgorithm='pso';
       case 4
           params.hybridAlgorithm='lsq';
       case 5
           params.hybridAlgorithm='fminuncqs';
       otherwise
           params.hybridAlgorithm='sa';
   end
else
    params.hybrid=0;
    fitness=input('Please enter the name of the fitness function. Your options are: -\n1) 1 - for mean square error.\n2) 2 - for scaled mean squared error\n3) 3 - for Santafe ant trail.\n');
    if(fitness==1)
        params.fitnessFunction='ge_mseonly';
    elseif(fitness==2)
        params.fitnessFunction='ge_evaluate';
    elseif(fitness==3)
        params.fitnessFunction='ge_antfitness';
    else
        params.fitnessFunction='ge_evaluate';
    end
end

ga_type=input('Please enter the type of GA that you would like to use\n1) 1 for simple GA.\n2) 2 for compact GA.\n3) 3 for MIMO GE using simple GA.\n');
if(ga_type==1)
    params.ga_fcn='ge_main';
    params.testFitnessFunction='ge_computeTestFitness';
elseif(ga_type==2)
    params.ga_fcn='ge_cga';
    params.testFtinessFunction='ge_computeTestFitness';
elseif(ga_type==3)
    params.ga_fcn='ge_multipletreesmain';
    params.testFitnessFunction='ge_computeMultipleTreeTestFitness';
end

params.hffs=input('Do you want to use hierarchical fitness functions? (0 for no, 1 for yes).\n');
if(params.hffs==1)
    params.fitnessFunction='ge_alhf';
end

params.lowerisbetter=input('Lower is better? Please enter 1 for yes and 0 for no!\n');

params.genome_length=input('Please enter a value for genome length.\nEnter a small value for Santafe (50-100).\nEnter a large value for symbolic regression (150-300).\n');
params.parallel=input('Do you want to run GELAB on parallel computing toolbox?\n 1) 1 for yes. 2) 0 for no.\n');
if(params.parallel~=1)
    params.parallel=0;
else
    params.numcores=input('How many cores do you want to dedicate for parallel computing?\n');
end

params=ge_defaultParams(params);%Load default parameters too.



