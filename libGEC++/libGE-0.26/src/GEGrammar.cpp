// GEGrammar.cpp -*- C++ -*-
#ifndef _GEGRAMMAR_CPP_
#define _GEGRAMMAR_CPP_

//#include<config.h>

#include<cstdio>
#include<iostream>
#include<sstream>
#include<cstring>
#include<vector>
#include<stack>

#include"GEGrammar.h"

///////////////////////////////////////////////////////////////////////////////
// Default constructor.
GEGrammar::GEGrammar():CFGrammar(){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'GEGrammar::GEGrammar()' called\n";
	#endif
	setMaxWraps(0);
}

///////////////////////////////////////////////////////////////////////////////
// Constructor setting the genotype structure of this mapper to newGenotype.
GEGrammar::GEGrammar(const Genotype &newGenotype):CFGrammar(newGenotype){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'GEGrammar::GEGrammar(const Genotype &)' called\n";
	#endif
	setMaxWraps(0);
}

///////////////////////////////////////////////////////////////////////////////
// Constructor setting the phenotype structure of this mapper to newPhenotype.
GEGrammar::GEGrammar(const Phenotype &newPhenotype):CFGrammar(newPhenotype){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'GEGrammar::GEGrammar(const Phenotype &)' called\n";
	#endif
	setMaxWraps(0);
}

///////////////////////////////////////////////////////////////////////////////
// Copy Constructor.
GEGrammar::GEGrammar(const GEGrammar& copy):CFGrammar(copy){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'GEGrammar::GEGrammar(const GEGrammar&)' called\n";
	#endif
	setMaxWraps(copy.getMaxWraps());
	// Call genotype2Phenotype() to regenerate phenotype structure,
	// and productions and derivationTree structures.
	genotype2Phenotype(true);
}

///////////////////////////////////////////////////////////////////////////////
// Destructor.
GEGrammar::~GEGrammar(){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'GEGrammar::~GEGrammar()' called\n";
	#endif
}

///////////////////////////////////////////////////////////////////////////////
// Return number of maximum allowed wrapping events.
unsigned int GEGrammar::getMaxWraps() const{
	#if (DEBUG_LEVEL >= 2)
	cerr << "'unsigned int GEGrammar::getMaxWraps() const' called\n";
	#endif
	return maxWraps;
}

///////////////////////////////////////////////////////////////////////////////
// Set the new number of maximum allowed wrapping events.
void GEGrammar::setMaxWraps(const unsigned int newMaxWraps){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'void GEGrammar::setMaxWraps(const unsigned int)' called\n";
	#endif
	maxWraps=newMaxWraps;
}

///////////////////////////////////////////////////////////////////////////////
// Builds the the current derivation tree, and returns its address;
// if derivation tree is impossible to build, returns NULL.
const DerivationTree* GEGrammar::getDerivationTree(){
#if (DEBUG_LEVEL >= 2)
	cerr << "'const DerivationTree* GEGrammar::getDerivationTree()' called\n";
#endif
	if((!getValidGrammar())||(!genotype.getValid())||(!getGenotype()->size())){
		return NULL;
	}
	genotype2Phenotype(true);
	return &derivationTree;
}

///////////////////////////////////////////////////////////////////////////////
// Returns a vector of all productions used during the mapping process.
const vector<Production*>* GEGrammar::getProductions(){
#if (DEBUG_LEVEL >= 2)
	cerr << "'const DerivationTree* GEGrammar::getDerivationTree()' called\n";
#endif
	if((!getValidGrammar())||(!genotype.getValid())||(!getGenotype()->size())){
		return NULL;
	}
	genotype2Phenotype(true);
	return &productions;
}

///////////////////////////////////////////////////////////////////////////////
// Strict implementation of genotype2Phenotype interface. Calls local
// genotype2Phenotype(bool) method, with bool=false.
bool GEGrammar::genotype2Phenotype(){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'bool GEGrammar::genotype2Phenotype()' called\n";
	#endif
	return genotype2Phenotype(false);
}

