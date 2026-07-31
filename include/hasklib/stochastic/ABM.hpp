// ABM.hpp
#ifndef ABM_H
#define ABM_H
#include "Process.hpp"
#include "hasklib/random/NormalRng.hpp"

class ABM : public StochasticProcess 
{
protected:
    double mu;     // Drift parameter (constant)
    double sigma;  // Diffusion parameter (constant)

public:
    // Constructors/Destructor
    ABM();
    ABM(double mu, double sigma);
    ~ABM();

    // StochasticProcess interface
    double drift(double t, double x) const override;
    double diffusion(double t, double x) const override;
    double diffusion_derivative(double t, double x) const override;

    // Sample
    double sample_terminal(double X0, double T, NormalRng& rng) const;

    // Accessor/modifier methods
    void   drift_param(double mu_in);
    double drift_param() const;
    void   vol_param(double sigma_in);
    double vol_param() const;
};
#endif