// ABM.cpp
#include "ABM.hpp"
#include <cmath>

ABM::ABM() : mu(0.0), sigma(0.0) {}

ABM::ABM(double mu, double sigma) : mu(mu), sigma(sigma) {}

double ABM::drift(double t, double x) const
{
    return mu;  // constant — no dependence on x
}

double ABM::diffusion(double t, double x) const
{
    return sigma;  // constant — no dependence on x
}

double ABM::diffusion_derivative(double t, double x) const
{
    return 0.0;  // b(t,x) = sigma (constant) => b'(t,x) = 0
}

double ABM::sample_terminal(double X0, double T, NormalRng& rng) const
{
    double Z = rng.draw();
    return X0 + mu * T + sigma * std::sqrt(T) * Z;
}

void ABM::drift_param(double mu_in) { mu = mu_in; }
double ABM::drift_param() const { return mu; }
void ABM::vol_param(double sigma_in) { sigma = sigma_in; }
double ABM::vol_param() const { return sigma; }