#include <stdio.h>
#include <math.h>
#include "GEspiral.h"

extern double xvals[194];
extern double yvals[194];
extern int Evolved[194];
int main()
{
 initVals();
 int i;
 double temp,x,y;
 for(i=0;i<194;i++)
   {
     x=xvals[i];
     y=yvals[i];
     temp=
cos(mysub((pdiv(if_cond(mymul(-0.734, +0.862), y, x, pdiv(-0.115, +0.944)), pdiv(if_cond(tan(myadd(y, x)), if_cond((y), exp(1.000), if_cond(y, 1.000, y, x), exp(x)), (sin(1.000)), 1.000), tan(tan(tan(y)))))), sin(mymul((pdiv(mysub(myadd(1.000, x), mymul(x, x)), sin(sin(y)))), mysub(x, tan(pdiv(mysub(y, 1.000), (1.000))))))))
;
   if(temp < 0)
     Evolved[i]=0;
   else
     Evolved[i]=1;
 }
 printf("%d\n",AssignFitness());
}
