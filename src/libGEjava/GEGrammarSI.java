/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package libGEjava;

import java.util.*;
import java.util.Iterator;
import java.util.ArrayList;

/**
 *
 * @author adil
 */
public class GEGrammarSI extends GEGrammar implements Initialiser{
    private float grow;
    private int maxDepth;
    private float tailRatio;
    private int tailSize;
    private int popSize;
    private int popIndex;
    private ArrayList<Integer> possibleRules;
    private MersenneTwisterFast myRand;
    
    
    /**
     * Default constructor
     */
    public GEGrammarSI(){
        super();
        // Initialiser settings
	this.setGrow(0);
	setMaxDepth(1);
	this.setTailRatio(0);
	this.setTailSize(0);
        this.possibleRules= new ArrayList();
        this.myRand=new MersenneTwisterFast(System.currentTimeMillis());
        
    }
    /**
     * Constructor setting the genotype structure of this mapper to newGenotype
     */
    public GEGrammarSI(final Genotype newGenotype ){
        super(newGenotype);
        
        this.setGrow(0);
	this.setMaxDepth(1);
	this.setTailRatio(0);
	this.setTailSize(0);
        this.possibleRules=new ArrayList();
        this.myRand=new MersenneTwisterFast(System.currentTimeMillis());
    }
    
    /**
     * Constructor setting the phenotype structure of this mapper to newPhenotype.
     */
    public GEGrammarSI(final Phenotype newPhenotype){
        super(newPhenotype);
        
        this.setGrow(0);
	this.setMaxDepth(1);
	this.setTailRatio(0);
	this.setTailSize(0);
        this.possibleRules=new ArrayList();
        this.myRand=new MersenneTwisterFast(System.currentTimeMillis());
    }
    
    /**
     * Copy Constructor
     */
    public GEGrammarSI(final GEGrammarSI copy) throws Exception{
        
        super(copy);
        
        setGrow(copy.getGrow());
	setMaxDepth(copy.getMaxDepth());
	setTailRatio(copy.getTailRatio());
	setTailSize(copy.getTailSize());
        this.possibleRules=new ArrayList();
        this.myRand=new MersenneTwisterFast(System.currentTimeMillis());
    }
    /**
     * Return the grow percentage set for this initialiser.
     */
    public final float getGrow(){
        return this.grow;
    }
    
    /**
     * Update the grow percentage for this initialiser.
     */
    public void setGrow(final float newGrow){
        if((newGrow<0.0)||(newGrow>1.0)){
		this.grow=0;
	}
	else{
		this.grow=newGrow;
	}
    }
    /**
     * Return the full percentage set for this initialiser.
     */
    public final float getFull(){
        return 1-grow;
    }
    
