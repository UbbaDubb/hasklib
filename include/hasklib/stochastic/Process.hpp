// Process.hpp
#ifndef PROCESS_H
#define PROCESS_H
#include "hasklib/core/types.hpp"

class StochasticProcess
{
public:
    // Constructors/Destructor
    StochasticProcess();
    virtual ~StochasticProcess();

    // Pure virtual functions for abstrac class
    virtual double drift(double t, double x) const = 0;
    virtual double diffusion(double t, double x) const = 0;

    // Diffusion derivative to be implemented by derived classes
    virtual double diffusion_derivative(double t, double x) const;
};
#endif
