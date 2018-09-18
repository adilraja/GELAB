 function individual = ge_mutation(individual, params)
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
    %genomeSize=size(genome);
    %out = individual;
end