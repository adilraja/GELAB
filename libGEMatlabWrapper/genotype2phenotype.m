%import libGEjava.*;
function pheno=genotype2phenotype(geno, grammar)
%This function does the mapping from genotype to phenotype. It calls
%libGE's jar and gets its work done.
% Inputs:
%   geno: genotype (integer array)
%   grammar: A grammar (java) object, possibly returned from loadGrammar.m
%Output:
%   pheno: phenotype (string)


%-----------------------------------------------------------------
%geno was double type array so I converted it into integer type
geno = uint8(geno);
disp(geno);
%To check geno & grammar data type
disp(class(geno));
disp(class(grammar));

libGEpath=strcat(pwd, '/libGEjar/GrammaticOptimization.jar');
javaaddpath(libGEpath);
javaclasspath;

% Just to display the list of all the methods in GEGrammar
%methodsview libGEjava.GEGrammar;

%----------------------------------------
%Method not Found: setGenotype: Error Message: No method 'setGenotype' with matching signature found for class 'libGEjava.GEGrammar'.
%----------------------------------------
grammar.setGenotype(geno, length(geno));
try
    grammar.genotype2phenotype(true);
catch E
    switch E.identifier
        case 'MATLAB:java.lang.Exception'
            fprintf('Caught this: In Main: %s\n',getReport(E));
        case 'MATLAB:java.lang.NoClassDefFoundError'
            %E.printStackTrace();
            fprintf('Caught this: printStackTrace: %s\n',getReport(E));
    end
end
pheno=grammar.phenotypetoString();
end