function params=ge_fiddleParams()
%This function keeps all the fiddle params of the GE system and returns a
%variable params. Muhammad Adil Raja, 9th July 2018
params.numRuns=input('Please enter the number of runs.\n');
params.numGens=input('Please enter the number of generations.\n');
params.popSize=input('Please enter the population size.\n');
bnfFile=input('Please enter the name of the BNF file.\n', 's');
params.grammar=loadGrammar(bnfFile);

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

fitness=input('Please enter the name of the fitness function. Your options are: -\n1) 1 - for mean square error.\n2) 2 - for scaled mean squared error\n3) 3 - for Santafe ant trail.\n');
if(fitness==1)
    params.fitnessFunction='ge_mse';
elseif(fitness==2)
    params.fitnessFunction='ge_evaluate';
elseif(fitness==3)
    params.fitnessFunction='ge_antfitness';
else
    params.fitnessFunction='ge_evaluate';
end
params.lowerisbetter=input('Lower is better? Please enter 1 for yes and 0 for no!\n');
