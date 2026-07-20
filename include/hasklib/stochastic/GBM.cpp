// GBM.cpp
#include "GBM.hpp"
#include <cmath>

GBM::GBM() : mu(0.0), sigma(1.0) {}

GBM::GBM(double mu, double sigma) : mu(mu), sigma(sigma) {}

GBM::~GBM() {}

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
    return sigma;  // exact: b(t,x) = sigma*x => b'(t,x) = sigma
}

double GBM::sample_terminal(double S0, double T, NormalRng& rng) const
{
    double Z = rng.draw();
    return S0 * std::exp((mu - 0.5 * sigma * sigma) * T + sigma * std::sqrt(T) * Z);
}

void GBM::drift_param(double mu_in) { mu = mu_in; }
double GBM::drift_param() const { return mu; }
void GBM::vol_param(double sigma_in) { sigma = sigma_in; }
double GBM::vol_param() const { return sigma; } 