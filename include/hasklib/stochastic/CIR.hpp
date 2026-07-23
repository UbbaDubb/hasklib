// CIR.hpp
#ifndef CIR_H
#define CIR_H
#include "Process.hpp"

class CIR : public StochasticProcess
{
protected:
    double kappa;  // speed of mean reversion
    double theta;  // long-run mean level
    double sigma;  // volatility parameter

public:
    // Constructor/Destructor
    CIR();
    CIR(double kappa, double theta, double sigma);
    ~CIR() {}

    // StochasticProcess interface
    // dX_t = kappa*(theta - x)*dt + sigma*sqrt(x)*dW_t
    // => a(t,x) = kappa*(theta - x), b(t,x) = sigma*sqrt(x)
    double drift(double t, double x) const override;
    double diffusion(double t, double x) const override;
    double diffusion_derivative(double t, double x) const override;

    // Accessor/modifier methods
    void   reversion_speed(double kappa_in);
    double reversion_speed() const;
    void   mean_level(double theta_in);
    double mean_level() const;
    void   vol_param(double sigma_in);
    double vol_param() const;
};
#endif