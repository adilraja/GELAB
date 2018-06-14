// Mapper.cpp -*- C++ -*-
#ifndef _MAPPER_CPP_
#define _MAPPER_CPP_

//#include <config.h>

#include<iostream>

#include "Mapper.h"

///////////////////////////////////////////////////////////////////////////////
// Default constructor.
Mapper::Mapper(){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Mapper::Mapper()' called\n";
#endif
}

///////////////////////////////////////////////////////////////////////////////
// Constructor with Genotype structure; set Genotype to newGenotype.
Mapper::Mapper(const Genotype &newGenotype):genotype(newGenotype){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Mapper::Mapper(const Genotype &)' called\n";
#endif
}

///////////////////////////////////////////////////////////////////////////////
// Constructor with Phenotype structure; set Phenotype to newPhenotype.
Mapper::Mapper(const Phenotype &newPhenotype):phenotype(newPhenotype){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Mapper::Mapper(const Phenotype &)' called\n";
#endif
}

///////////////////////////////////////////////////////////////////////////////
// Copy constructor.
Mapper::Mapper(const Mapper& copy):genotype(copy.genotype),phenotype(copy.phenotype){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Mapper::Mapper(const Mapper&)' called\n";
#endif
}

///////////////////////////////////////////////////////////////////////////////
// Destructor.
Mapper::~Mapper(){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Mapper::~Mapper()' called\n";
#endif
}

///////////////////////////////////////////////////////////////////////////////
// Returns a pointer to the genotype structure of this mapper.
Genotype const * Mapper::getGenotype() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'Mapper::getGenotype() const' called\n";
#endif
	return &genotype;
}

///////////////////////////////////////////////////////////////////////////////
// Sets this mapper's genotype structure to be a copy of the argument genotype
// structure, and calls the genotype2Phenotype private method.
void Mapper::setGenotype(const Genotype &newGenotype){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Mapper::setGenotype(const Genotype &)' called\n";
#endif
	genotype=newGenotype;
	genotype2Phenotype();
}

///////////////////////////////////////////////////////////////////////////////
// Returns apointer to the phenotype structure of this mapper.
Phenotype const * Mapper::getPhenotype() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'Mapper::getPhenotype() const' called\n";
#endif
	return &phenotype;
}

///////////////////////////////////////////////////////////////////////////////
// Sets this mapper's phenotype structure to be a copy of the argument
// phenotype structure, and calls the phenotype2Genotype private method.
void Mapper::setPhenotype(const Phenotype &newPhenotype){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Mapper::setPhenotype(const Phenotype &)' called\n";
#endif
	phenotype=newPhenotype;
	phenotype2Genotype();
}

///////////////////////////////////////////////////////////////////////////////
// Sets the maximum codon value of the genotype structure.
void Mapper::setGenotypeMaxCodonValue(const CodonType newMaxCodonValue){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Mapper::setGenotypeMaxCodonValue(const CodonType)' called\n";
#endif
	genotype.setMaxCodonValue(newMaxCodonValue);
}

#endif

