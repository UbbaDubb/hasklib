// OU.hpp
#ifndef OU_H
#define OU_H
#include "Process.hpp"
#include "hasklib/random/NormalRng.hpp"

class OU : public StochasticProcess
{
protected:
    double kappa;  // speed of mean reversion
    double theta;  // long-run mean level
    double sigma;  // volatility parameter (constant)

public:
    // Constructor/Destructor
    OU();
    OU(double kappa, double theta, double sigma);
    ~OU();

    // StochasticProcess interface
    // dX_t = kappa*(theta - x)*dt + sigma*dW_t
    // => a(t,x) = kappa*(theta - x), b(t,x) = sigma
    double drift(double t, double x) const override;
    double diffusion(double t, double x) const override;
    double diffusion_derivative(double t, double x) const override;

    // Exact terminal sampler — zero discretisation error
    // X_T = X0*exp(-kappa*T) + theta*(1 - exp(-kappa*T))
    //       + sigma*sqrt((1 - exp(-2*kappa*T)) / (2*kappa)) * Z
    double sample_terminal(double X0, double T, NormalRng& rng) const;

    // Accessor/modifier methods
    void   reversion_speed(double kappa_in);
    double reversion_speed() const;
    void   mean_level(double theta_in);
    double mean_level() const;
    void   vol_param(double sigma_in);
    double vol_param() const;
};
#endif
