// Grammar.cpp -*- C++ -*-
#ifndef _GRAMMAR_CPP_
#define _GRAMMAR_CPP_

//#include <config.h>

#include<iostream>

#include "Grammar.h"

///////////////////////////////////////////////////////////////////////////////
// Default constructor.
Grammar::Grammar():Mapper(){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Grammar::Grammar()' called\n";
#endif
	setValidGrammar(false);
	startSymbol=0;
}

///////////////////////////////////////////////////////////////////////////////
// Constructor setting the genotype structure of this mapper to newGenotype.
Grammar::Grammar(const Genotype &newGenotype):Mapper(newGenotype){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Grammar::Grammar(const Genotype &,unsigned int=0)' called\n";
#endif
	setValidGrammar(false);
	startSymbol=0;
}

///////////////////////////////////////////////////////////////////////////////
// Constructor setting the phenotype structure of this mapper to newPhenotype.
Grammar::Grammar(const Phenotype &newPhenotype):Mapper(newPhenotype){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Grammar::Grammar(const Phenotype &,unsigned int=0)' called\n";
#endif
	setValidGrammar(false);
	startSymbol=0;
}

///////////////////////////////////////////////////////////////////////////////
// Copy constructor.
Grammar::Grammar(const Grammar& copy):Mapper(copy),vector<Rule>(copy){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Grammar::Grammar(const Grammar&)' called\n";
#endif
	setValidGrammar(copy.getValidGrammar());
	startSymbol=copy.startSymbol;
}

///////////////////////////////////////////////////////////////////////////////
// Destructor: delete all Productions first, and then all rules.
Grammar::~Grammar(){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Grammar::~Grammar()' called\n";
#endif
	iterator ruleIt=begin();
	while(ruleIt!=end()){
		(*ruleIt).clear();
		ruleIt++;
	}
	clear();
}

///////////////////////////////////////////////////////////////////////////////
// Return the validity of the current grammar.
bool Grammar::getValidGrammar() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'bool Grammar::getValidGrammar() const' called\n";
#endif
	return validGrammar;
}

///////////////////////////////////////////////////////////////////////////////
// Set the validity of the grammar.
void Grammar::setValidGrammar(const bool newValidGrammar){
#if (DEBUG_LEVEL >= 2)
	cerr << "'void Grammar::setValidGrammar(const bool)' called\n";
#endif
	validGrammar=newValidGrammar;
}

///////////////////////////////////////////////////////////////////////////////
// Return pointer to current start symbol.
const Symbol* Grammar::getStartSymbol() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'const Symbol* Grammar::getStartSymbol() const' called\n";
#endif
	//return front().lhs.front();
	return (*this)[startSymbol].lhs.front();
}

///////////////////////////////////////////////////////////////////////////////
// Change start symbol by index on Vector of rules.
bool Grammar::setStartSymbol(const unsigned int index){
#if (DEBUG_LEVEL >= 2)
	cerr << "'bool Grammar::setStartSymbol(const unsigned int)' called\n";
#endif
	if(index<size()){// Check boundaries.
		startSymbol=index;
		genotype2Phenotype();// Update phenotype.
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Change start symbol by symbol pointer.
bool Grammar::setStartSymbol(const Symbol *newStartSymbol){
#if (DEBUG_LEVEL >= 2)
	cerr << "'bool Grammar::setStartSymbol(const Symbol*)' called\n";
#endif
	int ii=0;
	iterator it=begin();
	while(it!=end()){
		// Work by *pointer*.
		if(it->lhs.front()==newStartSymbol){
			startSymbol=ii;
			genotype2Phenotype();// Update phenotype.
			return true;
		}
		it++;ii++;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Change start symbol by string.
bool Grammar::setStartSymbol(const string &newStartSymbol){
#if (DEBUG_LEVEL >= 2)
	cerr << "'bool Grammar::setStartSymbol(const string&)' called\n";
#endif
	int ii=0;
	iterator it=begin();
	while(it!=end()){
		// Work by *string*.
		string currentStartSymbol=*(it->lhs.front());
		if(currentStartSymbol==newStartSymbol){
			startSymbol=ii;
			genotype2Phenotype();// Update phenotype.
			return true;
		}
		it++;ii++;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Return pointer to current start rule.
const Rule* Grammar::getStartRule() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'const Rule* Grammar::getStartRule() const' called\n";
#endif
	return &front();
}

#endif

