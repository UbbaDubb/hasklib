// test_stochastic.cpp
#include "hasklib/stochastic/GBM.hpp"
#include "hasklib/random/NormalRng.hpp"
#include <cmath>
#include <iostream>
#include <cassert>

int main()
{
    // --- GBM moment check ---
    // Parameters
    double S0    = 100.0;
    double mu    = 0.05;
    double sigma = 0.2;
    double T     = 1.0;

    GBM gbm(mu, sigma);
    NormalRng rng(42);  // fixed seed for reproducibility

    long N = 200000;
    double sum   = 0.0;
    double sumSq = 0.0;

    for (long i = 0; i < N; ++i)
    {
        double ST = gbm.sample_terminal(S0, T, rng);
        sum   += ST;
        sumSq += ST * ST;
    }

    double empMean = sum / N;
    double empVar  = (sumSq / N) - (empMean * empMean);

    // Closed-form GBM moments
    double exactMean = S0 * std::exp(mu * T);
    double exactVar  = S0 * S0 * std::exp(2.0 * mu * T) * (std::exp(sigma * sigma * T) - 1.0);

    double meanTol = 0.05 * exactMean;   // 5% tolerance
    double varTol  = 0.05 * exactVar;    // 5% tolerance

    std::cout << "Empirical mean: " << empMean << ", Exact mean: " << exactMean << "\n";
    std::cout << "Empirical var:  " << empVar  << ", Exact var:  " << exactVar  << "\n";

    assert(std::abs(empMean - exactMean) < meanTol);
    assert(std::abs(empVar  - exactVar)  < varTol);

    // --- diffusion_derivative check (should be exact: sigma) ---
    assert(std::abs(gbm.diffusion_derivative(0.0, S0) - sigma) < 1e-12);

    std::cout << "All stochastic tests passed.\n";
    return 0;
}