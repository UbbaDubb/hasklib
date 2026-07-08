// GBM.hpp
#ifndef GBM_H
#define GBM_H
#include <cmath>
#include "hasklib/stochastic/Process.hpp"
#include "hasklib/random/NormalRng.hpp"

class GBM : public StochasticProcess
{
protected:
    double mu;
    double sigma;

public:
    GBM() : mu(0.0), sigma(1.0) {}
    GBM(double mu, double sigma) : mu(mu), sigma(sigma) {}
    ~GBM() {}

    double drift(double t, double x) const override { return mu * x; }
    double diffusion(double t, double x) const override { return sigma * x; }
    double diffusion_derivative(double t, double x) const override { return sigma; }

    double sample_terminal(double S0, double T, NormalRng& rng) const {
        return S0 * std::exp((mu - 0.5 * sigma * sigma) * T
                             + sigma * std::sqrt(T) * rng.draw());
    }

    void   drift_param(double mu_in)    { mu = mu_in; }
    double drift_param() const          { return mu; }
    void   vol_param(double sigma_in)   { sigma = sigma_in; }
    double vol_param() const            { return sigma; }
};
#endif
