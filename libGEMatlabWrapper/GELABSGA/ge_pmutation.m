%function individual = ge_pmutation(individual, params). This function implements point mutation. Written 
%by Muhammad Adil Raja. 16th, November, 2018
function individual = ge_pmutation(individual, params)

% if(contains(ctfroot, 'MATLAB'))
%   % MATLAB is running.
%   rng('shuffle', 'twister');
% end
    genome=individual.genome;
    genome=genome(:);
    glen= length(genome);
    point=ceil(rand(1)*glen);%mutation point
    
    xmax=50;
    perturbation=floor(rand(1)*2*xmax-xmax);
    genome(point)=abs(genome(point)+perturbation);
    %Only have positive integers here.
    individual.genome=genome;
    individual.mutationoperator=2;
    
end