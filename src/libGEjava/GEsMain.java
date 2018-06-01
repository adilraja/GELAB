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




public class GEsMain {
    
    /** Creates a new instance of GEsMain */
    public GEsMain() {
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
    //    try{
    //    String current = new java.io.File( "." ).getCanonicalPath();
    //    System.out.println("Current dir:"+current);
    //    }
    //   catch(java.io.IOException e){
    //        e.printStackTrace();
    //    }
        
        Random rand=new Random();
        int []newArray= new int[10];
        newArray[0]=152;
        newArray[1]=2;
        newArray[2]=1;
        newArray[3]=3;
        newArray[4]=3;
        newArray[5]=3;
        newArray[6]=3;
        newArray[7]=3;
        newArray[8]=3;
        newArray[9]=3;
        
        ArrayList<Integer> arrList=new ArrayList();
       for (int i=0;i<10;i++){
            arrList.add((Integer)newArray[i]);
       }
        Genotype geno=new Genotype(newArray, 10, true,10);
        

        GEGrammar grammar=new GEGrammar(geno);
     //   grammar.setGenotype(geno);
     

        grammar.setMaxWraps(9);

        if(grammar.readBNFFile("/home/adil/Dropbox/adils-java/libGEjava/grammars/sr.bnf")) {
        } else {
            System.out.println("Reading of the grammar file was not successful\n");
        }

        try{
            grammar.genotype2phenotype(true);
        }
        catch(java.lang.Exception e){
            System.out.println(e+"In Main");
        }
        catch(java.lang.NoClassDefFoundError e){
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
        System.out.println("Here are the results: phenotype sizse= "+grammar.getPhenotype().size());
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
        
    }
    
}
