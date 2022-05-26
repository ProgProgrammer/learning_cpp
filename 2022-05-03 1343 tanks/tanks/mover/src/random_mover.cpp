#include "random_mover.h"
#include <random>

int getRandomIntDll(int & min, int & max)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min, max);
    auto random_integer = uni(rng);
    return random_integer;
}
