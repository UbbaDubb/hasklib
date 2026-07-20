// GBM.hpp
#ifndef GBM_H
#define GBM_H
#include "hasklib/stochastic/Process.hpp"
#include "hasklib/random/NormalRng.hpp"

class GBM : public StochasticProcess
{
protected:
    double mu;
    double sigma;

public:
    GBM();
    GBM(double mu, double sigma);
    ~GBM();

    double drift(double t, double x) const override;
    double diffusion(double t, double x) const override;
    double diffusion_derivative(double t, double x) const override;

    double sample_terminal(double S0, double T, NormalRng& rng) const;

    void   drift_param(double mu_in);
    double drift_param() const;
    void   vol_param(double sigma_in);
    double vol_param() const;
};
#endif
