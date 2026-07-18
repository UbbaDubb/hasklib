// OU.hpp
#ifndef OU_H
#define OU_H
#include <cmath>
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
    OU() : kappa(0.0), theta(0.0), sigma(0.0) {}
    OU(double kappa, double theta, double sigma)
        : kappa(kappa), theta(theta), sigma(sigma) {}
    ~OU() {}

    // StochasticProcess interface
    // dX_t = kappa*(theta - x)*dt + sigma*dW_t
    // => a(t,x) = kappa*(theta - x), b(t,x) = sigma
    double drift(double t, double x) const override
    {
        return kappa * (theta - x);
    }

    double diffusion(double t, double x) const override
    {
        return sigma;
    }

    double diffusion_derivative(double t, double x) const override
    {
        return 0.0;  // b(t,x) = sigma (constant) => b'(t,x) = 0
    }

    // Exact terminal sampler — zero discretisation error
    // X_T = X0*exp(-kappa*T) + theta*(1 - exp(-kappa*T))
    //       + sigma*sqrt((1 - exp(-2*kappa*T)) / (2*kappa)) * Z
    double sample_terminal(double X0, double T, NormalRng& rng) const
    {
        double Z = rng.draw();
        double meanTerm = X0 * std::exp(-kappa * T) + theta * (1.0 - std::exp(-kappa * T));
        double varTerm  = sigma * std::sqrt((1.0 - std::exp(-2.0 * kappa * T)) / (2.0 * kappa));
        return meanTerm + varTerm * Z;
    }

    // Accessor/modifier methods
    void   reversion_speed(double kappa_in) { kappa = kappa_in; }
    double reversion_speed() const          { return kappa; }
    void   mean_level(double theta_in)      { theta = theta_in; }
    double mean_level() const               { return theta; }
    void   vol_param(double sigma_in)       { sigma = sigma_in; }
    double vol_param() const                { return sigma; }
};
#endif