#include "Random.h"

thread_local std::mt19937 Random::Generator{std::random_device{}()};

void Random::SetSeed(const unsigned int seed)
{
    Generator.seed(seed);
}