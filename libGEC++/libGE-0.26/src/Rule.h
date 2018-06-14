// Rule.h -*- C++ -*-
#ifndef _RULE_H_
#define _RULE_H_

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* This class implements a rule of a grammar. It is used by classes such as  */
/* Grammar to specify grammars. It is composed of a left hand side,          */
/* containing Symbol elements, and a right hand side, containing             */
/* Production elements.                                                      */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "libGEdefs.h"

#include<vector>

#include"Production.h"
#include"Symbol.h"

using namespace std;

class Rule : public vector<Production>{
	public:
		Rule(const unsigned int=0);
		Rule(const Rule &);
		~Rule();
		void clear();
		bool getRecursive() const;
		void setRecursive(const bool);
		unsigned int getMinimumDepth() const;
		void setMinimumDepth(const unsigned int);

		vector<Symbol*> lhs;	// The left-hand side of the rule
	private:
		bool recursive;// Recursive nature of rule
		unsigned int minimumDepth;	// Minimum depth of parse tree for production to map to terminal symbol(s)
};

#endif

