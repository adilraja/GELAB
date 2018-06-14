#ifndef _eoGE_h
#define _eoGE_h

using namespace std;

template< class FitT>
class eoGE: public EO<FitT>, public vector<unsigned char>{
	public:
		eoGE(){ 
			setEffectiveSize(0);
		}

		virtual ~eoGE(){
		}

		virtual string className() const{
			return "eoGE";
		}

		void printOn(ostream& os) const{
			// First write the fitness
			EO<FitT>::printOn(os);
			os << ' ';
			os << size();
			if(size()){
			const_iterator it=vector<unsigned char>::begin();
			while(it!=vector<unsigned char>::end()){
				os << " " << static_cast<int>(*it++);
				}
			}
		}

		void readFrom(istream& is){
			EO<FitT>::readFrom(is);
			unsigned int genomeSize,dataRead;
			is >> genomeSize;
			clear();
			while(genomeSize){
			  // is >> static_cast<int>(dataRead);
				is >> dataRead;
				push_back(dataRead);
				genomeSize--;
			}
		}

		unsigned int getEffectiveSize(){
			return effSize;
		}
		void setEffectiveSize(const unsigned int newEffSize){
			effSize=newEffSize;
		}
	private:
		unsigned int effSize;
};

#endif

