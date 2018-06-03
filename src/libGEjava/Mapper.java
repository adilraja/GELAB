/*
 * Mapper.java
 *
 * Created on June 1, 2007, 11:24 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

/**
 *
 * @author adilraja
 */
package libGEjava;

import java.util.*;
import java.util.ArrayList;

public abstract class Mapper extends ArrayList<Rule> {
    
    protected Genotype genotype;
    protected Phenotype phenotype;
    protected abstract boolean genotype2phenotype();
    protected abstract boolean phenotype2genotype();
    
    public Mapper(){
        super();
        this.phenotype=new Phenotype();
        this.genotype=new Genotype();
        
    }
    /**
     *Constructor with genotype structure. set to new newGenotype
     */
    public Mapper(final Genotype newGenotype){
        super();
        this.genotype=newGenotype;
    }
    /**
     *Constructor with phenotype structor. set phenotype to newPhenotype
     */
    public Mapper(final Phenotype newPhenotype){
        super();
        this.phenotype=new Phenotype(newPhenotype);
    }
    /**
     *Copy Constructor
     */
     public Mapper(final Mapper copy){
         super(copy);
         this.genotype=new Genotype(copy.genotype);
         this.phenotype=new Phenotype(copy.phenotype);
     }
     /**
      *returns the genotype structure of this mapper
      */
     public final Genotype getGenotype(){
         return this.genotype;
     }
     /**
      *Sets this mapper's genotype structure to be a copy of the argument, newgenotype,
      *and calls the genotype2phenotype private method.
      */
    public void setGenotype(final Genotype newGenotype){
        this.genotype=new Genotype(newGenotype);
        genotype2phenotype();
    }
    /**
     *returns a pointer to the phenotype structure of this mapper
     */
    public final Phenotype getPhenotype(){
        return this.phenotype;
    }
    /**
     *Sets this mapper's phenotype structure to be a copy of the argument phenotype
     *structure, and calls the phenotype2genotype private method
     */
    public void setPhenotype(final Phenotype newPhenotype){
        phenotype=new Phenotype(newPhenotype);
        phenotype2genotype();
    }
    /**
     *Sets the maximum codon value of the genotype structure
     */
    public void setGenotypeMaxCodonValue(final int newMaxCodonValue){//CodonType=int
        this.genotype.setMaxCodonValue(newMaxCodonValue);
    }
    //something left here
}
// file complete