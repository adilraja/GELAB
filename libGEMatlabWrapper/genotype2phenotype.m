%import libGEjava.*;

function pheno=genotype2phenotype(geno, grammar)
%This function does the mapping from genotype to phenotype. It calls
%libGE's jar and gets its work done.
% Inputs:
%   geno: genotype (integer array)
%   grammar: A grammar (java) object, possibly returned from loadGrammar.m
%Output:
%   pheno: phenotype (string)

libGEpath=strcat(pwd, "/libGEjar/GrammaticOptimization.jar");

javaaddpath(libGEpath);
javaclasspath;

grammar.setGenotype(geno, length(geno));

try{
    grammar.genotype2phenotype(true);
}
catch(java.lang.Exception e){
    System.out.println(e+"In Main");
}
catch(java.lang.NoClassDefFoundError e){
    e.printStackTrace();
}
pheno=grammar.phenotypetoString();