function ge_mfrp();

load('mfrpparams.mat');
params.popSize=500;
params.numcores=2;
params.numRuns=2;
params.numGens=50;

params.data.train_x=load('train_mfrp_x.txt');
params.data.train_y=load('train_mfrp_y.txt');

params.data.test_x=load('train_mfrp_x.txt');
params.data.test_y=load('train_mfrp_y.txt');

params.fitnessFunction='ge_minimizeErrorVariance';

[all_pops, all_bests, all_stats, params]=ge_inaloop(params, 'mfrpresults', 0);