///////////////////////////////////////////////////////////////////////////////
// Updates the contents of the phenotype structure, based on the current
// genotype and the current grammar, and according to the standard GE
// mapping process. Returns true upon a successful mapping, and false
// otherwise, and also updates the valid field of the phenotype.
// With argument set to true, also updates derivationTree.
bool GEGrammar::genotype2Phenotype(const bool buildDerivationTree){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'bool GEGrammar::genotype2Phenotype(const bool)' called\n";
	#endif
	bool returnValue=true;
	unsigned int newEffectiveSize=0;
	// Start by setting effectiveSize to 0
	genotype.setEffectiveSize(newEffectiveSize);

	phenotype.clear();
	if(buildDerivationTree){
		productions.clear();
	}
	// Quick safety checks
	//if((!getValidGrammar())||(!genotype.getValid())||(!getGenotype()->size())){
	if(!getValidGrammar()){
		phenotype.clear();
		phenotype.setValid(false);
		return false;
	}

	// Wraps counter and nonterminals stack
	unsigned int wraps=0;
	stack<const Symbol*> nonterminals;

	// Iterators
	iterator ruleIt;
	Rule::iterator prodIt;
	Genotype::iterator genoIt=genotype.begin();

	// Start with the start symbol
	nonterminals.push(getStartSymbol());
	if(buildDerivationTree){
		// Use start symbol as the derivationTree node
		derivationTree.setData(getStartSymbol());
	}

	bool gotToUseWrap=false;
	// Get rid of all non-terminal symbols
	while((!nonterminals.empty())&&(wraps<=getMaxWraps())){
		// Do a mapping step
		switch(genotype2PhenotypeStep(nonterminals,genoIt,buildDerivationTree)){
			case -1:returnValue=false;
				break;
			case 0:	;
				break;
			case 1:	genoIt++;
				newEffectiveSize++;
				if(gotToUseWrap){
					wraps++;
					gotToUseWrap=false;
				}
				// Check if wrap is needed
				if(genoIt==genotype.end()){
					//newEffectiveSize+=genotype.size();
					genoIt=genotype.begin();
					gotToUseWrap=true;
				}
				break;
			default:cerr << "Internal error in genotype2Phenotype().\n";
				cerr << "Execution aborted.\n";
				exit(0);
		}
	}
	//newEffectiveSize+=(genoIt-genotype.begin());
	// Was the mapping successful?
	if((wraps>getMaxWraps())||(!nonterminals.empty())){
		returnValue=false;
		// Add remaining symbols in nonterminals queue to phenotype
		while(!nonterminals.empty()){
			phenotype.push_back(nonterminals.top());
			nonterminals.pop();
		}
	}
	phenotype.setValid(returnValue);
	genotype.setEffectiveSize(newEffectiveSize);
	genotype.setWraps(wraps);
	// Now build derivation tree, based on productions vector
	if(buildDerivationTree){
		derivationTree.clear();
		derivationTree.setData(getStartSymbol());
		derivationTree.setCurrentLevel(1);
		derivationTree.setDepth(1);
		vector<Production*>::iterator prodIt=productions.begin();
		buildDTree(derivationTree,prodIt);
	}
	return returnValue;
}

///////////////////////////////////////////////////////////////////////////////
// Updates the contents of the genotype structure, based on the current
// phenotype and the current grammar, and according to a mapping process
// corresponding to the inverse of the standard GE mapping process.
// Returns true upon a successful inverse mapping, and false otherwise.
bool GEGrammar::phenotype2Genotype(){
#if (DEBUG_LEVEL >= 2)
	cerr << "'bool GEGrammar::phenotype2Genotype()' called\n";
#endif
	cerr << "Method not yet implemented in this release of libGE.\n";
	return false;
//FIXME
}

