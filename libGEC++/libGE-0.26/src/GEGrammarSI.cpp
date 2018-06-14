// GEGrammarSI.cpp -*- C++ -*-
#ifndef _GEGRAMMARSI_CPP_
#define _GEGRAMMARSI_CPP_

//#include <config.h>

#include<iostream>

#include "GEGrammarSI.h"

///////////////////////////////////////////////////////////////////////////////
// Default constructor.
GEGrammarSI::GEGrammarSI():GEGrammar(),Initialiser(){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'GEGrammarSI::GEGrammarSI()' called\n";
	#endif
	// Initialiser settings
	setGrow(0.0);
	setMaxDepth(1);
	setTailRatio(0.0);
	setTailSize(0);
}

///////////////////////////////////////////////////////////////////////////////
// Constructor setting the genotype structure of this mapper to newGenotype.
GEGrammarSI::GEGrammarSI(const Genotype &newGenotype):GEGrammar(newGenotype){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'GEGrammarSI::GEGrammarSI(const Genotype &)' called\n";
	#endif
	setGrow(0.0);
	setMaxDepth(1);
	setTailRatio(0.0);
	setTailSize(0);
}

///////////////////////////////////////////////////////////////////////////////
// Constructor setting the phenotype structure of this mapper to newPhenotype.
GEGrammarSI::GEGrammarSI(const Phenotype &newPhenotype):GEGrammar(newPhenotype){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'GEGrammarSI::GEGrammarSI(const Phenotype &)' called\n";
	#endif
	setGrow(0.0);
	setMaxDepth(1);
	setTailRatio(0.0);
	setTailSize(0);
}

///////////////////////////////////////////////////////////////////////////////
// Copy Constructor.
GEGrammarSI::GEGrammarSI(const GEGrammarSI& copy):GEGrammar(copy),Initialiser(copy){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'GEGrammarSI::GEGrammarSI(const GEGrammarSI&)' called\n";
	#endif
	setGrow(copy.getGrow());
	setMaxDepth(copy.getMaxDepth());
	setTailRatio(copy.getTailRatio());
	setTailSize(copy.getTailSize());
}

///////////////////////////////////////////////////////////////////////////////
// Destructor.
GEGrammarSI::~GEGrammarSI(){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'GEGrammarSI::~GEGrammarSI()' called\n";
	#endif
}

///////////////////////////////////////////////////////////////////////////////
// Return the grow percentage set for this initialiser.
float GEGrammarSI::getGrow() const{
	#if (DEBUG_LEVEL >= 2)
	cerr << "'float GEGrammarSI::getGrow() const' called\n";
	#endif
	return grow;
}

