function pop=ge_evalPop(pop)
    popsize=length(pop);
    for(i=1:popsize)
        pop(i).fitness=ge_evaluate(pop(i));
    end
end