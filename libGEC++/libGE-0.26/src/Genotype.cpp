// Genotype.cpp -*- C++ -*-
#ifndef _GENOTYPE_CPP_
#define _GENOTYPE_CPP_

//#include <config.h>

#include<iostream>
#include<string>

#include"Genotype.h"

///////////////////////////////////////////////////////////////////////////////
// Default constructor. Creates a genotype structure of length newLength,
// using the elements of newArray, and sets its valid field to newValid
// and its fitness to newFitness. Non-specified arguments are given default
// values, as specified in the function prototype.
Genotype::Genotype(const int *newArray, const unsigned int newLength, const bool newValid, const FitnessType newFitness):_libGE_Genotype_valid(newValid),_libGE_Genotype_fitness(newFitness){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Genotype::Genotype(const int *, const unsigned int, const bool, const FitnessType)' called\n";
#endif
	setMaxCodonValue(INT_MAX);
	if(newArray){
		for(unsigned int ii=0;ii<newLength;ii++){
			push_back(newArray[ii]);
		}
	}
	setEffectiveSize(0);
	setWraps(0);
}

///////////////////////////////////////////////////////////////////////////////
// Constructor. Creates a genotype structure with the contents of newVector,
// and sets its valid field to newValid and its fitness to newFitness.
// Non-specified arguments are given default values, as specified in the
//function prototype.
Genotype::Genotype(const vector<CodonType> &newVector, const bool newValid, const FitnessType newFitness):_libGE_Genotype_valid(newValid),_libGE_Genotype_fitness(newFitness){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Genotype::Genotype(const vector<CodonType> *, const bool, const FitnessType)' called\n";
#endif
	vector<CodonType>::const_iterator it=newVector.begin();
	while(it!=newVector.end()){
		push_back(*it++);
	}
	setMaxCodonValue(INT_MAX);
	setEffectiveSize(0);
	setWraps(0);
}

///////////////////////////////////////////////////////////////////////////////
// Constructor. Creates an empty genotype structure, and sets maxCodonValue
// to the value specified as argument.
Genotype::Genotype(const CodonType maxCodonValue){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Genotype::Genotype(const CodonType)' called\n";
#endif
	setMaxCodonValue(maxCodonValue);
	setEffectiveSize(0);
	setWraps(0);
}

///////////////////////////////////////////////////////////////////////////////
// Copy constructor.
Genotype::Genotype(const Genotype &copy):vector<CodonType>(copy){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Genotype::Genotype(const Genotype &)' called\n";
#endif
	setValid(copy.getValid());
	setFitness(copy.getFitness());
	setMaxCodonValue(copy.getMaxCodonValue());
	setEffectiveSize(copy.getEffectiveSize());
	setWraps(copy.getWraps());
}

///////////////////////////////////////////////////////////////////////////////
// Destructor.
Genotype::~Genotype(){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Genotype::~Genotype()' called\n";
#endif
// do nothing!
}

///////////////////////////////////////////////////////////////////////////////
// Returns the current valid field.
bool Genotype::getValid() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'bool Genotype::getValid()' called\n";
#endif
	return _libGE_Genotype_valid;
}

///////////////////////////////////////////////////////////////////////////////
// Set a new value for the valid field.
void Genotype::setValid(const bool newValid){
#if (DEBUG_LEVEL >= 2)
	cerr << "'void Genotype::setValid(const bool)' called\n";
#endif
	_libGE_Genotype_valid=newValid;
}

///////////////////////////////////////////////////////////////////////////////
// Returns the current fitness score.
FitnessType Genotype::getFitness() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'FitnessType Genotype::getFitness()' called\n";
#endif
	return _libGE_Genotype_fitness;
}

///////////////////////////////////////////////////////////////////////////////
// Sets a new fitness score.
void Genotype::setFitness(const FitnessType newFitness){
#if (DEBUG_LEVEL >= 2)
	cerr << "'void Genotype::setFitness(const FitnessType)' called\n";
#endif
	_libGE_Genotype_fitness=newFitness;
}

///////////////////////////////////////////////////////////////////////////////
// Returns the maximum containable value in a codon.
CodonType Genotype::getMaxCodonValue() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'CodonType Genotype::getMaxCodonValue()' called\n";
#endif
	return _libGE_Genotype_maxCodonValue;
}

///////////////////////////////////////////////////////////////////////////////
// Sets the maximum containable value in a codon.
void Genotype::setMaxCodonValue(const CodonType newMaxCodonValue){
#if (DEBUG_LEVEL >= 2)
	cerr << "'void Genotype::getMaxCodonValue(const CodonType)' called\n";
#endif
	_libGE_Genotype_maxCodonValue=newMaxCodonValue;
}

///////////////////////////////////////////////////////////////////////////////
// Returns effective length of genotype.
unsigned int Genotype::getEffectiveSize() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'unsigned int Genotype::getEffectiveSize() const' called\n";
#endif
	return _libGE_Genotype_effectiveSize;
}

///////////////////////////////////////////////////////////////////////////////
// Sets effective length of genotype.
void Genotype::setEffectiveSize(const unsigned int newEffectiveSize){
#if (DEBUG_LEVEL >= 2)
	cerr << "'void Genotype::setEffectiveSize(const unsigned int)' called\n";
#endif
	_libGE_Genotype_effectiveSize=newEffectiveSize;
}

///////////////////////////////////////////////////////////////////////////////
// Returns number of wrapping events.
unsigned int Genotype::getWraps() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'unsigned int Genotype::getWraps() const' called\n";
#endif
	return _libGE_Genotype_wraps;
}

///////////////////////////////////////////////////////////////////////////////
// Sets number of wrapping events.
void Genotype::setWraps(const unsigned int newWraps){
#if (DEBUG_LEVEL >= 2)
	cerr << "'void Genotype::setWraps(const unsigned int)' called\n";
#endif
	_libGE_Genotype_wraps=newWraps;
}

///////////////////////////////////////////////////////////////////////////////
// Pretty print the contents of the genotype string.
ostream &operator<<(ostream &stream, const Genotype &g){
#if (DEBUG_LEVEL >= 2)
	cerr << "'ostream &operator<<(ostream &, const Genotype &)' called\n";
#endif
	char element[100];
	string s;
	int i=0;
	for(Genotype::const_iterator it=g.begin();it!=g.end();++it,++i){
		sprintf(element," %d",*it);
		s+=element;
	}
	return stream << s;
}

#endif

