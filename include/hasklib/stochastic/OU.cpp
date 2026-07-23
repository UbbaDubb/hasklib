// OU.cpp
#include "OU.hpp"
#include <cmath>

OU::OU() : kappa(0.0), theta(0.0), sigma(0.0) {}

OU::OU(double kappa, double theta, double sigma)
    : kappa(kappa), theta(theta), sigma(sigma) {}

OU::~OU() {}

double OU::drift(double t, double x) const
{
    return kappa * (theta - x);
}

double OU::diffusion(double t, double x) const
{
    return sigma;
}

double OU::diffusion_derivative(double t, double x) const
{
    return 0.0;  // b(t,x) = sigma (constant) => b'(t,x) = 0
}

double OU::sample_terminal(double X0, double T, NormalRng& rng) const
{
    double Z = rng.draw();
    double meanTerm = X0 * std::exp(-kappa * T) + theta * (1.0 - std::exp(-kappa * T));
    double stdTerm  = sigma * std::sqrt((1.0 - std::exp(-2.0 * kappa * T)) / (2.0 * kappa));
    return meanTerm + stdTerm * Z;
}

void   OU::reversion_speed(double kappa_in) { kappa = kappa_in; }
double OU::reversion_speed() const          { return kappa; }
void   OU::mean_level(double theta_in)      { theta = theta_in; }
double OU::mean_level() const               { return theta; }
void   OU::vol_param(double sigma_in)       { sigma = sigma_in; }
double OU::vol_param() const                { return sigma; }
