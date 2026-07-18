// EulerMaruyama.hpp
#ifndef EULERMARUYAMA_H
#define EULERMARUYAMA_H
#include <cmath>
#include "Process.hpp"
#include "hasklib/random/NormalRng.hpp"

class EulerMaruyama
{
protected:
    // Stateless — the scheme owns no parameters of its own,
    // it just steps whatever StochasticProcess it's given.

public:
    // Constructor/Destructor
    EulerMaruyama() {}
    ~EulerMaruyama() {}

    // Single step: X_{t+dt} = X_t + a(t,X_t)*dt + b(t,X_t)*sqrt(dt)*Z
    double step(const StochasticProcess& process, double t, double x,
                double dt, double z) const
    {
        double a = process.drift(t, x);
        double b = process.diffusion(t, x);
        return x + a * dt + b * std::sqrt(dt) * z;
    }

    // Simulate the full path from 0 to T in N equal steps,
    // return the terminal value X_T
    double simulate_terminal(const StochasticProcess& process, double x0,
                              double T, int N, NormalRng& rng) const
    {
        double dt = T / static_cast<double>(N);
        double x  = x0;
        double t  = 0.0;

        for (int i = 0; i < N; ++i)
        {
            double z = rng.draw();
            x = step(process, t, x, dt, z);
            t += dt;
        }
        return x;
    }
};
#endif