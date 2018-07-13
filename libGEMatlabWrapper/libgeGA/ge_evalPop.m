function pop=ge_evalPop(pop, params)
    popsize=length(pop);
    for(i=1:popsize)
        pop(i)=feval(params.fitnessFunction, pop(i), params.data);
    end
end