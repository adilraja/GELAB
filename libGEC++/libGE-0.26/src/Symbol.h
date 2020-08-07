// Symbol.h -*- C++ -*-
#ifndef _SYMBOL_H_
#define _SYMBOL_H_

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* This class implements a symbol of a grammar, be it a non-terminal or      */
/* terminal symbol. It is used both by the Rule class, to specify its left   */
/* side non-terminal symbols, and by the Production class, to specify its    */
/* terminal and non-terminal symbols.                                        */
/* It is also used by the Phenotype class, to specify phenotypic symbols.    */
/* It can hold any data type, but all data types will be treated as text, so */
/* for example no arithmetic operations are possible.                        */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "libGEdefs.h"

#include<iostream>
#include<vector>
#include<string>
#include<sstream>

// Types for symbols
enum SymbolType {NTSymbol,TSymbol};

using namespace std;

class Symbol : public string{
	public:
		Symbol(const string = "", const SymbolType = TSymbol);
		Symbol(const Symbol&);
		~Symbol();
		SymbolType getType() const;
		void setType(const SymbolType);
		template <class T>Symbol &operator=(const T);
		bool operator==(const Symbol&);
	private:
		SymbolType type;
};

///////////////////////////////////////////////////////////////////////////////
// Copy newValue as textual contents of Symbol.
template <class T>
Symbol &Symbol::operator=(const T newValue){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'Symbol &Symbol::operator=(const <T>)' called\n";
	#endif
	ostringstream oss;
	oss << newValue;
	assign(oss.str());
	return *this;
}

#endif

