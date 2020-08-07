// Phenotype.h -*- C++ -*-
#ifndef _PHENOTYPE_H_
#define _PHENOTYPE_H_

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* This class represents the structure of a phenotype, as employed by libGE  */
/* mappers. As in nearly all cases the output of the GE mapping process will */
/* be a text generated through the use of a grammar, it made sense to        */
/* implement this structure as being an array of characters. This structure  */
/* will most likely have to be converted to the output required by the       */
/* evaluator used to score phenotype structures.                             */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "libGEdefs.h"

#include<iostream>
#include<string>
#include<vector>

#include"Symbol.h"

#define MIN_PHENOTYPE_FITNESS		0.0

typedef long double FitnessType;

using namespace std;

class Phenotype: public vector<const Symbol*>{
	public:
		Phenotype(const bool=false, const FitnessType=MIN_PHENOTYPE_FITNESS);
		Phenotype(const Phenotype &);
		~Phenotype();
		bool getValid() const;
		void setValid(const bool);
		FitnessType getFitness() const;
		void setFitness(const FitnessType);
		string getString() const;
		//const char* c_str() const;
		friend ostream &operator<<(ostream &, const Phenotype &);
	private:
		bool _libGE_Phenotype_valid;
		FitnessType _libGE_Phenotype_fitness;
};

#endif

