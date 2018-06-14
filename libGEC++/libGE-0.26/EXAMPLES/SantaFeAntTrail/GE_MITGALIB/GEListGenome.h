// GEListGenome.h -*- C++ -*-
#ifndef _GELISTGENOME_H
#define _GELISTGENOME_H

#include<ga/ga.h>

class GEListGenome:public GAListGenome<unsigned char>{
	public:
		int getEffectiveSize() const;
		void setEffectiveSize(const int newEffSize);
		static int effCrossover(const GAGenome&, const GAGenome&, GAGenome*, GAGenome*);
		static int pointMutator(GAGenome&,float);
	private:
		unsigned int effSize;
};

#endif

