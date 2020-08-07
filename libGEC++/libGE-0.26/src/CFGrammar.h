// CFGrammar.h -*- C++ -*-
#ifndef _CFGRAMMAR_H_
#define _CFGRAMMAR_H_

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* This class implements the methods associated with the manipulation of     */
/* context-free grammars. It implements input and output methods for this    */
/* type of grammar, along with manipulation and analysis methods.            */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "libGEdefs.h"

#include<vector>
#include<string>

#include "Grammar.h"
#include "Tree.h"

using namespace std;

typedef Tree<const Symbol*> DerivationTree;

class CFGrammar : public Grammar{
	public:
		CFGrammar();
		CFGrammar(const Genotype &);
		CFGrammar(const Phenotype &);
		CFGrammar(const CFGrammar&);
		virtual ~CFGrammar();
		bool readBNFFile(const char *);
		bool readBNFFile(const string &);
		bool readBNFString(const char *);
		bool readBNFString(const string &);
		bool addBNFString(const char *);
		bool addBNFString(const string &);
		void outputBNF(ostream&);
		Rule* findRule(const Symbol&); // Maybe const Rule* instead?
		virtual const DerivationTree* getDerivationTree()=0;
	private:
		bool isRecursive(vector<Symbol*>&, Rule*);
		void updateRuleFields();
		void clearRuleFields();
	protected:
		DerivationTree derivationTree;
		virtual bool genotype2Phenotype() = 0;
		virtual bool phenotype2Genotype() = 0;
};

#endif

