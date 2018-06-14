// GEcart.c -*- C -*-
#ifndef _GECART_C_
#define _GECART_C_

// #include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef double Real;

// Cart and simulation state.
Real X = 0.0;
Real V = 0.0;
Real currTime = 0.0;

// Evaluation.
const unsigned int numFitCase = 20;
const Real startValuesArray[20][2] =
  {
    {0.50, 0.67},
    {-0.65, 0.40},
    {-0.16, -0.57},
    {0.10, 0.50},
    {-0.71,  0.66},
    {0.43, 0.01},
    {-0.28, -0.71},
    {0.27, -0.73},
    {-0.50, 0.34},
    {-0.57, 0.32},
    {0.43, -0.69},
    {-0.52, -0.16},
    {-0.33, -0.21},
    {-0.16, -0.06},
    {0.71, -0.69},
    {-0.04, -0.63},
    {0.39, 0.70},
    {-0.52, -0.42},
    {-0.59, 0.38},
    {0.58, -0.35}
  };
unsigned int currFitCase = 0;
Real sumFitCaseTimes = 0.0;
unsigned int hitCount = 0;
const Real maxTime = 7.5;
const Real overMaxTimePenalty = 10.0;
const Real maxHitEuclError = 0.01;
Real currEuclError = 0.0;

// Simulation parameters.
const Real timeStep = 0.02;
Real posForceVelChange;
Real negForceVelChange;
Real velocityChange = 0.0;

// Function prototypes.
void initCart();
void resetCart();
void stepSim();
Real DIV(Real n, Real d);
Real GT(Real lhs, Real rhs);
Real ABS(Real x);


void initCart()
{
  const Real forceToMassRatio = 0.5;
  posForceVelChange = (forceToMassRatio * timeStep);
  negForceVelChange = ((-1.0) * posForceVelChange);
  currFitCase = 0;
  resetCart();
}

void resetCart()
{
  // Set initial values and calculate initial euclidean distance to
  // the target (0, 0).
  X = startValuesArray[currFitCase][0];
  V = startValuesArray[currFitCase][1];
  currTime = 0.0;
  currEuclError = sqrt((X * X) + (V * V));
}

void stepSim()
{
  X += (V * timeStep);
  V += velocityChange;
  currTime += timeStep;
  currEuclError = sqrt((X * X) + (V * V));

/*   fprintf(stderr,  */
/* 	  "%d %f %f %f %f %f\n", */
/* 	  currFitCase, */
/* 	  currTime, */
/* 	  X, */
/* 	  velocityChange, */
/* 	  V, */
/* 	  currEuclError); */

  if (currEuclError <= maxHitEuclError)
  {
     if (currTime <= maxTime)
     {
       sumFitCaseTimes += currTime;
       ++hitCount;
       ++currFitCase;
       resetCart();
     }
  }
  else
  {
    if (currTime >= maxTime)
    {
      sumFitCaseTimes += overMaxTimePenalty;
      ++currFitCase;
      resetCart();
    }
  }
}

// Protected division.
Real DIV(Real n, Real d) 
{
  return (d == 0.0) ? 1.0 : (n / d);
}

// Greater than.
Real GT(Real lhs, Real rhs) 
{
  return (lhs > rhs) ? 1.0 : (-1.0);
}

// Absolute value.
Real ABS(Real x) 
{
  return (x > 0.0) ? x : ((-1.0) * x);
}

#endif
