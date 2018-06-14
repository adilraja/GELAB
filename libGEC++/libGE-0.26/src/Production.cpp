// Production.cpp -*- C++ -*-
#ifndef _PRODUCTION_CPP_
#define _PRODUCTION_CPP_

//#include<config.h>

#include<iostream>

#include"Production.h"

///////////////////////////////////////////////////////////////////////////////
// Creates a new Production with newLength elements.
Production::Production(const unsigned int newLength):vector<Symbol*>(){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Production::Production(const unsigned int)' called\n";
#endif
	resize(newLength);
	setRecursive(false);
	setMinimumDepth(INT_MAX>>1);
}

///////////////////////////////////////////////////////////////////////////////
// Copy constructor; copy all symbols.
Production::Production(const Production &copy){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Production::Production(const Production &copy)' called\n";
#endif
	const_iterator it=copy.begin();
	while(it!=copy.end()){
		if((*it)->getType()==TSymbol){
			// Terminal symbol, create new one
			push_back(new Symbol(**it));
		}
		else{
			push_back(*it);
		}
		it++;
	}
	setRecursive(copy.recursive);
	setMinimumDepth(copy.minimumDepth);
}

///////////////////////////////////////////////////////////////////////////////
// Destructor; call redefined operator clear().
Production::~Production(){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Production::~Production()' called\n";
#endif
	clear();
}

///////////////////////////////////////////////////////////////////////////////
// Delete all terminal symbols and all symbol references.
void Production::clear(){
#if (DEBUG_LEVEL >= 2)
	cerr << "'void Production::clear()' called\n";
#endif
	iterator it=begin();
	while(it!=end()){
		if((*it)->getType()==TSymbol){
			// Terminal symbol, delete
		delete *it;
		}
		else{
		}
		it++;
	}
	erase(begin(),end());
}

///////////////////////////////////////////////////////////////////////////////
// Return the recursive nature of this production.
bool Production::getRecursive() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'bool Production::getRecursive() const' called\n";
#endif
	return recursive;
}

///////////////////////////////////////////////////////////////////////////////
// Update the recursive nature of this production.
void Production::setRecursive(const bool newRecursive){
#if (DEBUG_LEVEL >= 2)
	cerr << "'bool Production::setRecursive(const bool)' called\n";
#endif
	recursive=newRecursive;
}

///////////////////////////////////////////////////////////////////////////////
// Return the minimum mapping depth of this production.
unsigned int Production::getMinimumDepth() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'unsigned int Production::getMinimumDepth() const' called\n";
#endif
	return minimumDepth;
}

///////////////////////////////////////////////////////////////////////////////
// Update the minimum mapping depth of this production.
void Production::setMinimumDepth(const unsigned int newMinimumDepth){
#if (DEBUG_LEVEL >= 2)
	cerr << "'int Production::setMinimumDepth(const unsigned int)' called\n";
#endif
	minimumDepth=newMinimumDepth;
}

///////////////////////////////////////////////////////////////////////////////
// Pretty print the contents of the production.
ostream &operator<<(ostream &stream, const Production &p){
#if (DEBUG_LEVEL >= 2)
	cerr << "'ostream &operator<<(ostream &, const Production &)' called\n";
#endif
	string output;
	Production::const_iterator it=p.begin();
	while(it!=p.end()){
		output+=**it;
		it++;
	}
	return stream << output;
}

#endif

