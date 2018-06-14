// Mapper.h -*- C++ -*-
#ifndef _MAPPER_H_
#define _MAPPER_H_

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* This is an abstract class that cannot be instantiated; it defines the     */
/* most basic characteristics and functionality of a mapper. It is always    */
/* composed of both a Genotype and Phenotype structures, and contains a      */
/* (private) genotype2phenotype method, that is called everytime a new       */
/* genotype is set, and a (private) phenotype2genotype method, that is       */
/* called everytime a new phenotype is set.                                  */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "libGEdefs.h"

#include "Genotype.h"
#include "Phenotype.h"

#ifdef GALIB_INCLUDEPATH
#include GALIB_INCLUDEPATH
#ifndef _ga_ga_h_
#error ######################################################################
#error # libGE has been configured to use GALib, but GALib was not found.   #
#error # Please re-install GALib, or reconfigure libGE and re-install it.   #
#error # Alternatively, edit the libGEdefs.h file in the include directory. #
#error ######################################################################
#endif
#endif

using namespace std;

class Mapper{
	public:
		Mapper();
		Mapper(const Genotype &);
		Mapper(const Phenotype &);
		Mapper(const Mapper&);
		virtual ~Mapper();
		const Genotype * getGenotype() const;
		void setGenotype(const Genotype &);
#ifdef _ga_ga_h_
		//void setGenotype(const GAListGenome<unsigned char> &);
		template <class T>void setGenotype(const GA1DArrayGenome<T> &);
		template <class T>void setGenotype(const GAListGenome<T> &);
#endif
		const Phenotype * getPhenotype() const;
		void setPhenotype(const Phenotype &);
		void setGenotypeMaxCodonValue(const CodonType);
	protected:
		Genotype genotype;
		Phenotype phenotype;
		virtual bool genotype2Phenotype() = 0;
		virtual bool phenotype2Genotype() = 0;
};

#ifdef _ga_ga_h_
///////////////////////////////////////////////////////////////////////////////
// Sets this mapper's genotype structure to be a copy of the argument
// GA1DArrayGenome structure, and calls the genotype2Phenotype private method.
template <class T>
void Mapper::setGenotype(const GA1DArrayGenome<T> &genome){
	// Clear contents of current genotype
	genotype.clear();
	if(genome.size()){
		// Copy elements of GAGenome onto genotype
		int ii=0;
		while(ii<genome.size()){
			genotype.push_back(genome.gene(ii++));
		}
		genotype.setValid(true);
	}
	// Call genotype2Phenotype
	genotype2Phenotype();
}

///////////////////////////////////////////////////////////////////////////////
// Sets this mapper's genotype structure to be a copy of the argument
// GAListGenome structure, and calls the genotype2Phenotype private method.
template <class T>
void Mapper::setGenotype(const GAListGenome<T> &genome){
	// Clear contents of current genotype
	genotype.clear();
	if(genome.size()){
		// Cast to non-const, because GALib doesn't allow
		// extraction of elements from const GAList<T>
		GAListGenome<T> *g=const_cast<GAListGenome<T>*>(&genome);
		// Copy elements of GAGenome onto genotype
		int ii=0;
		while(ii<genome.size()){
			//genotype.push_back(*(genome[ii++]));
			genotype.push_back(*(g->warp(ii++)));
		}
		genotype.setValid(true);
	}
	// Call genotype2Phenotype
	genotype2Phenotype();
}
#endif

#endif

