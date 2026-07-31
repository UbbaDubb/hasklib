// GBM.hpp
#ifndef GBM_H
#define GBM_H
#include "hasklib/stochastic/Process.hpp"
#include "hasklib/random/NormalRng.hpp"

class GBM : public StochasticProcess
{
protected:
    double mu; // Drift parameter
    double sigma; // Diffusion parameter

public:
    // Constructors/Destructor
    GBM();
    GBM(double mu, double sigma);
    ~GBM();

    // StochasticProcess interface
    double drift(double t, double x) const override;
    double diffusion(double t, double x) const override;
    double diffusion_derivative(double t, double x) const override;

    // Sample terminal value of GBM at time T given initial value S0 and a random number generator
    double sample_terminal(double S0, double T, NormalRng& rng) const;

    // Accessor/modifier methods
    void   drift_param(double mu_in);
    double drift_param() const;
    void   vol_param(double sigma_in);
    double vol_param() const;
};
#endif
