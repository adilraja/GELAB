/*
 * Phenotype.java
 *
 * Created on June 2, 2007, 5:18 PM
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


public class Phenotype extends ArrayList<Symbol> {
    
    /** 
     * Creates a new instance of Phenotype 
     *Default constructor. Creates a phenotype structure, and sets its valid field to newValid and its fitness
     *fitness to newFitness. Non-specified arguments are given default values.
     */
    private boolean _libGE_Phenotype_valid;
    private double _libGE_Phenotype_fitness;
    
    public Phenotype(){
        
    }
    public Phenotype(final boolean newValid, final double newFitness) {
        _libGE_Phenotype_valid=newValid;
        _libGE_Phenotype_fitness=newFitness;
    }
    /**
     * Copy constructor
     */
    public Phenotype(final Phenotype copy){
        setValid(copy.getValid());
        setFitness(copy.getFitness());
    }
    
    /*Returns the current _libGE_Phenotype_valid field
     */
    public final boolean getValid(){
        return _libGE_Phenotype_valid;
    }
    
    
    /**
     * sets a new value for the _libGE_Phenotype_valid field
     */
    public void setValid(final boolean newValid){
        _libGE_Phenotype_valid=newValid;
    }
    
    /**
     * Returns the current fitness score
     */
    public final double getFitness(){
        return _libGE_Phenotype_fitness;
    }
    
    /**
     * Sets a new fitness score
     */
    public void setFitness(final double newFitness){
        _libGE_Phenotype_fitness=newFitness;
    }
    
    public final String getString(){
        return this.toArray().toString();
    }
    /**
     *Print the contents of the phenotype
     */
    public String getPrintOut(){
        return this.toArray().toString();
    }
}
//file complete
