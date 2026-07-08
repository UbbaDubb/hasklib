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
    NormalRng() : engine(std::random_device{}()), dist(0.0, 1.0) {}
    NormalRng(unsigned int seed) : engine(seed), dist(0.0, 1.0) {}
    ~NormalRng() {}

    double draw() { return dist(engine); }
};
#endif
