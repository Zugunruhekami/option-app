#include"option.h"
#include"distribution.h"
#include<cmath>

StandardNormal *StandardNormal::inst = NULL;

double VanillaCall::Price(const double args[]) const
{  
  double spot = args[0];
  double vol = args[1];
  double rate = args[2];
  double div_rate = args[3];
  double expiry = args[4];

  double d1 = std::log(spot/strike_) + (rate - div_rate + vol * vol / 2.0) * expiry;
  d1 /= vol * std::sqrt(expiry);
  double d2 = d1 - vol * sqrt(expiry);
  
  double price = spot*std::exp(-div_rate * expiry) * StandardNormal::Instance()->cdf(d1) - strike_ * exp(-rate * expiry) * StandardNormal::Instance()->cdf(d2);
  return price;
}

HedgeRatios VanillaCall::Greeks(const double args[]) const
{  
  HedgeRatios greeks;
  
  double spot = args[0];
  double vol = args[1];
  double rate = args[2];
  double div_rate = args[3];
  double expiry = args[4];
  
  double d1 = std::log(spot/strike_) + (rate - div_rate + vol * vol / 2.0) * expiry;
  d1 /= vol * std::sqrt(expiry);
  double d2 = d1 - vol * sqrt(expiry);
 
  double div_factor = std::exp(-div_rate * expiry);
  double rate_factor = std::exp(-rate * expiry);
  double d1_dist = StandardNormal::Instance()->cdf(d1); 
  double d2_dist = StandardNormal::Instance()->cdf(d2); 
  double d1_density = StandardNormal::Instance()->pdf(d1);
   
  greeks.delta = d2_dist * div_factor * 100.0;
  greeks.gamma = div_factor * d1_density / (spot * vol * sqrt(expiry)) * 100.0;
  greeks.theta = (-div_factor * spot * vol * d1_density / (2.0 * sqrt(expiry))) - (rate * strike_ * rate_factor * d2_dist) + (div_rate * spot * div_factor * d1_dist);
  greeks.vega = spot * div_factor * d1_density * sqrt(expiry);
  greeks.rho = strike_ * expiry * rate_factor * d2_dist; 

  return greeks;
}

