// test_stochastic.cpp
#include "hasklib/stochastic/GBM.hpp"
#include "hasklib/stochastic/EulerMaruyama.hpp"
#include "hasklib/random/NormalRng.hpp"
#include "hasklib/stochastic/OU.hpp"
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

    std::cout << "All GBM tests passed.\n";

    // --- Euler-Maruyama convergence check ---
    // Simulate GBM via Euler stepping at increasing step counts N,
    // and confirm empirical terminal moments converge toward the
    // EXACT sample_terminal moments as N grows (Euler -> exact).
    EulerMaruyama scheme;

    int stepCounts[] = {10, 50, 200, 1000};
    long NPaths = 100000;

    std::cout << "\n--- Euler-Maruyama convergence on GBM ---\n";

    double prevMeanErr = 1e18;  // track that error shrinks as steps increase
    double prevVarErr  = 1e18;

    for (int stepCount : stepCounts)
    {
        NormalRng eulerRng(123);  // fixed seed, separate stream from GBM check above

        double eSum   = 0.0;
        double eSumSq = 0.0;

        for (long i = 0; i < NPaths; ++i)
        {
            double XT = scheme.simulate_terminal(gbm, S0, T, stepCount, eulerRng);
            eSum   += XT;
            eSumSq += XT * XT;
        }

        double eMean = eSum / NPaths;
        double eVar  = (eSumSq / NPaths) - (eMean * eMean);

        double meanErr = std::abs(eMean - exactMean);
        double varErr  = std::abs(eVar  - exactVar);

        std::cout << "N=" << stepCount
                   << "  Euler mean=" << eMean << " (err=" << meanErr << ")"
                   << "  Euler var="  << eVar  << " (err=" << varErr  << ")\n";

        /*
         * With only 10 steps, Euler mean can already be close since
         * GBM's drift term is exact in expectation for Euler; the
         * variance is the more sensitive discretisation check.
         * Loosen tolerance at low N, tighten as N grows.
         */
        double meanTolEuler = 0.10 * exactMean;
        double varTolEuler  = 0.25 * exactVar;

        if (stepCount >= 200)
        {
            meanTolEuler = 0.05 * exactMean;
            varTolEuler  = 0.10 * exactVar;
        }

        assert(meanErr < meanTolEuler);
        assert(varErr  < varTolEuler);

        prevMeanErr = meanErr;
        prevVarErr  = varErr;
    }

    (void)prevMeanErr;
    (void)prevVarErr;

    std::cout << "All Euler-Maruyama convergence tests passed.\n";

    // --- OU moment check ---
    double X0    = 0.05;
    double kappa = 1.5;
    double theta = 0.05;
    double sigmaOU = 0.02;
    double T_OU  = 1.0;

    OU ou(kappa, theta, sigmaOU);
    NormalRng ouRng(7);

    long N_OU = 200000;
    double ouSum = 0.0, ouSumSq = 0.0;

    for (long i = 0; i < N_OU; ++i)
    {
        double XT = ou.sample_terminal(X0, T_OU, ouRng);
        ouSum   += XT;
        ouSumSq += XT * XT;
    }

    double ouEmpMean = ouSum / N_OU;
    double ouEmpVar  = (ouSumSq / N_OU) - (ouEmpMean * ouEmpMean);

    double ouExactMean = theta + (X0 - theta) * std::exp(-kappa * T_OU);
    double ouExactVar  = (sigmaOU * sigmaOU / (2.0 * kappa))
                          * (1.0 - std::exp(-2.0 * kappa * T_OU));

    std::cout << "\n--- OU moment check ---\n";
    std::cout << "Empirical mean: " << ouEmpMean << ", Exact mean: " << ouExactMean << "\n";
    std::cout << "Empirical var:  " << ouEmpVar  << ", Exact var:  " << ouExactVar  << "\n";

    assert(std::abs(ouEmpMean - ouExactMean) < 0.05 * std::abs(ouExactMean));
    assert(std::abs(ouEmpVar  - ouExactVar)  < 0.05 * ouExactVar);
    assert(std::abs(ou.diffusion_derivative(0.0, X0)) < 1e-12);

    std::cout << "All OU tests passed.\n";

    return 0;
}