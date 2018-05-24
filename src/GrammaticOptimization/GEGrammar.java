/*
 * GEGrammar.java
 *
 * Created on August 2, 2007, 12:22 AM
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
import java.util.ListIterator;
import java.util.Iterator;

public class GEGrammar extends CFGrammar {
    
    private int maxWraps;
    protected ArrayList<Production> productions;
    private int counterFlag;//I just put it here
    
    
    /** 
     * Creates a new instance of GEGrammar 
     */
    public GEGrammar() {
        super();
        setMaxWraps(0);
    }
   
    
    /**
     *Constructor setting the genotype structure of this mapper to newGenotype.
     */
public GEGrammar(final Genotype newGenotype){
    super(newGenotype);
    setMaxWraps(0);
    productions=new ArrayList();
}

/**
     *Constructor setting the phenotype structure of this mapper to newPhenotype.
     */
public GEGrammar(final Phenotype newPhenotype){
    super(newPhenotype);
    setMaxWraps(0);
}
   /**
    * Copy Constructor.
    */
public GEGrammar(final GEGrammar copy) throws Exception{
        super(copy);
	setMaxWraps(copy.getMaxWraps());
	// Call genotype2Phenotype() to regenerate phenotype structure,
	// and productions and derivationTree structures.
	genotype2phenotype(true);
}


/**
 * Return number of maximum allowed wrapping events.
 */
public final int getMaxWraps() {
	return maxWraps;
}

/**
 * Set the new number of maximum allowed wrapping events.
 */
public void setMaxWraps(final int newMaxWraps){
	maxWraps=newMaxWraps;
}

/**
 * Builds the the current derivation tree, and returns its address;
 * if derivation tree is impossible to build, returns NULL.
 */
public final Tree getTree()throws Exception{
	if((!getValidGrammar())||(!genotype.getValid())||(getGenotype().size()!=0)){
		return null;
	}
	genotype2phenotype(true);
	return this.derivationTree;
}

/**
 * Returns a vector of all productions used during the mapping process.
 */
public final ArrayList<Production> getProductions()throws Exception{
	if((!getValidGrammar())||(!genotype.getValid())||(getGenotype().size()!=0)){
		return null;
	}
	genotype2phenotype(true);
	return productions;
        
}

/**
 * Strict implementation of genotype2Phenotype interface. Calls local
 * genotype2phenotype(bool) method, with bool=false.
 */
public boolean genotype2phenotype(){
    
    try{
	 return genotype2phenotype(false);
    }
    catch(Exception e){
        System.out.println(e+" genotype2phenotype()");
        return false;
    }
}

/**
 * Updates the contents of the phenotype structure, based on the current
 * genotype and the current grammar, and according to the standard GE
 * mapping process. Returns true upon a successful mapping, and false
 * otherwise, and also updates the valid field of the phenotype.
 * With argument set to true, also updates derivationTree.
 */
public boolean genotype2phenotype(final boolean buildDerivationTree){
        
	this.derivationTree=new Tree();//Initialize the tree
	boolean returnValue=true;
	int newEffectiveSize=0;
        this.counterFlag=0;
	// Start by setting effectiveSize to 0
	genotype.setEffectiveSize(newEffectiveSize);
  //      System.out.println("You called readBNFString, which called this");
        
        this.phenotype=new Phenotype(true,1);//No need to do this as this has already been done in Mapper's constructor.
        if(!phenotype.isEmpty())
            phenotype.clear();
        
	if(buildDerivationTree){
		this.productions.clear();//Removes all items from the list
	}
	// Quick safety checks
	//if((!getValidGrammar())||(!genotype.getValid())||(!getGenotype()->size())){
	if(!getValidGrammar()){
		phenotype.clear();
		phenotype.setValid(false);
		return false;
	}

	//Wraps counter and nonterminals stack
	int wraps=0;
	Stack<Symbol> nonterminals=new Stack();

	// Iterators
	Iterator<Rule> ruleIt;
	ListIterator<Production> prodIt;
	Iterator<Integer> genoIt=genotype.iterator();
        Integer tmpInt;//shall contain the values in Genotype

	// Start with the start symbol
	nonterminals.push(getStartSymbol());
	if(buildDerivationTree){
		// Use start symbol as the derivationTree node
            try{
		this.derivationTree.setData(getStartSymbol());
            }
            catch(java.lang.NullPointerException e){
                System.out.println(e+" The call: derivationTree.setData(getStartSymbol()); in GEGrammar sucks");
            }
	}

	boolean gotToUseWrap=true;
      Integer codonGenoIt=genoIt.next();
        
	// Get rid of all non-terminal symbols
	while((!nonterminals.empty())&&(wraps<=getMaxWraps())){
		// Do a mapping step
		switch(genotype2phenotypeStep(nonterminals, codonGenoIt, buildDerivationTree)){
			case -1:returnValue=false;
				break;
			case 0:	;
				break;
			case 1:	codonGenoIt=genoIt.next();
                                //genoIt++;
				newEffectiveSize++;
				if(gotToUseWrap){
					wraps++;
					gotToUseWrap=false;
				}
				// Check if wrap is needed
				if(!genoIt.hasNext()){
					//newEffectiveSize+=genotype.size();
					genoIt=genotype.iterator();
                                     //   codonGenoIt=new Integer(genoIt.next().intValue());
					gotToUseWrap=true;
				}
				break;
			default:System.out.println("Internal error in genotype2Phenotype()");
				System.out.println("Execution aborted.");
				System.exit(0);
		}
	}
	//newEffectiveSize+=(genoIt-genotype.begin());
	// Was the mapping successful?
	if((wraps>getMaxWraps())||(!nonterminals.empty())){
		returnValue=false;
		// Add remaining symbols in nonterminals queue to phenotype
		while(!nonterminals.empty()){
			phenotype.add(nonterminals.pop());
		}
	}
	phenotype.setValid(returnValue);
	genotype.setEffectiveSize(newEffectiveSize);
	genotype.setWraps(wraps);
	// Now build derivation tree, based on productions vector
	if(buildDerivationTree){
		this.derivationTree.clear();
		this.derivationTree.setData(getStartSymbol());
		this.derivationTree.setCurrentLevel(1);
		this.derivationTree.setDepth(1);
		prodIt=productions.listIterator();//something wrong here
		buildDTree(this.derivationTree,prodIt);
                Production temp =prodIt.next();
	}
	return returnValue;
}

