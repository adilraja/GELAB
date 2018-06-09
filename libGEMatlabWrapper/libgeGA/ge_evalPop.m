function pop=ge_evalPop(pop, data)
    popsize=length(pop);
    for(i=1:popsize)
        pop(i).fitness=ge_evaluate(pop(i), data);
    end
end