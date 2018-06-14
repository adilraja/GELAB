// Rule.cpp -*- C++ -*-
#ifndef _RULE_CPP_
#define _RULE_CPP_

//#include <config.h>

#include<iostream>

#include"Rule.h"

///////////////////////////////////////////////////////////////////////////////
// Creates a new rule with newLength elements.
Rule::Rule(const unsigned int newLength):vector<Production>(){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Rule::Rule(unsigned int)' called\n";
#endif
	resize(newLength);
	setRecursive(false);
	setMinimumDepth(INT_MAX>>1);
}

///////////////////////////////////////////////////////////////////////////////
// Copy constructor.
Rule::Rule(const Rule &copy):vector<Production>(copy){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Rule::Rule(Rule const &copy)' called\n";
#endif
	vector<Symbol*>::const_iterator lhsIt=copy.lhs.begin();
	while(lhsIt!=copy.lhs.end()){
		lhs.push_back(new Symbol(**lhsIt));
		lhsIt++;
	}
	setRecursive(copy.getRecursive());
	setMinimumDepth(copy.getMinimumDepth());
}

///////////////////////////////////////////////////////////////////////////////
// Destructor; call redefined operator clear().
Rule::~Rule(){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Rule::~Rule()' called\n";
#endif
	clear();
}

///////////////////////////////////////////////////////////////////////////////
// Delete all productions, and all symbols stored in lhs.
void Rule::clear(){
#if (DEBUG_LEVEL >= 2)
	cerr << "'void Rule::clear()' called\n";
#endif
	vector<Symbol*>::iterator it=lhs.begin();
	while(it!=lhs.end()){
		delete *it;
		it++;
	}
	lhs.clear();// Clear lhs vector
	erase(begin(),end());// Clear production vector
}

///////////////////////////////////////////////////////////////////////////////
// Return the recursive nature of this rule.
bool Rule::getRecursive() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'bool Rule::getRecursive() const' called\n";
#endif
	return recursive;
}

///////////////////////////////////////////////////////////////////////////////
// Update the recursive nature of this rule.
void Rule::setRecursive(const bool newRecursive){
#if (DEBUG_LEVEL >= 2)
	cerr << "'void Rule::setRecursive(bool const)' called\n";
#endif
	recursive=newRecursive;
}

///////////////////////////////////////////////////////////////////////////////
// Return the minimum mapping depth of this rule.
unsigned int Rule::getMinimumDepth() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'int Rule::getMinimumDepth() const' called\n";
#endif
	return minimumDepth;
}

///////////////////////////////////////////////////////////////////////////////
// Update the minimum mapping depth of this Rule.
void Rule::setMinimumDepth(const unsigned int newMinimumDepth){
#if (DEBUG_LEVEL >= 2)
	cerr << "'int Rule::setMinimumDepth(int const)' called\n";
#endif
	minimumDepth=newMinimumDepth;
}

#endif

