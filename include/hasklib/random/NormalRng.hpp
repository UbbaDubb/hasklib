// NormalRng.hpp
#ifndef NORMALRNG_H
#define NORMALRNG_H
#include <random>

class NormalRng
{
protected:
    std::mt19937 engine; // Mersenne Twister random number engine
    std::normal_distribution<double> dist; // Standard normal distribution

public:
    // Constructors/Destructor
    NormalRng();
    NormalRng(unsigned int seed);
    ~NormalRng();

    // Draw a sample from the standard normal distribution
    double draw();
};
#endif
