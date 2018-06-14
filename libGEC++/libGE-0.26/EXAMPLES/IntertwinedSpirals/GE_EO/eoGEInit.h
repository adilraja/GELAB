#ifndef _eoGEInit_h
#define _eoGEInit_h

// include the base definition of eoInit
#include <eoInit.h>

// libGE
#include <GE/ge.h>

template <class GenotypeT>
class eoGEInit: public eoInit<GenotypeT>{
	public:
		eoGEInit(GEGrammarSI &init, long int seed, unsigned int newMinSize, unsigned int newMaxSize, bool sensibleInit, unsigned int popSize, float grow, unsigned int maxDepth, unsigned int tailSize, float tailRatio){
			mapper=&init;
			minSize=newMinSize;
			maxSize=newMaxSize;
			mapper->setPopSize(popSize);
			useSensibleInit=sensibleInit;
			if(useSensibleInit){
				mapper->setGrow(grow);
				mapper->setMaxDepth(maxDepth);
				if(tailSize>0){
					mapper->setTailSize(tailSize);
					if(tailRatio>0.0){
						throw std::logic_error("You cannot specify both tailSize and tailRatio for Sensible Initialisation.");
					}
				}
				else{
					mapper->setTailRatio(tailRatio);
				}
			}
		}

		void operator()(GenotypeT & _genotype){
			_genotype.invalidate();	   // IMPORTANT in case the _genotype is old
			if(!useSensibleInit){
				randomInit(_genotype);
			}
			else{
				sInit(_genotype);
			}
		}

		void randomInit(GenotypeT &_genotype){
			unsigned int size = minSize+rng.random(maxSize-minSize+1);
			_genotype.clear();
			for(unsigned int ii=0;ii<size;ii++){
				_genotype.push_back(rng.random(UCHAR_MAX));
			}
		}

		void sInit(GenotypeT &_genotype){
			_genotype.clear();
			// Apply sensible initialisation to genotype
			if(!mapper->init()){
				throw std::logic_error("Error using sensible initialisation.");
			}
			// Now copy genotype onto _genotype
			Genotype::const_iterator genIt=(mapper->getGenotype())->begin();
			while(genIt!=(mapper->getGenotype())->end()){
				_genotype.push_back(static_cast<unsigned char>(*genIt++));
			}
		}

	private:
		GEGrammarSI *mapper;
		bool useSensibleInit;
		unsigned int minSize;
		unsigned int maxSize;
};

#endif

