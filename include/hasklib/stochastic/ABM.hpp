// ABM.hpp
#ifndef ABM_H
#define ABM_H
#include "Process.hpp"
#include "hasklib/random/NormalRng.hpp"

class ABM : public StochasticProcess 
{
protected:
    double mu;     // drift parameter (constant)
    double sigma;  // volatility parameter (constant)

public:
    // Constructor/Destructor
    ABM();
    ABM(double mu, double sigma);
    ~ABM();

    // StochasticProcess interface
    // dX_t = mu*dt + sigma*dW_t  ->  a(t,x) = mu, b(t,x) = sigma
    double drift(double t, double x) const override;
    double diffusion(double t, double x) const override;
    double diffusion_derivative(double t, double x) const override;

    // Exact terminal sampler — zero discretisation error
    // X_T = X_0 + mu*T + sigma*sqrt(T)*Z
    double sample_terminal(double X0, double T, NormalRng& rng) const;

    // Accessor/modifier methods
    void drift_param(double mu_in);
    double drift_param() const;
    void vol_param(double sigma_in);
    double vol_param() const;
};
#endif