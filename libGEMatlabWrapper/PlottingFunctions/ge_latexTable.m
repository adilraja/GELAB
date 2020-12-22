function data_mat=ge_latexTable(stats, fname, varargin);


[x,y]=size(stats);
nargs=length(varargin);

data_mat=zeros(x*y, nargs);
k=1;

for(k=1:nargs)
    switch lower(varargin{k})
        case 'f'
            for(i=1:y)
                for(j=1:x)
                    score_f=(1+stats{j, i}.bestfithistory(end, :));
                    mean_f=mean(score_f);
                    data_mat(i*j, k)=mean_f;
                end
            end
        case 'tf'
            for(i=1:y)
                for(j=1:x)
                    score_f=(1+stats{j, i}.testfithistory(end, :));
                    mean_f=mean(score_f);
                    data_mat(i*j, k)=mean_f;
                end
            end
        case 'diversity'
            for(i=1:y)
                for(j=1:x)
                    score_f=(1+stats{j, i}.diversityhistory(end, :));
                    mean_f=mean(score_f);
                    data_mat(i*j, k)=mean_f;
                end
            end
        otherwise
            error(['Unexpected option: ' varargin{k}]);
    end     
end
ge_tablatex(data_mat, fname);
end