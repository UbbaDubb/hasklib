// Process.cpp
#include "Process.hpp"

// Constructors/Destructor
StochasticProcess::StochasticProcess() {}

StochasticProcess::~StochasticProcess() {}

// Diffusion derivative to be implemented by derived classes
double StochasticProcess::diffusion_derivative(double t, double x) const
{
    double h = 1e-5;
    return (diffusion(t, x + h) - diffusion(t, x - h)) / (2.0 * h);
}