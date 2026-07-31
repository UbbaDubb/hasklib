// NormalRng.cpp
#include "NormalRng.hpp"

// Default constructor
NormalRng::NormalRng()
    : engine(std::random_device{}()), dist(0.0, 1.0)
{
}

// Constructor by input
NormalRng::NormalRng(unsigned int seed)
    : engine(seed), dist(0.0, 1.0)
{
}

// Destructor
NormalRng::~NormalRng() {}

// Sample from the standard normal distribution
double NormalRng::draw()
{
    return dist(engine);
}