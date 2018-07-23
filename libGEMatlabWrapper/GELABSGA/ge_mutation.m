function individual = ge_mutation(individual)
    genome=individual.genome;
    genome=genome(:);
    glen= length(genome);
    
    xmin=0;
    xmax=2550000;
    n=1;
    val1=xmin+rand(1,n)*(xmax-xmin);
    val1=floor(val1);
    
    index1=floor(rand(1)*(glen-1))+1;
    
    genome(index1)=val1;
    individual.genome=genome;
    %genomeSize=size(genome);
    %out = individual;
end