/*
 * Production.java
 *
 * Created on June 3, 2007, 12:24 AM
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
import java.util.Iterator;



public class Production extends ArrayList<Symbol>{
    
    
    private boolean recursive;
    private int minimumDepth;
    /**
     *Creates a new production with newLength elements
     */
    public Production(final int newLength){
        super();
        this.ensureCapacity(newLength);
        setRecursive(false);
        setMinimumDepth(32767>>1);
    }
    /**
     *Copy constructor; copy all symbols
     */
    public Production(final Production copy){
        Iterator<Symbol> itr = copy.iterator();
        while(itr.hasNext()) {
            Symbol tmpsymb=itr.next();
            if(tmpsymb.getType().toString().compareTo("TSymbol")==0){
                this.add(new Symbol(tmpsymb));// Terminal symbol, create new one
            }     
            else 
                this.add(tmpsymb);
        }
        setRecursive(copy.recursive);
        setMinimumDepth(copy.minimumDepth);
    }
    /**
     *Delete all terminal symbols and all symbol references
     */
    public void clearTerminals(){
        Iterator<Symbol> itr = this.iterator();
        while(itr.hasNext()) {
            Symbol tmpsymb=itr.next();
            if(tmpsymb.getType().toString().compareTo("TSymbol")==0){
                this.remove(tmpsymb);
            }            
            
        }
    }
    
    /**
     *Return the recursive nature of this production
     */
    
    public final boolean getRecursive(){
        return this.recursive;
    }
    
    /**
     *Update the recursive nature of this production
     */
    public void setRecursive(final boolean newRecursive){
        this.recursive=newRecursive;
    }
    /**
     *Return the minimum mapping depth of this production
     */
    public final int getMinimumDepth(){
        return this.minimumDepth;
    }
    
    
    /**
     *Update the minimum mapping depth of this production
     */
    public void setMinimumDepth(final int newMinimumDepth){
        this.minimumDepth=newMinimumDepth;
    }

    
    /**
     *Print the contents of this production
     */
    
    /**
     *This removes and adds a symbol at a particular location in this object. To be called latter from CFGrammar class.
     */
    public void insertSymbol(final Symbol symb, int pos){
        this.remove(pos);
        this.add(pos,symb);
    }
    
}
//file complete
