// Process.cpp
#include "Process.hpp"

StochasticProcess::StochasticProcess() {}

double StochasticProcess::diffusion_derivative(double t, double x) const
{
    double h = 1e-5;
    return (diffusion(t, x + h) - diffusion(t, x - h)) / (2.0 * h);
}