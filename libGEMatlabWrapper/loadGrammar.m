function grammar=loadGrammar(bnffile)
%This function loads a grammar for a particular domain such as symbolic
%regression, classification, Santa Fe Ant Trail and so on. All you have to
%do is to simply provide the file name of the grammar as input and this
%function will do the rest. But please make sure that the bnf file is lying
%in the grammars directory. Input: bnffile (BNF file), output: grammar (a
%java object). This function is written by Muhammad Adil Raja on 25th May,
%2018.

libGEpath=strcat(pwd, "/libGEjar/libGEjava.jar");
javaaddpath(libGEpath);
javaclasspath;

bnffilepath=strcat(pwd, "/grammars/bnffile");
grammar=javaObject("libGEjava.GEGrammar");

grammar.setMaxWraps(9);
if(grammar.readBNFFile("grammars/sr.bnf")) {
 } 
else {
    System.out.println("Reading of the grammar file was not successful\n");
}
%return grammar;
