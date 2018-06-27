/*
 * GEGrammar.java
 *
 * Created on August 2, 2007, 12:22 AM
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
import java.util.ListIterator;
import java.util.Iterator;

public class GEGrammar extends CFGrammar {
    
    private int maxWraps;
    protected ArrayList<Production> productions;
    private int counterFlag;//I just put it here
    private Stack<Symbol> nonterminals;
    private String phenotypeString;
    
    
    /** 
     * Creates a new instance of GEGrammar 
     */
    public GEGrammar() {
        super();
        setMaxWraps(0);
        this.productions=new ArrayList();
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
        this.productions=new ArrayList();
        this.productions.clear();
        this.genotype2phenotype(true);
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
 * This is simply like the above function. Its purpose is to be able to call genotype2phenotype from 
 * outside java, such as Matlab or Octave
 * @param buildDerivationTree
 * @return 
 */
public boolean genotype2phenotype(final String buildDerivationTree){
    
    if(buildDerivationTree.equalsIgnoreCase("true")){
        try{
            return this.genotype2phenotype(true);
        }
   //     catch(Exception e){
   //         e.printStackTrace();
   //         return false;
   //     }
        catch(java.lang.NullPointerException e){
            System.out.println(e.getMessage());
            return false;
        }
    }
    else{
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
            if(!this.productions.isEmpty())
                this.productions.clear();//Removes all items from the list
	}
	// Quick safety checks
	//if((!getValidGrammar())||(!genotype.getValid())||(!getGenotype()->size())){
        
	if(!getValidGrammar()){
		phenotype.clear();
		phenotype.setValid(false);
		return false;
	}

	//Wraps counter and nonterminals (Symbols) stack
	int wraps=0;
	this.nonterminals=new Stack();

	// Iterators
	Iterator<Rule> ruleIt;
	ListIterator<Production> prodIt;
	Iterator<Integer> genoIt=genotype.iterator();
        Integer tmpInt;//shall contain the values in Genotype
        
	// Start with the start symbol
        Symbol tmpSmb=this.getStartSymbol();
/*        try{
            System.out.println("Here is the symbol: "+tmpSmb.getType().toString());
        }
        catch(java.lang.NullPointerException e){
            System.out.println("Problem getting the symbol!");
            e.printStackTrace();
        }*/
	this.nonterminals.push(tmpSmb);
	if(buildDerivationTree){
		// Use start symbol as the derivationTree node
            try{
		this.derivationTree.setData(tmpSmb);
            }
            catch(java.lang.NullPointerException e){
                System.out.println(e+" The call: derivationTree.setData(getStartSymbol()); in GEGrammar sucks");
                e.printStackTrace();
            }
	}

	boolean gotToUseWrap=true;
      Integer codonGenoIt=new Integer(0);
      try{
        codonGenoIt=genoIt.next();
      }
      catch(java.util.NoSuchElementException e){
          e.printStackTrace();
      }
	// Get rid of all non-terminal symbols
	while((!this.nonterminals.empty())&&(wraps<=getMaxWraps())){
		// Do a mapping step
                
		switch(genotype2phenotypeStep(this.nonterminals, codonGenoIt, buildDerivationTree)){
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
				//System.exit(0);
                                returnValue=false;
                                break;
		}
	}
	//newEffectiveSize+=(genoIt-genotype.begin());
	// Was the mapping successful?
	if((wraps>getMaxWraps())||(!this.nonterminals.empty())){
		returnValue=false;
		// Add remaining symbols in nonterminals queue to phenotype
		while(!this.nonterminals.empty()){
			phenotype.add(this.nonterminals.pop());
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
public int genotype2phenotypeStep(Stack<Symbol> nonterminals1, Integer codonGenoIt, boolean buildDerivationTree){
	
	ListIterator<Production> prodIt;
	int returnValue=-1;
        this.nonterminals=nonterminals1;
	// Find the rule for the current non-terminal
	Rule rulePtr=null;
        try{
            rulePtr=findRule(this.nonterminals.peek());
        }
        catch(java.lang.Exception e){
            System.out.println(e+" genotype2phenotypeStep()s rulePtr sucks");
            returnValue=-1;
            return returnValue;
        }
	//cerr << "mapping " << *(nonterminals.top()) << " with " << *genoIt << "\n";
        
	if(rulePtr==null){// Undefined symbol - could be an extension symbol
            try{
		if(this.nonterminals.peek().getSymbol().startsWith("<GECodonValue")&&(codonGenoIt!=null)){
			// Insert codon value
			// Extract range for value from non-terminal specification
			int low=0,high=-1, pointer="<GECodonValue".length();
			// currentChar is the first character after "<GECodonValue"
			char currentChar=this.nonterminals.peek().getSymbol().substring(pointer,pointer+1).charAt(0);
                       
			// Look for range definitions
			while(Character.toString(currentChar).compareTo(">")!=0){
				if(Character.toString(currentChar).compareTo("-")==0){
					// Low range specification
					currentChar=this.nonterminals.peek().getSymbol().substring(++pointer,pointer+1).charAt(0);
					while(Character.isDigit(currentChar)){
						low=(low*10)+(currentChar-'0');
                                   
						currentChar=this.nonterminals.peek().getSymbol().substring(++pointer,pointer+1).charAt(0);
					}
				}
				else if(Character.toString(currentChar).compareTo("+")==0){
					// High range specification
					currentChar=this.nonterminals.peek().toString().substring(++pointer,pointer+1).charAt(0);
					while(Character.isDigit(currentChar)){
						if(high==-1){
							high=0;
						}
						high=(high*10)+(currentChar-'0');
						currentChar=this.nonterminals.peek().toString().substring(++pointer,pointer+1).charAt(0);
					}
				}
				else{// Ignore errors
					currentChar=this.nonterminals.peek().toString().substring(++pointer,pointer+1).charAt(0);
				}
			}
			// High range was not specified, so set it to maximum
			if(high==-1){
				high=genotype.getMaxCodonValue();
			}
			// Remove non-terminal
			this.nonterminals.pop();
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
			phenotype.add(this.nonterminals.pop());
			// Remove non-terminal
			//nonterminals.pop();
			// Invalidate mapping
			returnValue=-1;
		}
            }
            catch(java.lang.NullPointerException e){
                System.out.println(e);
                returnValue=-1;
                return returnValue;
            }
	}
        
	//else if(rulePtr->getMinimumDepth()>=INT_MAX>>1){// Stuck on recursive rule
	// Allow recursive rules, but only if they consume a codon
	else if((rulePtr.getMinimumDepth()>=(32767>>1))// Stuck on recursive rule
		&&(rulePtr.size()<=1)){// No codon will be consumed
		// Include symbol on phenotype
		phenotype.add(this.nonterminals.pop());
		// Remove non-terminal
		//nonterminals.pop();
		// Invalidate mapping
		returnValue=-1;
	}
	else{
		// Remove non-terminal
		this.nonterminals.pop();
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
				this.productions.add(tmpProd);//tmpProd is also used latter
			}
			// Put all terminal symbols at start of production onto phenotype
			int s_start=0;
			int s_stop=0;
                        try{
                            s_stop=tmpProd.size();//Instead of prodIt.size();
                        }
                        catch(java.lang.NullPointerException e){
                            System.out.println(e+"tmpProd is null in GEGrammar");
                            returnValue=-1;
                            return returnValue;
                        }
                        
			while((s_start<s_stop)&&tmpProd.get(s_start).getType().toString().compareTo("TSymbol")==0){
				phenotype.add(tmpProd.get(s_start++));
				//s_start++;
			}
			// Push all remaining symbols from production onto nonterminals queue, backwards
			for(;s_stop>s_start;s_stop--){
				this.nonterminals.push(tmpProd.get(s_stop-1));
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
                if(this.nonterminals.empty()){
                    break;
                }
                else if(!this.nonterminals.peek().getType().toString().equalsIgnoreCase("TSymbol")){
                    break;
                }
                phenotype.add(this.nonterminals.pop());
            }
                catch(java.lang.NullPointerException e){
                System.out.println(e+"The while loop at the end of genotype2phenotypeStep sucks");
                e.printStackTrace();
                returnValue=-1;
                return returnValue;
              //  System.exit(0);
            }
            catch(java.util.EmptyStackException e){
                System.out.println(e+" GEGrammar sucks...Stack is empty");
                returnValue=-1;
                return returnValue;
              //  System.exit(0);
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
        prodIt.previous();
	while(treeIt.hasNext()){
            try{
                prodIt.next();
                buildDTree(treeIt.next(), prodIt);
  //              prodIt.next();
                
           }
            catch(java.util.NoSuchElementException e){
              System.out.println(e+" The last lines of buildTree suck");
             // System.exit(0);
           }
		
	//	treeIt++;
	}
    }
    catch(java.lang.StackOverflowError e){
        e.printStackTrace();
    }
}

/**
 * Converts an integer array to an ArrayList<Integer> genoType
 * @param geno
 * @param size 
 */
public void setGenotype(final int[] geno, int size){
    ArrayList<Integer> genoList=new ArrayList();
    for(int i=0;i<size;i++){
        genoList.add(new Integer(geno[i]));
    }
    this.genotype.clear();
    this.genotype.addAll(genoList);
}
/**
 * Converts the contents of the Phenotype list to its string representation and 
 * then returns it back.
 * @return 
 */
private String phenotypetoString(){
    this.phenotypeString=new String();
    int siz=this.getPhenotype().size();
    Iterator<Symbol> symbIt=this.getPhenotype().iterator();
    while(symbIt.hasNext()){
        this.phenotypeString+=symbIt.next().getSymbol().toString();
    }
    return this.phenotypeString;
}

/**
 * return the phenotype string
 * @return 
 */
public String getPhenotypeString(){
        return this.phenotypetoString();
}

public boolean isPhenotypeValid(){
    return this.phenotype.getValid();
}

/**
 * Returns the string format of phenotype. Can be plugged into Matlab/eval
 * @return 
 */
public String getGenotypeString(){
    Iterator<Integer> symbIt=this.getGenotype().iterator();
    String genoString=new String();
    while(symbIt.hasNext()){
        genoString+=Integer.toString(symbIt.next().intValue());
        genoString+=" ";
    }
    return genoString;
}


}
