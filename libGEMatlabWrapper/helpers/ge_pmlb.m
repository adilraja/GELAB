function [size_mat, pops, bests, stats]=ge_pmlb(fname, data_file)
fid=fopen(data_file);
tline = fgetl(fid);
pops=[];
p=load('pmlb.mat');
params=p.params;
bests=[];
stats=[];
i=1;
size_mat=[];
siz_m=[];
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
    
     [all_pops, all_bests, all_stats, params]=ge_inaloop(params, 'temp');
    pops{i}=all_pops;
    bests{i}=all_bests;
    stats{i}=all_stats;
    i=i+1;
    
    tline = fgetl(fid);
end
fclose(fid);
size_mat;

save(fname, 'pops', 'bests', 'stats', 'params');

