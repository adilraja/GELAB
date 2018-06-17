function grammar=loadGrammar(bnffile)
%This function loads a grammar for a particular domain such as symbolic
%regression, classification, Santa Fe Ant Trail and so on. All you have to
%do is to simply provide the file name of the grammar as input and this
%function will do the rest. But please make sure that the bnf file is lying
%in the grammars directory. Input: bnffile (BNF file), output: grammar (a
%java object). This function is written by Muhammad Adil Raja on 25th May,
%2018.

clear JAVA;

%fileparts(which('loadGrammar.m')), 
libGEpath=strcat(fileparts(which('loadGrammar.m')), '/libGEjar/libGEjava.jar');
javaaddpath(libGEpath);
%javaclasspath;
%fileparts(which('loadGrammar.m')),
bnffilepath=strcat(fileparts(which('loadGrammar.m')), '/grammars/', bnffile);
bnffilepath2=javaObject('java.lang.String', bnffilepath);
grammar=javaObject('libGEjava.GEGrammarSI');

grammar.setMaxWraps(9);
GrammarFile = grammar.readBNFFile(bnffilepath2);
disp('Grammar File');
disp(GrammarFile);
% if grammar.readBNFFile('grammars/sr.bnf')
%     genoSample(1:10) = [1 4 2 5 1 6 3 1 2 8];
%     gen2phen = genotype2phenotype(genoSample,grammar);
%     disp(gen2phen);
% else
%     System.out.println('Reading of the grammar file was not successful\n');
% end
% genotype2phenotype.m class function should be called here, and integer
% array of random numbers as geno and the grammar javaObject should
% be passed as an argument to make it work properly!!! @Qadeer Ahmad

%return grammar;
