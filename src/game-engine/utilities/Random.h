#pragma once
#include <random>

//Create a random utility class to have a improve of the simple GetRandomInt (that was not implemented correctly)
class Random
{
public:
    template <typename T>
    static std::enable_if_t<std::is_integral_v<T>, T> GetRandomNumber(const T min, const T max)
    {
        std::uniform_int_distribution<T> distribution(min, max);
        return distribution(Generator);
    }

    template <typename T>
    static std::enable_if_t<std::is_floating_point_v<T>, T> GetRandomNumber(const T min, const T max)
    {
        std::uniform_real_distribution<T> distribution(min, max);
        return distribution(Generator);
    }

    static void SetSeed(unsigned int seed);
    static thread_local std::mt19937 Generator;
};