    /**
     * Update the full percentage for this initialiser.
     */
    public void setFull(final float newFull){
        if((newFull<0.0)||(newFull>1.0)){
		this.grow=0;
	}
	else{
		this.grow=1-newFull;
	}
    }
    /**
     * Return the maxDepth parameter set for this initialiser.
     */
    public final int getMaxDepth(){
        return this.maxDepth;
    }
    /**
     * Update the maxDepth parameter for this initialiser.
     */
    public void setMaxDepth(final int newMaxDepth){
        if(maxDepth<0){
		this.maxDepth=0;
	}
	else{
		this.maxDepth=newMaxDepth;
	}
    }
    /**
     * Return the tail size percentage set for this initialiser.
     */
    public float getTailRatio(){
       return this.tailRatio; 
    }
    /**
     * Update the tail size percentage for this initialiser, and set tailSize to 0.
     */
    public void setTailRatio(final float newTailRatio){
        if(newTailRatio>=0.0){
		this.tailRatio=newTailRatio;
		this.tailSize=0;
	}
    }
    /**
     * Return the tail size set for this initialiser.
     */
    public final int getTailSize(){
        return this.tailSize;
    }
    /**
     * Update the tail size for this initialiser, and set tailRatio to 0.
     */
     public void setTailSize(final int newTailSize){
         this.tailSize=newTailSize;
         this.tailRatio=0;
    }
    /**
     * Grow the derivation tree according to the grow or full method, up to the 
     * maximumDepth specified.
     */
    public boolean growTree(Tree tree, final boolean growMethod, final int maximumDepth){
        //this.myRand.setSeed(System.currentTimeMillis());
        // Stop conditions
	if(tree.getCurrentLevel()>maximumDepth){
		return false;
	}
	if(tree.getData().getType()==SymbolType.TSymbol){
		return true;
	}
        Rule rulePtr=null;
        try{
            rulePtr=this.findRule(tree.getData());
        }
        catch(java.lang.NullPointerException e){
            System.out.println(e.getMessage());
        }
        catch(java.lang.Exception e){
            System.out.println(e.getMessage());
        }
        
        if(rulePtr == null){// No definition for the current non-terminal found
            if(tree.getData().getSymbol().startsWith("<GECodonValue")){
                //this.genotype.add(new Integer(this.myRand.nextInt(genotype.getMaxCodonValue())));
                this.genotype.add(new Integer(Math.round(genotype.getMaxCodonValue()*this.myRand.nextFloat(true, true))));
                //genotype.push_back(static_cast<CodonType>(genotype.getMaxCodonValue()*(static_cast<float>(rand())/RAND_MAX)));
                return true;
            }
            else if(tree.getData().getSymbol().compareTo("<GEXOMarker>")==0){
                return true;
            }
            else{
                this.genotype.setValid(false);
                this.phenotype.setValid(false);
                return true;
            }
        }
        else{
            Iterator<Production> prodIt=rulePtr.iterator();
            int ii=0;
            //ArrayList<Integer> possibleRules=new ArrayList();
            this.possibleRules.clear();
            
            boolean recursiveRules=false;// Flags the presence of recursive rules on full method
            while(prodIt.hasNext()){
                // Choose from all rules growing the individual
		// up to maximumDepth
                Production prod=prodIt.next();
                if(tree.getCurrentLevel()+prod.getMinimumDepth()<=this.getMaxDepth()){
                    if(!growMethod && !recursiveRules && prod.getRecursive()){
                        // Choose only recursive rules from now on
                        recursiveRules=true;
			this.possibleRules.clear();
                    }
                    if((growMethod)||(!recursiveRules)||((!growMethod)&&(recursiveRules)&&(prod.getRecursive()))){
                        this.possibleRules.add(new Integer(ii));
                    }
                }
                ii++;
            }
                // possibleRules now contains all valid rules
                if(this.possibleRules.isEmpty()){
                    return false;
                }
                else if(rulePtr.size()>1){
                    // Only choose production and insert it on genotype if there
                    // is more than 1 production associated with current rule
                    int denominator=Integer.MAX_VALUE+1;
                    int index= Math.round((float)(this.possibleRules.size()*this.myRand.nextDouble(true, false)));//Math.round((float)(this.possibleRules.size()*Math.random()));//
                    if(index>=this.possibleRules.size() && index!=0){
                        index=this.possibleRules.size()-1;
                    }
                        
                    this.genotype.add(this.possibleRules.get(index));
                    //save choice
                    prodIt=rulePtr.iterator();// What does this mean? prodIt=rulePtr->begin()+genotype.back();. Adil
                    int moveAhead=genotype.get(genotype.size()-1);
                    for(int i=0;i<moveAhead;i++){
                        prodIt.next();//Just trying something. Adil
                    }
                    // Perform "unmod" on choice
                    //Adil. Is this the right way to do it?
                    genotype.set(genotype.size()-1, genotype.get(genotype.size()-1)+(int)(genotype.getMaxCodonValue()/rulePtr.size()*this.myRand.nextDouble(true, false)));
                    //genotype.back()+=static_cast<CodonType>((genotype.getMaxCodonValue()/rulePtr->size()*(rand()/(RAND_MAX+1.0))))*rulePtr->size();
                }
                else{
                    // Otherwise set prodIt to point to the only production
                    prodIt=rulePtr.iterator();
                }
                // Insert symbols of chosen production on argument derivation tree,
		// and call grow tree for each symbol
                Iterator<Symbol> symbIt=prodIt.next().iterator();
		boolean result=true;
		int newMaxDepth=tree.getDepth();
                while(symbIt.hasNext()&& result){
                    tree.add(new Tree(symbIt.next(), tree.getCurrentLevel()+1, tree.getDepth()+1));
                    result=growTree(tree.get(tree.size()-1), growMethod, maximumDepth);
                    // Update maximum depth of tree
                    if(newMaxDepth<tree.get(tree.size()-1).getDepth()){
                        newMaxDepth=tree.get(tree.size()-1).getDepth();
                    }
                }
                this.genotype.setValid(result);
                this.phenotype.setValid(result);
                tree.setDepth(newMaxDepth);
                return result;
            }
        }
    /**
     * Initialise the Genotype and Phenotype structures, according to the sensible
     * initialisation technique for GE. If index is not set (or if it is set 
     * to UINT_MAX), initialise the structures as part of a series of calls to 
     * init(); if it is set, initialise the structures as being the index-th member 
     * (out of popSize) of the population. 
     * The next call to this routine will initialise the structures as being the
     * next individual of a population of popSize individuals. There is an 
     * exception to this rule:
     * 
     * If a specific index is set, then the structures are initialised as being 
     * the index-th individual of a population of popSize, and the next call 
     * to this routine will initialise the index-th+1 individual (unless a 
     * specific index is set again).
     */
    public boolean init(final int index){
        if(index!=2147483647){
		this.setIndex(index);
	}
        // Check depth validity
	if(maxDepth<1){
		System.err.println("Cannot initialise individual with maxDepth set to zero.\n");
		return false;
	}
        this.myRand.setSeed(System.currentTimeMillis());
        // Check for valid mapper
	if(!getValidGrammar()){
		System.err.println("Invalid Mapper, cannot initialise individual.\n");
		return false;
	}
        // check if start symbol minimumDepth smaller or equal to newMaxDepth
	final Rule startRule=this.getStartRule();
        if(startRule.getMinimumDepth()>=this.getMaxDepth()){// maxDepth is smaller
		System.err.println("Current maxDepth (" + Integer.toString(getMaxDepth()) +  ") is too small to initialise individual.\n");
		return false;
	}
        // Grow or Full?
	boolean grow=false;
        int idx=this.getIndex();
        int ps=this.getPopSize();
        if(idx<Math.round(ps*this.getGrow())){
            grow=true;
        }
        // Clear genotype
        this.genotype.clear();
        // Clear derivation tree, and add start symbol
        try{
            this.derivationTree.clear();
        }
        catch(java.lang.NullPointerException e){
            e.printStackTrace();
            return false;
        }
        this.derivationTree.setData(this.getStartSymbol());
        this.derivationTree.setCurrentLevel(1);
        this.derivationTree.setDepth(1);
        // Grow individual until reaching newDepth
        boolean returnValue;
        returnValue=this.growTree(derivationTree, grow, this.getMaxDepth());
        if(returnValue){
            this.genotype.setValid(true);
            if(!this.genotype2phenotype(true)){
                returnValue=false;
                //System.err.println("WARNING: invalid phenotype structure produced with Sensible Initialisation");
            }
        }
    	// Create tails if required
        int tailSize=0;
        if(this.getTailRatio()>0.0){
		tailSize=Math.round(genotype.size()*getTailRatio());
                
	}
        else{
            tailSize=this.getTailSize();
        }
        if(tailSize>0){
            // Create tail of size tailsize
            //this.myRand.setSeed(System.currentTimeMillis());
            for(int ii=0;ii<tailSize;ii++){
                this.genotype.add(Math.round(this.genotype.getMaxCodonValue()*this.myRand.nextFloat(true, true)));
            }
        }
        this.setIndex(this.getIndex()+1);
        return returnValue;
    }
    
