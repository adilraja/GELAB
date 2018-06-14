// eoGEMutation.h -*- C++ -*-
#ifndef eoGEMutation_H
#define eoGEMutation_H

#include <eoOp.h>

template<class GenotypeT> 
class eoGEMutation: public eoMonOp<GenotypeT>{
	public:
		eoGEMutation(float newPMutPerBit) : pMutPerBit(newPMutPerBit){
		}

		string className() const{
			return "eoGEMutation"; }

		bool operator()(GenotypeT & _genotype){
			bool isModified=false;
			// START code for mutation of the _genotype object
			register unsigned char mutator;
			register int nMut = 0;
			unsigned int n = _genotype.size();
			unsigned bits = sizeof(unsigned char)*8;

			for(unsigned int ii=0;ii<n;ii++){
				mutator=0;
				// Go through each bit
				for(unsigned int jj=0;jj<bits;jj++){
					mutator=mutator<<1;
					// Flip the bit with prob. 0.01
					if(rng.flip(pMutPerBit)){
						isModified = true;
						mutator++;
						nMut++;
					}
				}
				// Update the genotype
				_genotype[ii]=_genotype[ii]^mutator;
			}
			return isModified;
		}

	private:
		float pMutPerBit;
};

#endif

