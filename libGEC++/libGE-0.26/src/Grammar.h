// Grammar.h -*- C++ -*-
#ifndef _GRAMMAR_H_
#define _GRAMMAR_H_

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* This is an abstract class that cannot be instantiated; it defines the     */
/* basic characteristics and functionality of a Grammar mapper. It is        */
/* composed of a vector of Rule objects, defining a grammar, and of fields   */
/* defining the maximum number of allowed wrapping events and the validity   */
/* of the current grammar.                                                   */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "libGEdefs.h"

#include<vector>
#include<string>

#include "Mapper.h"
#include "Rule.h"

using namespace std;

class Grammar : public Mapper, public vector<Rule>{
	public:
		Grammar();
		Grammar(const Genotype &);
		Grammar(const Phenotype &);
		Grammar(const Grammar&);
		virtual ~Grammar();
		bool getValidGrammar() const;
		const Symbol* getStartSymbol() const;
		bool setStartSymbol(const unsigned int);
		bool setStartSymbol(const Symbol*);
		bool setStartSymbol(const string&);
		const Rule* getStartRule() const;
	protected:
		void setValidGrammar(const bool);
		virtual bool genotype2Phenotype() = 0;
		virtual bool phenotype2Genotype() = 0;
	private:
		bool validGrammar;
		int startSymbol;
};

#endif

