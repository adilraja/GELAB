/*
 * Symbol.java
 *
 * Created on June 2, 2007, 6:05 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

/**
 *
 * @author adilraja
 *
 */
package libGEjava;

import java.util.*;
import java.lang.String;

//

enum SymbolType{
    NTSymbol, TSymbol
};

public class Symbol implements java.io.Serializable{
    
    private SymbolType type;
    private String symbol;
    /** Creates a new instance of Symbol */
    /*Creat a new symbol object as a copy of newArry and with type newType, if specified
     */
    public Symbol(){
        setType(SymbolType.TSymbol);
        this.symbol=new String();
    }
    
    public Symbol(final String newArray, final SymbolType newType){
        if(newArray!=null)
            this.symbol=new String(newArray);
        else
            this.symbol=new String("");
        if(newType!=null)
            setType(newType);
        else
            setType(SymbolType.TSymbol);
    }
    /**
     * Copy Constructor
     */
    public Symbol(final Symbol copy){
        try{
            this.symbol=new String(copy.getSymbol());
        }
        catch(java.lang.NullPointerException e){
            System.out.println(e);
        }
        setType(copy.getType());
    }
    
    /**
     * Get the type of the symbol
     */
    public final SymbolType getType(){
        return this.type;
    }
    /*Set the type of the symbol
     */
    public void setType(final SymbolType newType){
        this.type=newType;
    }
    /**
     *Returns the symbol
     */
    public final String getSymbol(){
        return this.symbol;
    }
    /**
     *Sets the symbol
     */
    public void setSymbol(final String newSymbol){
        this.symbol=newSymbol;
    }
    
    
    /**
     *
     */
    public boolean makeComparison(final Symbol newSymbol){
        if(this.symbol.compareTo(newSymbol.symbol)==0 && this.getType().toString().compareTo(newSymbol.getType().toString())==0)
            return true;
        return false;
    }
    public void clear(){
        this.symbol="";
    }
}
//under consideration
