/*
 * GEsMain.java
 *
 * Created on August 4, 2007, 5:31 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package GrammaticOptimization;

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
        Random rand=new Random();
        int []newArray= new int[10];
        newArray[0]=0;
        newArray[1]=2;
        newArray[2]=1;
        newArray[3]=4;
        newArray[4]=4;
        newArray[5]=4;
        newArray[6]=4;
        newArray[7]=4;
        newArray[8]=4;
        newArray[9]=4;
        
        ArrayList<Integer> arrList=new ArrayList();
       for (int i=0;i<10;i++){
            arrList.add((Integer)newArray[i]);
       }
        Genotype geno=new Genotype(newArray, 10, true,10);
        
        GEGrammar grammar=new GEGrammar(geno);
        grammar.setMaxWraps(9);
        grammar.readBNFFile("/Users/adilraja/mywork/adils-java/GrammaticOptimization/dist/grammar.bnf");
   //     try{
       //     grammar.genotype2phenotype(true);
    //    }
      //  catch(java.lang.Exception e){
       //     System.out.println(e+"In Main");
        //}
        Iterator<Symbol> symbIt=grammar.getPhenotype().iterator();
        Iterator<Rule> ruleIt=grammar.iterator();
        System.out.println("Here are the results: phenotype sizse= "+grammar.getPhenotype().size());
        while(symbIt.hasNext()){
            System.out.print(symbIt.next().getSymbol());
        }
        if(grammar.phenotype.getValid()==true)
            System.out.println("\nThe above phenotype is valid");
        else 
            System.out.println("\nThe above phenotype is not valid");
        System.out.println("\n\nHere is the grammar");
        while(ruleIt.hasNext()){
            Rule tmpRule=ruleIt.next();
            System.out.print("\n"+tmpRule.lhs.get(0).getSymbol()+"::=");
            Iterator<Production> prodIt=tmpRule.iterator();
            while(prodIt.hasNext()){
                Iterator<Symbol> symbIt2=prodIt.next().iterator();
                while(symbIt2.hasNext()){
                    System.out.print(symbIt2.next().getSymbol());
                }
            }
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
        while(ruleIt.hasNext()){
            Rule tmpRule=ruleIt.next();
            System.out.print("\n"+tmpRule.lhs.get(0).getType().toString()+"::=");
            Iterator<Production> prodIt=tmpRule.iterator();
            while(prodIt.hasNext()){
                Iterator<Symbol> symbIt2=prodIt.next().iterator();
                while(symbIt2.hasNext()){
                    System.out.print(symbIt2.next().getType().toString()+" ");
                }
            }
        }
        
    }
    
}
