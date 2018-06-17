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
        
        Random rand=new Random();
        int []newArray= new int[15];
        newArray[0]=152;
        newArray[1]=1;
        newArray[2]=2;
        newArray[3]=5;
        newArray[4]=4;
        newArray[5]=6;
        newArray[6]=9;
        newArray[7]=1;
        newArray[8]=3;
        newArray[9]=34;
        newArray[10]=34;
        newArray[11]=34;
        newArray[12]=34;
        newArray[13]=34;
        newArray[14]=34;
        
        ArrayList<Integer> arrList=new ArrayList();
       for (int i=0;i<10;i++){
            arrList.add((Integer)newArray[i]);
       }
        Genotype geno=new Genotype(newArray, 15, true,10);
        

        GEGrammarSI grammar=new GEGrammarSI();
        grammar.setGenotype(geno);
     //   grammar.setGenotype(geno);
     GEGrammarSI grammar3;
    

        grammar.setMaxWraps(9);
        grammar.setMaxDepth(6);
        

        if(grammar.readBNFFile("/home/adil/Dropbox/adils-java/libGEjava/grammars/sr.bnf")) {
        } else {
            System.out.println("Reading of the grammar file was not successful\n");
        }
        grammar.init(1);
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
        System.out.println("My name is John Rambo "+grammar.size());
        System.out.println(newArray.length);
       
        String str1=new String("Adil");
        String str2=new String("Adil");
        if(str1.equals(str2))
                System.out.println("adilRaja");
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
        
    /*    try{
            GEGrammar grammar2=new GEGrammar(grammar);
        }
        catch(java.lang.Exception e){
            e.printStackTrace();
        }*/
    } 
    
}
