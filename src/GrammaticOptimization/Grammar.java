/*
 * Grammar.java
 *
 * Created on July 26, 2007, 6:09 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package GrammaticOptimization;

/**
 *
 * @author adilraja
 */
import java.util.Iterator;

public abstract class Grammar extends Mapper{
    private boolean validGrammar;
    private int startSymbol;
    
    protected abstract boolean genotype2phenotype();
    protected abstract boolean phenotype2genotype();
    
    /**
     * Creates a new instance of Grammar 
     */
    
    public Grammar() {
        super();
        setValidGrammar(false);
	startSymbol=0;
    }
    
    /**
     *Constructor setting the genotype structure of this mapper to newGenotype.
     */
    public Grammar(final Genotype newGenotype){
        super(newGenotype);
        setValidGrammar(false);
	startSymbol=0;
    }
    
    
    /**
     *Constructor setting the phenotype structure of this mapper to newPhenotype.
     */
    public Grammar(final Phenotype newPhenotype){
        super(newPhenotype);
        setValidGrammar(false);
	startSymbol=0;
    }
    
    /**
     *Copy Constructor
     */
    public Grammar(final Grammar copy){
        super();
        setValidGrammar(copy.getValidGrammar());
	startSymbol=copy.startSymbol;
    }
    
    /**
     * Return the validity of the current grammar.
     */
    
    
    public final boolean getValidGrammar(){
	return validGrammar;
    }

    /**
     *Set the validity of the grammar.
     */
    protected void setValidGrammar(final boolean newValidGrammar){
	validGrammar=newValidGrammar;
    }
    
/**
 *Return current start symbol.
 */
    
public final Symbol getStartSymbol(){
	//return front().lhs.front();
	//return (*this)[startSymbol].lhs.front();
        Symbol symb=null;
        if (startSymbol<this.size())
        {
         symb=this.get(startSymbol).lhs.get(0);
        }
        return symb;
}

/**
 *Change start symbol by index on Vector of rules.
 */
public boolean setStartSymbol(final int index){
	if(index<this.size()){// Check boundaries.
		startSymbol=index;
		genotype2phenotype();// Update phenotype.
		return true;
	}
	return false;
}


/**
 *Change start symbol by symbol pointer.
 */
public boolean setStartSymbol(final Symbol newStartSymbol){
	int ii=0;
	Iterator<Rule> it=this.iterator();
	while(it.hasNext()){
		// Work by *pointer*.
		if(it.next().lhs.get(0).getSymbol().compareTo(newStartSymbol.getSymbol())==0){
			startSymbol=ii;
			genotype2phenotype();// Update phenotype.
			return true;
		}
		ii++;
	}
	return false;
}

/**
 *Change start symbol by string.
 */

public boolean setStartSymbol(final String newStartSymbol){
	int ii=0;
	Iterator<Rule> it=this.iterator();
	while(it.hasNext()){
		// Work by *string*.
		String currentStartSymbol=it.next().lhs.get(0).getSymbol();
		if(currentStartSymbol.compareTo(newStartSymbol)==0){
			startSymbol=ii;
			genotype2phenotype();// Update phenotype.
			return true;
		}
		ii++;
	}
	return false;
}

/**
 *Return pointer to current start rule.
 */

public final Rule getStartRule(){
	return this.get(0);
}

}
//complete
