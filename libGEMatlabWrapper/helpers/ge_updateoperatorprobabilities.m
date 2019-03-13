%function params=ge_updateoperatorprobabilities(population, params). As the
%name suggests, this function computes the operator probabilities for
%various genetic operators. Written by Muhammad Adil Raja, 15th November,
%2018.
function params=ge_updateoperatorprobabilities(population, params)

fitness_vector=[];
operator_vector=[];
popSize=length(population);
for(i=1:popSize)
    fitness_vector(i)=population(i).fitness;
    operator_vector(i)=population(i).operator;
end

total_operators=4;
sum_prob_all_ops=0;
operator_probability=zeros(4,1);
for(i=1:total_operators)
    I=find(operator_vector==i);
    fitness_proportion=sum(fitness_vector(I))/sum(fitness_vector);
    if(params.lowerisbetter)
        operator_probability(i)=1-fitness_proportion;
    else
        operator_probability(i)=fitness_proportion;
    end 
end

if(params.lowerisbetter)
    sum_prob_all_ops=sum(operator_probability);
else
    sum_prob_all_ops=1;
end

for(i=1:total_operators)
    switch i
        case 1
            params.spxoverp=operator_probability(i)/sum_prob_all_ops;%The denominotor does not make any difference if lower is not better, its '1' in that case anyways.
        case 2
            params.vpxoverp=operator_probability(i)/sum_prob_all_ops;
        case 3
            params.weavep=operator_probability(i)/sum_prob_all_ops;
        case 4
            params.tweavep=operator_probability(i)/sum_prob_all_ops;
    end
end
