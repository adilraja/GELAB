function [pop, numValid]=ge_evalPop(pop, params)
    popsize=length(pop);
    j=0;
    for(i=1:popsize)
        if(pop(i).valid==1 && pop(i).isEvaluated==0)
            pop(i)=feval(params.fitnessFunction, pop(i), params);
            pop(i).isEvaluated=1;
            
        elseif(pop(i).valid==0)
            individual.fitness=50000;
            if(params.data.test)
                individual.testFitness=500000;
            end
        end
        if(pop(i).valid==1)
            j=j+1;
        end
    end
    numValid=j;
    disp('Returning from evalPop');
end