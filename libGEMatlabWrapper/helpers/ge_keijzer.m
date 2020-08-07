function [size_mat, pops, bests, stats]=ge_keijzer(fname, called_external, params)
% fid=fopen(data_file);
% tline = fgetl(fid);
pops=[];
if(~called_external)
    p=load('keijzerparams.mat');
    params=p.params;
end
bests=[];
stats=[];
i=1;
size_mat=[];
siz_m=[];
if(~called_external)
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
end
tline='keijzer';

for(ii=1:6)
    siz_m=[];
    str=strcat(tline, num2str(ii), '_train_x.txt');
    params.data.train_x=load(str);
    a=size(params.data.train_x);
    str=strcat(tline, num2str(ii), '_train_y.txt');
    y=load(str);
    params.data.train_y=y(:);
    b=size(params.data.train_y);
    siz_m=[siz_m a b];
    
    
    str=strcat(tline, num2str(ii), '_test_x.txt');
    params.data.test_x=load(str);
    a=size(params.data.test_x);
    str=strcat(tline, num2str(ii), '_test_y.txt');
    y=load(str);
    params.data.test_y=y(:);
    b=size(params.data.test_y);
    siz_m=[siz_m a b];
    size_mat=[size_mat; siz_m];
    
    params=ge_updateNumCoefs(params);
%     save('tline.mat', 'tline');
    
     [all_pops, all_bests, all_stats, params]=ge_inaloop(params, 'temp', 1);
    pops{i}=all_pops;
    bests{i}=all_bests;
    stats{i}=all_stats;
    i=i+1;
    
%     tline = fgetl(fid);
end
% fclose(fid);
size_mat;
if(~called_external)
    if(params.parallel)
        delete(pool);
        pause(5);
    end
    save(fname, 'pops', 'bests', 'stats', 'params');
end

