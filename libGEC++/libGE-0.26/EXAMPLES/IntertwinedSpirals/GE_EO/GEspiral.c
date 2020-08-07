

#include <math.h>

double xvals[194];
double yvals[194];
int Class[194];
int Evolved[194];

#define FitnessCases 194



void initVals(){

  int i,j;
  double angle;
  double radius;
  double varx,vary;

  for (i=0,j=0; i < FitnessCases/2; i++,j++) 
    {
      angle = (double)i * M_PI  / 16.0;
      radius = (double)6.5 * (104 - i) / 104.0;
      varx = radius * sin(angle);
      vary = radius * cos(angle);
      xvals[j] = varx;
      yvals[j] = vary;
      Class[j]=1;
      j++;

      xvals[j] = -varx;
      yvals[j] = -vary;
      Class[j]= 0;

    }

}

int AssignFitness()
{
  int i,hits;
  hits=0;
  for(i=0;i<FitnessCases;i++)
    if((((Evolved[i]  > 0) && (Class[i] == 1))) || ((Evolved[i]  <= 0) && (Class[i] == 0))) 
      hits++;
  return hits;
}

double if_cond(double exp1,double exp2,double exp3,double exp4)
{
  if(exp1 <= exp2)
    return exp3;
  else
    return exp4;
}



double pdiv(double a1,double a2){
  if(a2 == 0)
    return 0;
  else
    return a1/a2;
}

double myadd(double a1,double a2){
  return a1+a2;
}

double mysub(double a1,double a2){
  return a1-a2;
}

double mymul(double a1,double a2){
  return (a1*a2);
}

