function [pop, params]=ge_evalMultipleTreePop(pop, params)
    popSize=length(pop);
    [nrows, ncols]=size(params.data.train_y);
    
    for(i=1:popSize)
        pop(i).result=zeros(nrows, ncols);
        pop(i)=ge_evalMultipleTrees(pop(i), params);
        fitness=0;
        valid=0;
        for(j=1:length(pop(i).ind))
            fitness=fitness+pop(i).ind(j).fitness;
            if(pop(i).ind(j).valid==1)
                if(length(pop(i).ind(j).result)~=nrows)
                    pop(i).result(:, j)=ones(nrows, 1)*params.maxBadFitness;
                else
                    pop(i).result(:,j)=pop(i).result(:, j)+pop(i).ind(j).result;
                end
                valid=valid+1;
            else
                pop(i).result(:, j)=ones(nrows, 1)*params.maxBadFitness;
            end
        end
        pop(i).fitness=mean(fitness);%This is the ensembles fitness, to be used in replacement
        pop(i).valid=valid;
    end
end