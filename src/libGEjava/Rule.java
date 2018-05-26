/*
 * Rule.java
 *
 * Created on June 21, 2007, 12:06 PM
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
import java.util.ArrayList;// The left-hand side of the rule

public class Rule extends ArrayList<Production>{
    private boolean recursive;// Recursive nature of rule
    private int minimumDepth;	// Minimum depth of parse tree for production to map to terminal symbol(s)
    public ArrayList<Symbol> lhs;
    /**
     *Creates a new rule with newLength elements.
     */
    public Rule(final int newLength){
        super(newLength);
	this.ensureCapacity(newLength);
	setRecursive(false);
	setMinimumDepth(32767>>1);
        lhs =new ArrayList();
}
    /**
     *Copy constructor
     */
    public Rule(final Rule copy){
        super();
        lhs=new ArrayList();
        Iterator<Symbol> lhsIt=copy.lhs.iterator();
	while(lhsIt.hasNext()){
            Symbol tmpsymb=lhsIt.next();
		lhs.add(new Symbol(tmpsymb));
	}
	setRecursive(copy.getRecursive());
	setMinimumDepth(copy.getMinimumDepth());
    }
   
/**
 *Delete all productions, and all symbols stored in lhs.
 */
 
    
public void clear(){
    try{
    lhs.clear();//clear the lhs vector
	super.clear();// Clear production vector
    }
    catch(java.lang.Exception e){
        System.out.print(e);
    }
}

    
/**
 *Return the recursive nature of this rule.
 */

public final boolean getRecursive(){
	return recursive;
}

/**
 *Update the recursive nature of this rule.
 */

public void setRecursive(final boolean newRecursive){
	recursive=newRecursive;
}

/**
 *Return the minimum mapping depth of this rule.
 */
public final int getMinimumDepth(){
	return minimumDepth;
}

/**
 * Update the minimum mapping depth of this Rule.
 */
public void setMinimumDepth(final int newMinimumDepth){
	minimumDepth=newMinimumDepth;
}


}

