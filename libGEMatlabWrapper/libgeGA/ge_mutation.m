function [out,val1,val2] = ge_mutation(individual)
    genome=individual.genome;
    [r,c] = size(genome);
    
    xmin=0;
    xmax=255;
    n=1;
    val1=xmin+rand(1,n)*(xmax-xmin);
    val1=int16(fix(val1));

    val2=xmin+rand(1,n)*(xmax-xmin);
    val2=int16(fix(val2));
    
    row=floor(rand(1)*(r-1))+1;
    col=floor(rand(1)*(c-1))+1;

    
    genome(row, col)=val1;
    individual.genome=genome;
    genomeSize=size(genome);
    out = individual;
end