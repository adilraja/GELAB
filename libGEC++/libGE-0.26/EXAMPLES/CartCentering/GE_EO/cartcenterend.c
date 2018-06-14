
    > 0.0)
    {
      velocityChange = posForceVelChange;
    }
    else
    {
      velocityChange = negForceVelChange;
    }
  
    stepSim();
  }


  printf("%f %d\n",
         sumFitCaseTimes,
  	 hitCount);

  return (0);
}
