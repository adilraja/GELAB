#include <stdio.h>

typedef double Real;

void initCart();
void resetCart();
void stepCart();
Real DIV(Real n, Real d);
Real GT(Real lhs, Real rhs);
Real ABS(Real x);

extern Real X;
extern Real V;
extern Real velocityChange;
extern Real posForceVelChange;
extern Real negForceVelChange;
extern Real sumFitCaseTimes;
extern unsigned int hitCount;
extern unsigned int numFitCase;
extern unsigned int currFitCase;


int main(void)
{
  initCart();
  resetCart();
  while (currFitCase < numFitCase)
  {  
    if (
