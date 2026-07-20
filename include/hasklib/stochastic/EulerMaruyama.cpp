// EulerMaruyama.cpp
#include "EulerMaruyama.hpp"
#include <cmath>

EulerMaruyama::EulerMaruyama() {}

EulerMaruyama::~EulerMaruyama() {}

double EulerMaruyama::step(const StochasticProcess& process, double t, double x,
                            double dt, double z) const
{
    double a = process.drift(t, x);
    double b = process.diffusion(t, x);
    return x + a * dt + b * std::sqrt(dt) * z;
}

double EulerMaruyama::simulate_terminal(const StochasticProcess& process, double x0,
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