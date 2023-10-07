#ifndef MISC_H
#define MISC_H
#include <cstdlib>
#include <cstring>
#include <map>
#include <time.h>

typedef unsigned int uint;
typedef unsigned long long ullong;

class Misc
{
public:
    Misc();
    static ullong randomKey();

    static void createConfigMap();
};

#endif // MISC_H
