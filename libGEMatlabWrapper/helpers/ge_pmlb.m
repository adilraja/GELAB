function [size_mat, pops, bests, stats]=ge_pmlb(numCores, fname, data_file)
fid=fopen('pmlb_regression_files.txt');
tline = fgetl(fid);
pops=[];
p=load('pmlb.mat');
params=p.params;
bests=[];
stats=[];
i=1;
size_mat=[];
siz_m=[];

params.hybrid=0;
params.fitnessFunction='ge_evaluate';

if(exist('numCores', 'var'))
    params.numcores=numCores;
    params.numRuns=numCores;
end

if(params.parallel)
    if(isempty(gcp('nocreate')))
        pool=parpool(params.numcores, 'IdleTimeout', 9600);
    else
        delete(gcp);
%         pool = gcp('nocreate');
        pool=parpool(params.numcores, 'IdleTimeout', 9600);
    end
    pctRunOnAll javaaddpath(strcat(fileparts(which('loadGrammar.m')), '/libGEjar/libGEjava.jar'));
else
    javaaddpath(libGEpath);
end

while ischar(tline)
    siz_m=[];
    str=strcat(tline, '_train_x.csv');
    params.data.train_x=csvread(str);
    a=size(params.data.train_x);
    str=strcat(tline, '_train_y.csv');
    y=csvread(str);
    params.data.train_y=y(:);
    b=size(params.data.train_y);
    siz_m=[siz_m a b];
    
    
    str=strcat(tline, '_test_x.csv');
    params.data.test_x=csvread(str);
    a=size(params.data.test_x);
    str=strcat(tline, '_test_y.csv');
    y=csvread(str);
    params.data.test_y=y(:);
    b=size(params.data.test_y);
    siz_m=[siz_m a b];
    size_mat=[size_mat; siz_m];
    
    params=ge_updateNumCoefs(params);
    save('tline.mat', 'tline');
    
     [all_pops, all_bests, all_stats, params]=ge_inaloop(params, 'temp', 1);
    pops{i}=all_pops;
    bests{i}=all_bests;
    stats{i}=all_stats;
    i=i+1;
    
    tline = fgetl(fid);
end
fclose(fid);
size_mat;
if(params.parallel)
    delete(pool);
    pause(5);
end
save('pmlbsim.mat', '-v7.3', 'pops', 'bests', 'stats', 'params');

