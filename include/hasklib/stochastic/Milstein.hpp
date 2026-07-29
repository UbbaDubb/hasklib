// Milstein.hpp
#ifndef MILSTEIN_H
#define MILSTEIN_H
#include "Process.hpp"
#include "hasklib/random/NormalRng.hpp"

class Milstein  
{
protected:
    // Stateless — the scheme owns no parameters of its own,
    // it just steps whatever StochasticProcess it's given.

public:
    // Constructor/Destructor
    Milstein();
    ~Milstein();

    // Single step: X_{t+dt} = X_t + a(t,X_t)*dt + b(t,X_t)*sqrt(dt)*Z +1/2*b(t,X_t)*b'(t,X_t)*dt*(Z^2 - 1)
    double step(const StochasticProcess& process, double t, double x,
                double dt, double z) const;

    // Simulate the full path from 0 to T in N equal steps,
    // return the terminal value X_T
    double simulate_terminal(const StochasticProcess& process, double x0,
                              double T, int N, NormalRng& rng) const;
};
#endif