/**
 * Updates the contents of the genotype structure, based on the current
 * phenotype and the current grammar, and according to a mapping process
 * corresponding to the inverse of the standard GE mapping process.
 * Returns true upon a successful inverse mapping, and false otherwise.
 */
public boolean phenotype2genotype(){
	return false;
//FIXME
}

 /**
  * Performs one step of the mapping process, that is, maps the next
  *non-terminal symbol on the nonterminals stack passed as argument, using the
  *codon at the position pointed by genoIt.
  *Returns number of codons consumed, -1 if not successful
  */
public int genotype2phenotypeStep(Stack<Symbol> nonterminals, Integer codonGenoIt, boolean buildDerivationTree){
	
	ListIterator<Production> prodIt;
	int returnValue=-1;

	// Find the rule for the current non-terminal
	Rule rulePtr=null;
        try{
            rulePtr=findRule(nonterminals.peek());
        }
        catch(java.lang.Exception e){
            System.out.println(e+" genotype2phenotypeStep()s rulePtr sucks");
        }
	//cerr << "mapping " << *(nonterminals.top()) << " with " << *genoIt << "\n";
        
	if(rulePtr==null){// Undefined symbol - could be an extension symbol
            try{
		if(nonterminals.peek().getSymbol().startsWith("<GECodonValue")&&(codonGenoIt!=null)){
			// Insert codon value
			// Extract range for value from non-terminal specification
			int low=0,high=-1, pointer="<GECodonValue".length();
			// currentChar is the first character after "<GECodonValue"
			char currentChar=nonterminals.peek().getSymbol().substring(pointer,pointer+1).charAt(0);
                       
			// Look for range definitions
			while(Character.toString(currentChar).compareTo(">")!=0){
				if(Character.toString(currentChar).compareTo("-")==0){
					// Low range specification
					currentChar=nonterminals.peek().getSymbol().substring(++pointer,pointer+1).charAt(0);
					while(Character.isDigit(currentChar)){
						low=(low*10)+(currentChar-'0');
                                   
						currentChar=nonterminals.peek().getSymbol().substring(++pointer,pointer+1).charAt(0);
					}
				}
				else if(Character.toString(currentChar).compareTo("+")==0){
					// High range specification
					currentChar=nonterminals.peek().toString().substring(++pointer,pointer+1).charAt(0);
					while(Character.isDigit(currentChar)){
						if(high==-1){
							high=0;
						}
						high=(high*10)+(currentChar-'0');
						currentChar=nonterminals.peek().toString().substring(++pointer,pointer+1).charAt(0);
					}
				}
				else{// Ignore errors
					currentChar=nonterminals.peek().toString().substring(++pointer,pointer+1).charAt(0);
				}
			}
			// High range was not specified, so set it to maximum
			if(high==-1){
				high=genotype.getMaxCodonValue();
			}
			// Remove non-terminal
			nonterminals.pop();
			// Print value onto "codon"
			String codon;
			if(high==low){
				// Catch division by zero
				codon=Integer.toString(low);
			}
			else{
				codon=Integer.toString(codonGenoIt.intValue()%(high-low+1)+low);
			}
			// Insert symbol with value onto phenotype
			phenotype.add(new Symbol(codon,null));
			returnValue=1;
		}
		else{
			// Unknown symbol or special symbol that requires non-empty genotype
			// Include symbol on phenotype
			phenotype.add(nonterminals.pop());
			// Remove non-terminal
			//nonterminals.pop();
			// Invalidate mapping
			returnValue=-1;
		}
            }
            catch(java.lang.NullPointerException e){
                System.out.println(e);
            }
	}
        
	//else if(rulePtr->getMinimumDepth()>=INT_MAX>>1){// Stuck on recursive rule
	// Allow recursive rules, but only if they consume a codon
	else if((rulePtr.getMinimumDepth()>=(32767>>1))// Stuck on recursive rule
		&&(rulePtr.size()<=1)){// No codon will be consumed
		// Include symbol on phenotype
		phenotype.add(nonterminals.pop());
		// Remove non-terminal
		//nonterminals.pop();
		// Invalidate mapping
		returnValue=-1;
	}
	else{
		// Remove non-terminal
		nonterminals.pop();
		// Choose production
		if(codonGenoIt==null&&rulePtr.size()>1){
			// Empty genotype, but symbol requires choice
			// Include symbol on phenotype
			phenotype.add(rulePtr.lhs.get(0));
			// Invalidate mapping
			returnValue=-1;
		}
		else{
			if(codonGenoIt==null){//Empty genotype
				prodIt=rulePtr.listIterator(0);
			}
			else{
				prodIt=rulePtr.listIterator(0);
                                int tmp=0;
                                tmp=codonGenoIt.intValue()%rulePtr.size();
                                for(int i=0; i<tmp;i++)
                                    prodIt.next();
    //                            if(prodIt.hasPrevious())
      //                              prodIt.previous();
			}
			// Place production on productions vector
                        Production tmpProd=prodIt.next();
			if(buildDerivationTree){
				productions.add(tmpProd);//tmpProd is also used latter
			}
			// Put all terminal symbols at start of production onto phenotype
			int s_start=0;
			int s_stop=0;
                        try{
                            s_stop=tmpProd.size();//Instead of prodIt.size();
                        }
                        catch(java.lang.NullPointerException e){
                            System.out.println(e+"tmpProd is null in GEGrammar");
                        }
                        
			while((s_start<s_stop)&&tmpProd.get(s_start).getType().toString().compareTo("TSymbol")==0){
				phenotype.add(tmpProd.get(s_start++));
				//s_start++;
			}
			// Push all remaining symbols from production onto nonterminals queue, backwards
			for(;s_stop>s_start;s_stop--){
				nonterminals.push(tmpProd.get(s_stop-1));
			}
			// 0 or 1 choice for current rule, didn't consume genotype codon
			if(rulePtr.size()<=1){
				returnValue=0;
			}
			else{
				returnValue=1;
			}
		}
	}
        if(phenotype==null)System.out.println("Phenotype is messy");
            
        
	// Finally, pop all terminal symbols on top of stack and insert onto phenotype
    //    try{
	while(true){
            try{
                if((nonterminals.empty()) || (!nonterminals.peek().getType().toString().equalsIgnoreCase("TSymbol"))){
                    break;
                }
                phenotype.add(nonterminals.pop());
            }
                catch(java.lang.NullPointerException e){
                System.out.println(e+" The whileloop at the end of genotype2phenotypeStep sucks");
                System.exit(0);
            }
            catch(java.util.EmptyStackException e){
                System.out.println(e+" GEGrammar sucks...Stack is empty");
                System.exit(0);
            }
            }
      //  }
        
     //   catch(java.lang.NullPointerException e){
       //     System.out.println(e+" The whileloop at the end of genotype2phenotypeStep sucks");
        //}
        
	return returnValue;
}


