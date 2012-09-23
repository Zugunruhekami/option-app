#ifndef OPTION_H
#define OPTION_H

struct HedgeRatios { double delta, gamma, theta, vega, rho; };

class Option_Interface
{ 
  public:
    enum OptionType { CALL, PUT };
    typedef double vanilla_args[5];
    
    Option_Interface(OptionType t, double K):type_(t), strike_(K) {  };
    virtual ~Option_Interface(){  };
    
    virtual double Price(const double args[]) const = 0;
    virtual HedgeRatios Greeks(const double args[]) const = 0;
      
  protected:
    OptionType type_;
    double strike_;

    
};

class VanillaCall : public Option_Interface
{  
  public:
    VanillaCall(double K):Option_Interface(CALL,K){  };
    ~VanillaCall(){  };
    
    double Price(const double args[]) const;
    HedgeRatios Greeks(const double args[]) const;
};

#endif
