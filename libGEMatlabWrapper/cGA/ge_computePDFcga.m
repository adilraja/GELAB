function [probability_matrix, genome_length]=ge_computePDFcga(population, genome_length, recompute_genome_length)
%This function computes the probability distribution of the CGA. Written by
%Muhammad Adil Raja, 15th July, 2018
%adjust genome length
popSize=length(population);

if(recompute_genome_length)
    max_len=0;
    for(i=1:popSize)
        cgl=length(population(i).genome);
        if(cgl>max_len)
            max_len=cgl;
        end
    end
    
    if(max_len>genome_length)
        genome_length=max_len;
    end
end

%population=[parent_population child_population];
pop_genomes=zeros(popSize, genome_length);

j=1;
for(i=1:popSize)
    if(population(i).valid)
        pop_genomes(j, 1:length(population(i).genome))=population(i).genome;%Copy the genomes of the whole population
        j=j+1;
    end
end

probability_matrix=zeros(genome_length, 2);

%Compute the PDF and return,
probability_matrix(:, 1)=mean(pop_genomes(1:j-1, :));%The first row contains the means
probability_matrix(:, 2)=std(pop_genomes(1:j-1, :));%The second row contains the standard deviations.

%The above was for non-zero entries. For zero entries, do the following.
I=find(probability_matrix(:, 1)==0);
probability_matrix(I, 1)=mean(probability_matrix(1,:));%Assign the mean of means to the zero entries

I=find(probability_matrix(:, 2)==0);
probability_matrix(I, 2)=mean(probability_matrix(2,:));%Assign the mean of deviations to the zero entries
