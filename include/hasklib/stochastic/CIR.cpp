// CIR.cpp
#include "CIR.hpp"
#include <cmath>
#include <algorithm>

CIR::CIR() : kappa(0.0), theta(0.0), sigma(0.0) {}

CIR::CIR(double kappa, double theta, double sigma)
    : kappa(kappa), theta(theta), sigma(sigma) {}

CIR::~CIR() {}

double CIR::drift(double t, double x) const
{
    return kappa * (theta - x);
}

double CIR::diffusion(double t, double x) const
{
    return sigma * std::sqrt(std::max(x, 0.0));
}

double CIR::diffusion_derivative(double t, double x) const
{
    double xSafe = std::max(x, 1e-12); // so as to not divide by zero
    return sigma / (2.0 * std::sqrt(xSafe));
}


void   CIR::reversion_speed(double kappa_in) { kappa = kappa_in; }
double CIR::reversion_speed() const          { return kappa; }
void   CIR::mean_level(double theta_in)      { theta = theta_in; }
double CIR::mean_level() const               { return theta; }
void   CIR::vol_param(double sigma_in)       { sigma = sigma_in; }
double CIR::vol_param() const                { return sigma; }
