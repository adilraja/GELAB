// Production.h -*- C++ -*-
#ifndef _PRODUCTION_H_
#define _PRODUCTION_H_

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* This class implements the production of a grammar. It is used by the Rule */
/* class to specify the various productions which make up a rule.            */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "libGEdefs.h"

#include<vector>

#include"Symbol.h"

using namespace std;

class Production : public vector<Symbol*>{
	public:
		Production(const unsigned int=0);
		Production(const Production &);
		~Production();
		void clear();
		bool getRecursive() const;
		void setRecursive(const bool);
		unsigned int getMinimumDepth() const;
		void setMinimumDepth(const unsigned int);
		friend ostream &operator<<(ostream &, const Production &);
	private:
		bool recursive;// Recursive nature of production
		unsigned int minimumDepth;	// Minimum depth of parse tree for production to map to terminal symbol(s)
};

#endif

