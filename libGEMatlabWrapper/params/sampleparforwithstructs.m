function [a, b, c]=sampleparforwithstructs

p=struct('age', [], 'gender', [], 'dateofbirth', []);
    a1=repmat(p, [params.numRuns, params.popSize]);
    b1=repmat(p, [params.numRuns, 1]);
    c1=repmat(all_stats, [params.numRuns, 1]);
    
     parfor(i=1:50, 2)
        [pop(i, :), best(i), stats2(i)]=feval(params.ga_fcn, params);
        bestfithistory(:,i)=stats2(i).bestfithistory;
        testfithistory(:, i)=stats2(i).testfithistory;
        meanfithistory(:, i)=stats2(i).meanfithistory;
        timehistory(:, i)=stats2(i).timehistory;
        numvalidhistory=stats2(i).numvalidhistory;
        diversityhistory=stats2(i).numvalidhistory;
        all_pops=[all_pops; pop(i)];
        all_bests=[all_bests; best(i)];
    end