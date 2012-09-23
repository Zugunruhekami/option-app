#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include<boost/math/distributions.hpp>

/* Implementation of Distribution Singletons for Probability Calculations*/

class StandardNormal
{ 
  public:
    static StandardNormal *Instance();
    double pdf(const double &x) const { return boost::math::pdf(norm_, x); };
    double cdf(const double &x) const { return boost::math::cdf(norm_, x); };

  private:
    StandardNormal():norm_(boost::math::normal_distribution<double>(0,1)){ };
    static StandardNormal *inst; 
    boost::math::normal_distribution<double> norm_;
};

StandardNormal *StandardNormal::Instance()
{ 
  if(inst == NULL){ inst = new StandardNormal(); } 
  return inst; 
}

#endif
