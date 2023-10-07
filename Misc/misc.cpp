#include "misc.h"

Misc::Misc()
{
    
}

ullong Misc::randomKey()
{
    char buf[8];
    ullong key = std::abs(std::rand());
    std::srand(time(NULL) - key);
    for (int i{0}; i < 8; i++) {
        buf[i] = std::abs(std::rand());
    }
    memcpy(&key, buf, 8);
    return key;
}