    /**
     * Return the popsize
     * @return 
     */
    public final int getPopSize(){
        return this.popSize;
    }
    
    /**
     * 
     * set the popsize
     * @param newPopSize 
     */
    public void setPopSize(final int newPopSize){
        this.popSize=newPopSize;
    }
    
    /**
     * return the index.
     * @return 
     */
    public final int getIndex(){
        return this.popIndex;
    }
    /**
     * set the index
     * @param newPopIndex 
     */
    public void setIndex(final int newPopIndex){
        if(newPopIndex<0){
		this.popIndex=this.getPopSize()-((-newPopIndex)%this.getPopSize());
	}
	else if(newPopIndex>=this.getPopSize()){
            int popSize=this.getPopSize();
            if(popSize>0)
		this.popIndex=newPopIndex%popSize;
            else
                this.popIndex=1;
	}
	else{
		this.popIndex=newPopIndex;
	}
    }
    
    /**
     * Return the genotype as an integer array
     * @return 
     */
    public int[] getGenotypeIntArray(){
        Iterator<Integer> intItr=this.genotype.iterator();
        int[] geneArray=new int[this.genotype.size()];
        int i=0;
        while(intItr.hasNext()){
            geneArray[i]=intItr.next();
            i++;
        }
        return geneArray;
    }
}
