// NormalRng.hpp
#ifndef NORMALRNG_H
#define NORMALRNG_H
#include <random>

class NormalRng
{
protected:
    std::mt19937 engine;
    std::normal_distribution<double> dist;

public:
    NormalRng();
    NormalRng(unsigned int seed);
    ~NormalRng();

    double draw();
};
#endif
