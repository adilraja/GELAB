// Genotype.h -*- C++ -*-
#ifndef _GENOTYPE_H_
#define _GENOTYPE_H_

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* This class represents the structure of a genotype, as employed by libGE   */
/* mappers. It is simply an array of elements, each element corresponding to */
/* an allele of an individual. The structures used by search engines to      */
/* represent genotype strings must be converted to this representation,      */
/* before they can benefit from libGE's mapping process.                     */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "libGEdefs.h"

#include<iostream>
#include<vector>
#include<climits>

#define MIN_GENOTYPE_FITNESS		0.0
#define MAX_GENOTYPE_LENGTH		32767
#define STANDARD_MAXCODONVALUE		INT_MAX

typedef long double FitnessType;
typedef int CodonType;

using namespace std;

class Genotype: public vector<CodonType>{
	public:
		Genotype(const int * = 0, const unsigned int = 0, const bool = true, const FitnessType=MIN_GENOTYPE_FITNESS);
		Genotype(const vector<CodonType> &, const bool = true, const FitnessType=MIN_GENOTYPE_FITNESS);
		Genotype(const CodonType);
		Genotype(const Genotype &);
		~Genotype();
		bool getValid() const;
		void setValid(const bool);
		FitnessType getFitness() const;
		void setFitness(const FitnessType);
		CodonType getMaxCodonValue() const;
		void setMaxCodonValue(const CodonType);
		unsigned int getEffectiveSize() const;
		void setEffectiveSize(const unsigned int);
		unsigned int getWraps() const;
		void setWraps(const unsigned int);
		friend ostream &operator<<(ostream &, const Genotype &);
	private:
		bool _libGE_Genotype_valid;
		FitnessType _libGE_Genotype_fitness;
		CodonType _libGE_Genotype_maxCodonValue;
		unsigned int _libGE_Genotype_effectiveSize;
		unsigned int _libGE_Genotype_wraps;
};

#endif

