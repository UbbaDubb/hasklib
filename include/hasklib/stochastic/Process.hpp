// Process.hpp
#ifndef PROCESS_H
#define PROCESS_H
#include "hasklib/core/types.hpp"

class StochasticProcess
{
public:
    StochasticProcess() = default;
    virtual ~StochasticProcess() {}

    virtual double drift(double t, double x) const = 0;
    virtual double diffusion(double t, double x) const = 0;

    virtual double diffusion_derivative(double t, double x) const {
        const double h = 1e-5;
        return (diffusion(t, x + h) - diffusion(t, x - h)) / (2.0 * h);
    }
};
#endif
