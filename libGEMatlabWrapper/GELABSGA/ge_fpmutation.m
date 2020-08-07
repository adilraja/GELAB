%function individual = ge_mutation(individual, params). This function
%implements fixed bounds, few points mutation. Muhammad Adil Raja, 16th November, 2018.
function individual = ge_fpmutation(individual, params)

% if(contains(ctfroot, 'MATLAB'))
%   % MATLAB is running.
%   rng('shuffle', 'twister');
% end
    genome=individual.genome;
    genome=genome(:);
    glen= length(genome);
    mpv=rand(1,glen);%mutation probability vector
    I=find(mpv>=params.mutationProbability);
    
    xmin=-50;
    xmax=50;
    n=1;
%     perturbation=xmin+rand(1,glen)*(xmax-xmin);
    perturbation=randi([xmin, xmax], glen, 1);
%     perturbation=floor(perturbation);
    perturbation(I)=0;
      perturbation=int32(perturbation);
    genome=genome+perturbation;
    genome=abs(genome);%Only have positive integers here.
%     genome=uint32(genome);
    
    %index1=floor(rand(1)*(glen-1))+1;
    
    %genome(index1)=val1;
    individual.genome=genome;
    individual.mutationoperator=3;
    %genomeSize=size(genome);
    %out = individual;
end