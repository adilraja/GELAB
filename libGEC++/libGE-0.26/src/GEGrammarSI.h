// GEGrammarSI.h -*- C++ -*-
#ifndef _GEGRAMMARSI_H_
#define _GEGRAMMARSI_H_

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* This class implements the standard GE ramped half-and-half initialisation */
/* routine, also known as sensible initialisation. It implements the virtual */
/* methods from the class Initialiser.                                       */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "libGEdefs.h"

#include "Initialiser.h"
#include "GEGrammar.h"

using namespace std;

class GEGrammarSI: public GEGrammar, public Initialiser{
	public:
		GEGrammarSI();
		GEGrammarSI(const Genotype &);
		GEGrammarSI(const Phenotype &);
		GEGrammarSI(const GEGrammarSI&);
		virtual ~GEGrammarSI();
		float getGrow() const;
		void setGrow(const float);
		float getFull() const;
		void setFull(const float);
		unsigned int getMaxDepth() const;
		void setMaxDepth(const unsigned int);
		float getTailRatio() const;
		void setTailRatio(const float);
		unsigned int getTailSize() const;
		void setTailSize(const unsigned int);
		bool init(const unsigned int=UINT_MAX);
	private:
		float grow;
		unsigned int maxDepth;
		float tailRatio;
		unsigned int tailSize;
		bool growTree(DerivationTree&,const bool&,const unsigned int&);
};

#endif

