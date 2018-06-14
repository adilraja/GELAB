// GEGrammar.h -*- C++ -*-
#ifndef _GEGRAMMAR_H_
#define _GEGRAMMAR_H_

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* This class implements the standard GE mapping process. It implements the  */
/* virtual methods genotype2phenotype and phenotype2genotype, and the        */
/* standard GE wrapping operator.                                            */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "libGEdefs.h"

#include<stack>
#include<vector>

#include "CFGrammar.h"

using namespace std;

class GEGrammar : public CFGrammar{
	public:
		GEGrammar();
		GEGrammar(const Genotype &);
		GEGrammar(const Phenotype &);
		GEGrammar(const GEGrammar&);
		virtual ~GEGrammar();
		unsigned int getMaxWraps() const;
		void setMaxWraps(const unsigned int);
		const DerivationTree* getDerivationTree();
		const vector<Production*>* getProductions();
	protected:
		vector<Production*> productions;
		bool genotype2Phenotype();
		bool phenotype2Genotype();
		void buildDTree(DerivationTree&, vector<Production*>::iterator&);
	private:
		bool genotype2Phenotype(const bool);
		int genotype2PhenotypeStep(stack<const Symbol*>&,Genotype::iterator,bool=false);
		unsigned int maxWraps;
};

#endif

