// Process.hpp
#ifndef PROCESS_H
#define PROCESS_H
#include "hasklib/core/types.hpp"

class StochasticProcess 
{
protected:
    // No stored parameters at this level — drift/diffusion are pure
    // functions of (t, x); concrete processes (GBM, OU, CIR) own their
    // own parameters and implement the formulas below.

public:
    // Constructor/Destructor
    StochasticProcess();
    virtual ~StochasticProcess() {}  // virtual destructor — base class used polymorphically

    // Pure virtual methods that must be implemented by derived classes
    virtual double drift(double t, double x) const = 0;
    virtual double diffusion(double t, double x) const = 0;

    // Diffusion derivative (needed for Milstein scheme). Provides a
    // central-difference default; override with a closed form where
    // one exists (e.g. GBM: sigma).
    virtual double diffusion_derivative(double t, double x) const;
};
#endif