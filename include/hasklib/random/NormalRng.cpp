// NormalRng.cpp
#include "NormalRng.hpp"

NormalRng::NormalRng()
    : engine(std::random_device{}()), dist(0.0, 1.0)
{
}

NormalRng::NormalRng(unsigned int seed)
    : engine(seed), dist(0.0, 1.0)
{
}

NormalRng::~NormalRng() {}

double NormalRng::draw()
{
    return dist(engine);
}