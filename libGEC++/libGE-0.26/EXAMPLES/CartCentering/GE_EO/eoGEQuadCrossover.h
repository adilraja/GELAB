#ifndef eoGEQuadCrossover_H
#define eoGEQuadCrossover_H

#include <eoOp.h>

template<class GenotypeT> 
class eoGEQuadCrossover: public eoQuadOp<GenotypeT>{
	public:
		eoGEQuadCrossover(const bool effCross=false){
			setUseEffectiveCrossover(effCross);
		}

	string className() const{
		return "eoGEQuadCrossover";
	}

	bool operator()(GenotypeT& _genotype1, GenotypeT & _genotype2){
		if((_genotype1.size()<=1)||(_genotype2.size()<=1)){
			return false;
		}

		vector<unsigned char>::iterator after_cut1;
		vector<unsigned char>::iterator after_cut2;
		vector<unsigned char> temp1;
		vector<unsigned char> temp2;

		if(!useEffCross){
			after_cut1=1+_genotype1.begin()+rng.random(_genotype1.size()-1);
			after_cut2=1+_genotype2.begin()+rng.random(_genotype2.size()-1);
		}
		else{
			if(_genotype1.getEffectiveSize()>_genotype1.size()){
				// Wrapping was used, so stick to normal size
				after_cut1=1+_genotype1.begin()+rng.random(_genotype1.size()-1);
			}
			else{
				after_cut1=1+_genotype1.begin()+rng.random(_genotype1.getEffectiveSize()-1);
			}
			if(_genotype2.getEffectiveSize()>_genotype2.size()){
				// Wrapping was used, so stick to normal size
				after_cut2=1+_genotype2.begin()+rng.random(_genotype2.size()-1);
			}
			else{
				after_cut2=1+_genotype2.begin()+rng.random(_genotype2.getEffectiveSize()-1);
			}
		}

		// Create first child  - first half from _g1, second half from _g2
		temp1.insert(temp1.begin(),after_cut2,_genotype2.end());
		temp1.insert(temp1.begin(),_genotype1.begin(),after_cut1);
		// Create second child - first half from _g2, second half from _g1
		temp2.insert(temp2.begin(),after_cut1,_genotype1.end());
		temp2.insert(temp2.begin(),_genotype2.begin(),after_cut2);
		// Copy them back to _genotype structures
		_genotype1.clear();
		_genotype1.insert(_genotype1.begin(),temp1.begin(),temp1.end());
		_genotype2.clear();
		_genotype2.insert(_genotype2.begin(),temp2.begin(),temp2.end());

		return true;// One at least is modified
	}

	bool getUseEffectiveCrossover(){
		return useEffCross;
	}
	void setUseEffectiveCrossover(const bool newUseEffCross){
		useEffCross=newUseEffCross;
	}

	private:
		bool useEffCross;
};

#endif

