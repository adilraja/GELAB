/*
 * Genotype.java
 *
 * Created on June 1, 2007, 11:35 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

/**
 *
 * @author adilraja
 */
package GrammaticOptimization;

import java.util.*;
import java.util.ArrayList;

/*Default Constructor. Creates a genotype structure of length newLength, using the elements of newArray, and sets 
 *its valid field to newValid and its fitness to newFitness. Non-specified arguments are given default values
 *, as specified in the function prototype.
 *
 */
public class Genotype extends ArrayList<Integer>{//codonType
    
    private Vector genome;
    private boolean _libGE_Genotype_valid;
    private double _libGE_Genotype_fitness;
    private int _libGE_Genotype_maxCodonValue;
    private int _libGE_Genotype_effectiveSize;
    private int _libGE_Genotype_wraps;
    
    
    public Genotype(){
        
    }
    
    /** Creates a new instance of Genotype */
    public Genotype(final int []newArray, final int newLength, final boolean newValid, final double newFitness) {
        _libGE_Genotype_valid=newValid;
        _libGE_Genotype_fitness=newFitness;
        this.setMaxCodonValue(32767);//INT_MAX
        for(int ii=0;ii<newLength;ii++){
            this.add(new Integer(newArray[ii]));
        }
        setEffectiveSize(0);
        setWraps(0);
       
    }
    
    /*Constructor. Creates a genotype structure with the contents of newvector, and sets its valid
     *field to newValid and its fitness to newFitness.
     *Non-specified arguments are given default values, as specified in he function prototype
     */
    public Genotype(final ArrayList<Integer> newVector, final boolean newValid, final double newFitness) {
        _libGE_Genotype_valid=newValid;
        _libGE_Genotype_fitness=newFitness;
        this.addAll(newVector);
        setMaxCodonValue(32767);
        setEffectiveSize(0);
        setWraps(0);
        
    }
    
    /*Constructor. Creates an empty genotype structure, and sets maCodonValue to the value
     *specified as argument
     */
    public Genotype(final int maxCodonValue) {
        setMaxCodonValue(maxCodonValue);
        setEffectiveSize(0);
        setWraps(0);
        
    }
    
    /*Copy constructor
     */
    public Genotype(final Genotype copy) {
        setValid(copy.getValid());
        setFitness(copy.getFitness());
        setMaxCodonValue(copy.getMaxCodonValue());
        setEffectiveSize(copy.getEffectiveSize());
        setWraps(copy.getWraps());
    }
    
    /*Returns the current valid field
     */
    public final boolean getValid(){
        return _libGE_Genotype_valid;
    }
    
    /*Set a new value for the valid field
     */
    public void setValid(final boolean newValid){
        _libGE_Genotype_valid=newValid;
    }
    
    /*Returns the current fitness score
     */
    public final double getFitness(){
        return _libGE_Genotype_fitness;
    }
    
    /*Sets a new fitness score
     */
    public void setFitness(final double newFitness){
        _libGE_Genotype_fitness=newFitness;
    }
    
    /*Returns the maximum containable value in a codon
     */
    public final int getMaxCodonValue(){
        return _libGE_Genotype_maxCodonValue;
    }
    
    /*Sets the maximum containable value in a codon
     */
    public void setMaxCodonValue(final int newMaxCodonValue){
        _libGE_Genotype_maxCodonValue=newMaxCodonValue;
    }
    
    /*Returns effective length of Genotype
     */
    public final int getEffectiveSize(){
        return _libGE_Genotype_effectiveSize;
    }
    
    /*Sets effective length of genotype
     */
    public void setEffectiveSize(final int newEffectiveSize){
        _libGE_Genotype_effectiveSize=newEffectiveSize;
    }
    
    /*Returns number of wrapping events
     */
    public final int getWraps(){
        return _libGE_Genotype_wraps;
    }
    
    /*Sets the number of wrapping events
     */
    public void setWraps(final int newWraps){
        _libGE_Genotype_wraps=newWraps;
    }
    
    /*Used to print the genome as a string
     */
    public String printContents(){
        //String s=new String();
        return this.toArray().toString();
    }
}
//complete