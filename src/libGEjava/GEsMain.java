/*
 * GEsMain.java
 *
 * Created on August 4, 2007, 5:31 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package libGEjava;

/**
 *
 * @author adilraja
 */
import java.util.*;




public class GEsMain{
    
    /** Creates a new instance of GEsMain */
    public GEsMain() {
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws java.lang.Exception{
        // TODO code application logic here
    //    try{
    //    String current = new java.io.File( "." ).getCanonicalPath();
    //    System.out.println("Current dir:"+current);
    //    }
    //   catch(java.io.IOException e){
    //        e.printStackTrace();
    //    }
    int[] newArray={ 2, 1, 1, 0, 0, 1, 4, 3, 44, 1, 2, 0, 3, 44, 3, 44, 2, 2, 1, 0, 0, 3, 44, 2, 3, 44, 2, 2, 2, 1, 3, 44, 3, 44, 2, 2, 3, 44, 3, 44};
        Random rand=new Random();
        
        
        
        Genotype geno=new Genotype(newArray, newArray.length, true,10);
        

        GEGrammarSI grammar=new GEGrammarSI();
        grammar.setGenotype(geno);
     //   grammar.setGenotype(geno);
     GEGrammarSI grammar3;
    

        grammar.setMaxWraps(9);
        grammar.setMaxDepth(6);
        

        if(grammar.readBNFFile("/home/adil/Dropbox/UL/ULPostdoc/GELAB/grammars/sr.bnf")) {
        } else {
            System.out.println("Reading of the grammar file was not successful\n");
        }
        //grammar.init(1);
        try{
            grammar.genotype2phenotype(true);
        }
        catch(java.lang.Exception e){
            System.out.println(e+"In Main");
        }
        catch(java.lang.NoClassDefFoundError e){
            e.printStackTrace();
        }
        
       
        //grammar.setPhenotype(new Phenotype());
         try{
           //  grammar.setPhenotype(grammar.getPhenotype());
        grammar3=new GEGrammarSI(grammar);
     }
     catch(java.lang.NullPointerException e){
         e.printStackTrace();
     }
        Tree tmpTree=grammar.derivationTree;
        Iterator<Symbol> symbIt=null;
        try{
            symbIt=grammar.getPhenotype().iterator();
        }
        catch(java.lang.NullPointerException e){
            e.printStackTrace();
        }
        
        Iterator<Rule> ruleIt=grammar.iterator();
        System.out.println("Here are the results: phenotype size= "+grammar.getPhenotype().size());
        while(symbIt.hasNext()){
            System.out.print(symbIt.next().getSymbol());
        }
        
        System.out.println("\n\nHere is the grammar\n");
        String tmpStr;
        while(ruleIt.hasNext()){
            Rule tmpRule=ruleIt.next();
            System.out.print(tmpRule.lhs.get(0).getSymbol()+"::=");
            Iterator<Production> prodIt=tmpRule.iterator();
            while(prodIt.hasNext()){
                Iterator<Symbol> symbIt2=prodIt.next().iterator(); 
                while(symbIt2.hasNext()){
                    tmpStr=symbIt2.next().getSymbol();
                //    if(tmpStr.equalsIgnoreCase(" ") || tmpStr.equalsIgnoreCase("")){
                //        symbIt2.remove();
                //    }
               //     else{
                        System.out.print(tmpStr);
                //    }
                    
                }
                System.out.print("|");
            }
            System.out.println();
        }
        
        Symbol symb=new Symbol();
        System.out.println(symb.getType().toString());
        symb.setType(SymbolType.NTSymbol);
        System.out.println(symb.getType().toString());
        
        ruleIt=grammar.iterator();
        System.out.println("\n\nHere is the grammar's NT/T info");
        Symbol tmpSymb23=null;
        while(ruleIt.hasNext()){
            Rule tmpRule=ruleIt.next();
            System.out.print("\n"+tmpRule.lhs.get(0).getType().toString()+"::=");
            Iterator<Production> prodIt=tmpRule.iterator();
            
            while(prodIt.hasNext()){
                Iterator<Symbol> symbIt2=prodIt.next().iterator();
                
                while(symbIt2.hasNext()){
                    tmpSymb23=symbIt2.next();
                    System.out.print(tmpSymb23.getType().toString()+"("+tmpSymb23.getSymbol() +") ");
                }
                System.out.print("|");
            }
        }
        if(grammar.phenotype.getValid()==true)
            System.out.println("\nThe above phenotype is valid");
        else 
            System.out.println("\nThe above phenotype is not valid");
        int loopC=grammar.getPhenotype().size();
        Iterator<Symbol> symbIt3=grammar.getPhenotype().iterator();
        for(int i=0;i<loopC;i++){
            System.out.print(symbIt3.next().getSymbol()+" ");
        }
        System.out.println("\n Size of Phenotype is: "+ grammar.getPhenotype().size());
        System.out.println("\n Here is the Phenotype String!");
        System.out.println(grammar.getPhenotypeString());
        System.out.println("Here is the genotype string!");
        System.out.println(grammar.getGenotypeString());
        System.out.println("Contents of the genotypeIntArray:");
        int []tmpArr=grammar.getGenotypeIntArray();
        for(int j=0;j<grammar.getGenotypeIntArray().length;j++){
            System.out.print(tmpArr[j]+" ");
        }
        System.out.println("\nTree depth is: "+grammar.getTreeDepth());
        if(grammar.isPhenotypeValid())
            System.out.println("The phenotype is also valid:");
        grammar.setVars("G");
        System.out.println("The rules are: \n"+grammar.getRules());
        
    /*    try{
            GEGrammar grammar2=new GEGrammar(grammar);
        }
        catch(java.lang.Exception e){
            e.printStackTrace();
        }*/
    } 
    
}