///////////////////////////////////////////////////////////////////////////////
// Update the grow percentage for this initialiser.
void GEGrammarSI::setGrow(const float newGrow){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'void GEGrammarSI::setGrow(const float)' called\n";
	#endif
	if((newGrow<0.0)||(newGrow>1.0)){
		grow=0.0;
	}
	else{
		grow=newGrow;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Return the full percentage set for this initialiser.
float GEGrammarSI::getFull() const{
	#if (DEBUG_LEVEL >= 2)
	cerr << "'float GEGrammarSI::getFull() const' called\n";
	#endif
	return 1.0-grow;
}

///////////////////////////////////////////////////////////////////////////////
// Update the full percentage for this initialiser.
void GEGrammarSI::setFull(const float newFull){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'void GEGrammarSI::setFull(const float)' called\n";
	#endif
	if((newFull<0.0)||(newFull>1.0)){
		grow=0.0;
	}
	else{
		grow=1.0-newFull;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Return the maxDepth parameter set for this initialiser.
unsigned int GEGrammarSI::getMaxDepth() const{
	#if (DEBUG_LEVEL >= 2)
	cerr << "'unsigned int GEGrammarSI::getMaxDepth() const' called\n";
	#endif
	return maxDepth;
}

///////////////////////////////////////////////////////////////////////////////
// Update the maxDepth parameter for this initialiser.
void GEGrammarSI::setMaxDepth(const unsigned int newMaxDepth){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'void GEGrammarSI::setMaxDepth(const unsigned int)' called\n";
	#endif
	if(maxDepth<0){
		maxDepth=0;
	}
	else{
		maxDepth=newMaxDepth;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Return the tail size percentage set for this initialiser.
float GEGrammarSI::getTailRatio() const{
	#if (DEBUG_LEVEL >= 2)
	cerr << "'float GEGrammarSI::getTailRatio() const' called\n";
	#endif
	return tailRatio;
}

///////////////////////////////////////////////////////////////////////////////
// Update the tail size percentage for this initialiser, and set tailSize to 0.
void GEGrammarSI::setTailRatio(const float newTailRatio){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'void GEGrammarSI::setTailRatio(const float)' called\n";
	#endif
	if(newTailRatio>=0.0){
		tailRatio=newTailRatio;
		tailSize=0;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Return the tail size set for this initialiser.
unsigned int GEGrammarSI::getTailSize() const{
	#if (DEBUG_LEVEL >= 2)
	cerr << "'unsigned int GEGrammarSI::getTailSize() const' called\n";
	#endif
	return tailSize;
}

///////////////////////////////////////////////////////////////////////////////
// Update the tail size for this initialiser, and set tailRatio to 0.
void GEGrammarSI::setTailSize(const unsigned int newTailSize){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'void GEGrammarSI::setTailSize(const unsigned int)' called\n";
	#endif
	tailSize=newTailSize;
	tailRatio=0.0;
}

///////////////////////////////////////////////////////////////////////////////
// Grow the derivation tree according to the grow or full method, up to the
// maximumDepth specified.
bool GEGrammarSI::growTree(DerivationTree &tree,const bool &growMethod,const unsigned int &maximumDepth){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'bool GEGrammarSI::growTree(DerivationTree&, const bool&, const int&)' called\n";
	#endif

	// Stop conditions
	if(tree.getCurrentLevel()>maximumDepth){
		return false;
	}
	if(tree.getData()->getType()==TSymbol){
		return true;
	}

	Rule *rulePtr;
	if(!(rulePtr=findRule(*(tree.getData())))){// No definition for the current non-terminal found
		if((*(tree.getData())).substr(0,strlen("<GECodonValue"))=="<GECodonValue"){
		//if (*(tree.getData())=="<GECodonValue>"){
			genotype.push_back(static_cast<CodonType>(genotype.getMaxCodonValue()*(static_cast<float>(rand())/RAND_MAX)));
			return true;
		}
		else if (*(tree.getData())=="<GEXOMarker>"){
			return true;
		}
		else{
			genotype.setValid(false);
			phenotype.setValid(false);
			return true;
		}
	}
	else{
		Rule::const_iterator prodIt=rulePtr->begin();
		int ii=0;
		vector<int> possibleRules;// The possible rules to choose from
		possibleRules.clear();
		bool recursiveRules=false;// Flags the presence of recursive rules on full method
		while(prodIt!=rulePtr->end()){
			// Choose from all rules growing the individual
			// up to maximumDepth
			if((tree.getCurrentLevel()+prodIt->getMinimumDepth())<=maximumDepth){
				if((!growMethod)&&(!recursiveRules)&&(prodIt->getRecursive())){
					// Choose only recursive rules from now on
					recursiveRules=true;
					possibleRules.clear();
				}
				if((growMethod)||(!recursiveRules)||((!growMethod)&&(recursiveRules)&&(prodIt->getRecursive()))){
					possibleRules.push_back(ii);
				}
			}
			prodIt++;
			ii++;
		}
		// possibleRules now contains all valid rules
		if(possibleRules.empty()){
			return false;
		}
		else if(rulePtr->size()>1){
			// Only choose production and insert it on genotype if there
			// is more than 1 production associated with current rule
			genotype.push_back(possibleRules[static_cast<CodonType>(possibleRules.size()*(rand()/(RAND_MAX+1.0)))]);
			// Save choice
			prodIt=rulePtr->begin()+genotype.back();
			// Perform "unmod" on choice
			genotype.back()+=static_cast<CodonType>((genotype.getMaxCodonValue()/rulePtr->size()*(rand()/(RAND_MAX+1.0))))*rulePtr->size();
		}
		else{
			// Otherwise set prodIt to point to the only production
			prodIt=rulePtr->begin();
		}
		// Insert symbols of chosen production on argument derivation tree,
		// and call grow tree for each symbol
		Production::const_iterator symbIt=prodIt->begin();
		bool result=true;
		unsigned int newMaxDepth=tree.getDepth();
		while((symbIt!=prodIt->end())&&result){
			tree.push_back(DerivationTree(*symbIt,tree.getCurrentLevel()+1,tree.getDepth()+1));
			result=growTree(tree.back(),growMethod,maximumDepth);
			// Update maximum depth of tree
			if(newMaxDepth<tree.back().getDepth()){
				newMaxDepth=tree.back().getDepth();
			}
			symbIt++;
		}
		genotype.setValid(result);
		phenotype.setValid(result);
		tree.setDepth(newMaxDepth);
		return result;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Initialise the Genotype and Phenotype structures, according to the sensible
// initialisation technique for GE. If index is not set (or if it is set
// to UINT_MAX), initialise the structures as part of a series of calls to
// init(); if it is set, initialise the structures as being the index-th member
// (out of popSize) of the population.
// The next call to this routine will initialise the structures as being the
// next individual of a population of popSize individuals. There is an
// exception to this rule:
// * If a specific index is set, then the structures are initialised as being
// the index-th individual of a population of popSize, and the next call
// to this routine will initialise the index-th+1 individual (unless a
// specific index is set again).
bool GEGrammarSI::init(const unsigned int index){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'bool GEGrammarSI::init(const unsigned int)' called\n";
	#endif
	if(index!=UINT_MAX){
		setIndex(index);
	}

	// Check depth validity
	if(maxDepth<1){
		cerr << "Cannot initialise individual with maxDepth set to zero.\n";
		return false;
	}
	// Check for valid mapper
	if(!getValidGrammar()){
		cerr << "Invalid Mapper, cannot initialise individual.\n";
		return false;
	}
	// check if start symbol minimumDepth smaller or equal to newMaxDepth
	const Rule *startRule=getStartRule();
	if(startRule->getMinimumDepth()>=getMaxDepth()){// maxDepth is smaller
		cerr << "Current maxDepth (" << getMaxDepth() <<  ") is too small to initialise individual.\n";
		return false;
	}

	// Grow or Full?
	bool grow=(getIndex()<static_cast<unsigned int>(getPopSize()*getGrow()));
	// Clear genotype
	genotype.clear();
	// Clear derivation tree, and add start symbol
	derivationTree.clear();
	derivationTree.setData(getStartSymbol());
	derivationTree.setCurrentLevel(1);
	derivationTree.setDepth(1);

	// Grow individual until reaching newDepth
	bool returnValue;
	returnValue=growTree(derivationTree,grow,getMaxDepth());
	if(returnValue){
		genotype.setValid(true);
		if (!genotype2Phenotype()){
			cerr << "WARNING: invalid phenotype structure produced with Sensible Initialisation\n";
		}
	}
	// Create tails if required
	unsigned int tailsize=0;
	if(getTailRatio()>0.0){
		tailsize=static_cast<unsigned int>(genotype.size()*getTailRatio());
	}
	else{
		tailsize=getTailSize();
	}
	if(tailsize){
		// Create tail of size tailsize
		for(unsigned int ii=0;ii<tailsize;ii++){
			genotype.push_back(static_cast<CodonType>(genotype.getMaxCodonValue()*(static_cast<float>(rand())/RAND_MAX)));
		}
	}
	setIndex(getIndex()+1);
	return returnValue;
}

#endif

