#include "misc.h"
#include "random"
Misc::Misc()
{
    
}

ullong Misc::randomKey()
{
    std::random_device rd;
    std::mt19937_64 generator(rd());
    std::uniform_int_distribution<unsigned long long> distribution;
    return distribution(generator);
}
