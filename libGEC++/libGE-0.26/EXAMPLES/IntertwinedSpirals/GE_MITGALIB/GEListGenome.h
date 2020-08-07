// GEListGenome.h -*- C++ -*-
#ifndef _GELISTGENOME_H
#define _GELISTGENOME_H

#include<ga/ga.h>

class GEListGenome:public GAListGenome<unsigned char>{
public:

  GEListGenome();
  GEListGenome(const GEListGenome& source);
  virtual ~GEListGenome();

  virtual GEListGenome* clone(GAGenome::CloneMethod method) const;
  virtual void copy(const GAGenome& source);
  virtual int equal(const GAGenome& source) const;

  GEListGenome operator=(const GAGenome& source);

  int getEffectiveSize() const;
  void setEffectiveSize(const int newEffSize);
  static int effCrossover(const GAGenome& p1,
			  const GAGenome& p2,
			  GAGenome* c1, 
			  GAGenome* c2);
  static int pointMutator(GAGenome& g, float pmut);


private:

  void helpCopy(const GEListGenome& source);
  int helpCompare(const GEListGenome& source) const;

  unsigned int effSize;
};

#endif

