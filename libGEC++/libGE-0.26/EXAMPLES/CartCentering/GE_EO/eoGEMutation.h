/** -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

The above line is useful in Emacs-like editors
 */

/*
Template for simple mutation operators
======================================
*/

#ifndef eoGEMutation_H
#define eoGEMutation_H


#include <eoOp.h>

/** 
 *  Always write a comment in this format before class definition
 *  if you want the class to be documented by Doxygen
 *
 * THere is NO ASSUMPTION on the class GenoypeT.
 * In particular, it does not need to derive from EO
 */
template<class GenotypeT> 
class eoGEMutation: public eoMonOp<GenotypeT>
{
public:
  /**
   * Ctor - no requirement
   */
// START eventually add or modify the anyVariable argument
  eoGEMutation(float newPMutPerBit) : pMutPerBit(newPMutPerBit){
  //  eoGEMutation( varType  _anyVariable) : anyVariable(_anyVariable) 
// END eventually add or modify the anyVariable argument
    // START Code of Ctor of an eoGEEvalFunc object
    // END   Code of Ctor of an eoGEEvalFunc object
  }

  /// The class name. Used to display statistics
  string className() const { return "eoGEMutation"; }

  /**
   * modifies the parent
   * @param _genotype The parent genotype (will be modified)
   */
  bool operator()(GenotypeT & _genotype) 
  {
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
    // END code for mutation of the _genotype object
  }

private:
// START Private data of an eoGEMutation object
  //  varType anyVariable;		   // for example ...
	float pMutPerBit;
// END   Private data of an eoGEMutation object
};

#endif