///////////////////////////////////////////////////////////////////////////////
// Performs one step of the mapping process, that is, maps the next
// non-terminal symbol on the nonterminals stack passed as argument, using the
// codon at the position pointed by genoIt.
// Returns number of codons consumed, -1 if not successful
int GEGrammar::genotype2PhenotypeStep(stack<const Symbol*> &nonterminals,
		Genotype::iterator genoIt, bool buildDerivationTree){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'bool GEGrammar::genotype2PhenotypeStep(stack<const Symbol*>&,Genotype::iterator&,bool)' called\n";
	#endif
	Rule::iterator prodIt;
	int returnValue;

	// Find the rule for the current non-terminal
	Rule *rulePtr=findRule(*(nonterminals.top()));
	//cerr << "mapping " << *(nonterminals.top()) << " with " << *genoIt << "\n";

	if(!rulePtr){// Undefined symbol - could be an extension symbol
		if(((*(nonterminals.top())).substr(0,strlen("<GECodonValue"))==
			"<GECodonValue")&&(genoIt!=genotype.end())){
			// Insert codon value
			// Extract range for value from non-terminal specification
			int low=0,high=-1,pointer=strlen("<GECodonValue");
			// currentChar is the first character after "<GECodonValue"
			char currentChar=((*(nonterminals.top())).substr(pointer,1))[0];
			// Look for range definitions
			while(currentChar!='>'){
				if(currentChar=='-'){
					// Low range specification
					currentChar=((*(nonterminals.top())).substr(++pointer,1))[0];
					while((currentChar>='0')&&(currentChar<='9')){
						low=(low*10)+(currentChar-'0');
						currentChar=((*(nonterminals.top())).substr(++pointer,1))[0];
					}
				}
				else if(currentChar=='+'){
					// High range specification
					currentChar=((*(nonterminals.top())).substr(++pointer,1))[0];
					while((currentChar>='0')&&(currentChar<='9')){
						if(high==-1){
							high=0;
						}
						high=(high*10)+(currentChar-'0');
						currentChar=((*(nonterminals.top())).substr(++pointer,1))[0];
					}
				}
				else{// Ignore errors
					currentChar=((*(nonterminals.top())).substr(++pointer,1))[0];
				}
			}
			// High range was not specified, so set it to maximum
			if(high==-1){
				high=genotype.getMaxCodonValue();
			}
			// Remove non-terminal
			nonterminals.pop();
			// Print value onto "codon"
			ostringstream codon;
			if(high==low){
				// Catch division by zero
				codon << low;
			}
			else{
				codon << (*genoIt%(high-low+1))+low;;
			}
			// Insert symbol with value onto phenotype
			phenotype.push_back(new Symbol(codon.str()));
			returnValue=1;
		}
		else{
			// Unknown symbol or special symbol that requires non-empty genotype
			// Include symbol on phenotype
			phenotype.push_back(nonterminals.top());
			// Remove non-terminal
			nonterminals.pop();
			// Invalidate mapping
			returnValue=-1;
		}
	}
	//else if(rulePtr->getMinimumDepth()>=INT_MAX>>1){// Stuck on recursive rule
	// Allow recursive rules, but only if they consume a codon
	else if((rulePtr->getMinimumDepth()>=INT_MAX>>1)// Stuck on recursive rule
		&&(rulePtr->size()<=1)){// No codon will be consumed
		// Include symbol on phenotype
		phenotype.push_back(nonterminals.top());
		// Remove non-terminal
		nonterminals.pop();
		// Invalidate mapping
		returnValue=-1;
	}
	else{
		// Remove non-terminal
		nonterminals.pop();
		// Choose production
		if((genoIt==genotype.end())&&(rulePtr->size()>1)){
			// Empty genotype, but symbol requires choice
			// Include symbol on phenotype
			phenotype.push_back(*(rulePtr->lhs.begin()));
			// Invalidate mapping
			returnValue=-1;
		}
		else{
			if(genoIt==genotype.end()){//Empty genotype
				prodIt=rulePtr->begin();
			}
			else{
				prodIt=rulePtr->begin()+*genoIt%(rulePtr->size());
			}
			// Place production on productions vector
			if(buildDerivationTree){
				productions.push_back(&*prodIt);
			}
			// Put all terminal symbols at start of production onto phenotype
			int s_start=0;
			int s_stop=(*prodIt).size();
			while((s_start<s_stop)&&((*prodIt)[s_start]->getType()==TSymbol)){
				phenotype.push_back((*prodIt)[s_start]);
				s_start++;
			}
			// Push all remaining symbols from production onto nonterminals queue, backwards
			for(;s_stop>s_start;s_stop--){
				nonterminals.push((*prodIt)[s_stop-1]);
			}
			// 0 or 1 choice for current rule, didn't consume genotype codon
			if(rulePtr->size()<=1){
				returnValue=0;
			}
			else{
				returnValue=1;
			}
		}
	}
	// Finally, pop all terminal symbols on top of stack and insert onto phenotype
	while((!nonterminals.empty()) && (nonterminals.top()->getType()==TSymbol)){
		phenotype.push_back(nonterminals.top());
		nonterminals.pop();
	}
	return returnValue;
}

///////////////////////////////////////////////////////////////////////////////
// Builds the derivation tree, based on the productions vector.
// Arguments are current tree node, and iterator on productions vector.
void GEGrammar::buildDTree(DerivationTree &currentNode, vector<Production*>::iterator &prodIt){
#if (DEBUG_LEVEL >= 2)
	cerr << "'bool GEGrammar::buildDTree(vector<Production*>::iterator&)' called\n";
#endif
	// If current symbol is not a non-terminal, or if all productions have been treated
	if((currentNode.getData()->getType()!=NTSymbol)||(prodIt==productions.end())){
		// Correct productions iterator, as no production was read from it
		prodIt--;
		return;
	}
	// Create new tree level
	Production::iterator symbIt=(*prodIt)->begin();
	while(symbIt!=(*prodIt)->end()){
		currentNode.push_back(DerivationTree(*symbIt,currentNode.getCurrentLevel()+1,
					currentNode.getDepth()+1));
		symbIt++;
		}
	// Expand each child node
	DerivationTree::iterator treeIt=currentNode.begin();
	while(treeIt!=currentNode.end()){
		buildDTree(*treeIt,++prodIt);
		treeIt++;
	}
}

#endif

