// Symbol.cpp -*- C++ -*-
#ifndef _SYMBOL_CPP_
#define _SYMBOL_CPP_

//#include <config.h>

#include<iostream>
#include<string>
#include<vector>

#include "Symbol.h"

///////////////////////////////////////////////////////////////////////////////
// Create a new Symbol object as a copy of newArray and with type newType, if
// specified; otherwise the default values specified in the function prototype
// are used.
Symbol::Symbol(const string newArray, const SymbolType newType){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Symbol::Symbol(const string, const SymbolType)' called\n";
#endif
	*this=newArray;
	setType(newType);
}

///////////////////////////////////////////////////////////////////////////////
// Copy constructor.
Symbol::Symbol(const Symbol &copy){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Symbol::Symbol(const Symbol&)' called\n";
#endif
	append(copy);
	setType(copy.getType());
}


///////////////////////////////////////////////////////////////////////////////
// Destructor.
Symbol::~Symbol(){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Symbol::~Symbol()' called\n";
#endif
}

///////////////////////////////////////////////////////////////////////////////
// Return the type of the symbol (NTSymbol or TSymbol).
SymbolType Symbol::getType() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'SymbolType Symbol::getType() const' called\n";
#endif
	return type;
}

///////////////////////////////////////////////////////////////////////////////
// Set the type of the symbol.
void Symbol::setType(const SymbolType newType){
#if (DEBUG_LEVEL >= 2)
	cerr << "'void Symbol::setType(const SymbolType)' called\n";
#endif
	type=newType;
}

///////////////////////////////////////////////////////////////////////////////
// Symbol comparison operator.
bool Symbol::operator==(const Symbol &newSymbol){
#if (DEBUG_LEVEL >= 2)
	cerr << "'bool Symbol::operator==(const Symbol&)' called\n";
#endif
	if ((!compare(newSymbol))&&getType()==newSymbol.getType()){
		return true;
	}
	return false;
} 

#endif