/**
 * Builds the derivation tree, based on the productions vector.
 *Arguments are current tree node, and iterator on productions vector.
 */
public void buildDTree(Tree currentNode, ListIterator<Production> prodIt){
    
    
    try{
	// If current symbol is not a non-terminal, or if all productions have been treated
	if(currentNode.getData().getType().toString().compareTo("NTSymbol")!=0||!prodIt.hasNext()){
		// Correct productions iterator, as no production was read from it
		prodIt.previous();
		return;
	}
	// Create new tree level
	Iterator<Symbol> symbIt=prodIt.next().iterator();;
	while(symbIt.hasNext()){
		currentNode.add(new Tree(symbIt.next(), currentNode.getCurrentLevel()+1, currentNode.getDepth()+1));
		//symbIt++;
		}
	// Expand each child node
	Iterator<Tree> treeIt=currentNode.iterator();
	while(treeIt.hasNext()){
            try{
                prodIt.next();
                buildDTree(treeIt.next(), prodIt);
  //              prodIt.next();
                
           }
            catch(java.util.NoSuchElementException e){
              System.out.println(e+" The last lines of buildTree suck");
              System.exit(0);
           }
		
	//	treeIt++;
	}
    }
    catch(java.lang.StackOverflowError e){
        e.printStackTrace();
    }
}


}
