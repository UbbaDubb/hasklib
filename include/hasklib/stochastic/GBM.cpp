// GBM.cpp
#include "GBM.hpp"
#include <cmath>

///// Constructors/Destructor //////////////////////

// Default constructor
GBM::GBM() : mu(0.0), sigma(1.0) {}

// Constructor by input
GBM::GBM(double mu, double sigma) : mu(mu), sigma(sigma) {}

// Destructor
GBM::~GBM() {}

//// Overriden functions from StochasticProcess /////////////////

double GBM::drift(double t, double x) const
{
    return mu * x;
}

double GBM::diffusion(double t, double x) const
{
    return sigma * x;
}

double GBM::diffusion_derivative(double t, double x) const
{
    return sigma;  // b(t,x) = sigma*x => b'(t,x) = sigma
}

///// Sample terminal ///////////////////////////////

double GBM::sample_terminal(double S0, double T, NormalRng& rng) const
{
    double Z = rng.draw();
    return S0 * std::exp((mu - 0.5 * sigma * sigma) * T + sigma * std::sqrt(T) * Z);
}


///// Accessor/modifier methods //////////////////
void GBM::drift_param(double mu_in) { mu = mu_in; }
double GBM::drift_param() const { return mu; }
void GBM::vol_param(double sigma_in) { sigma = sigma_in; }
double GBM::vol_param() const { return sigma; } 