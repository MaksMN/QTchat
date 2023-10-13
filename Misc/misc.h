#ifndef MISC_H
#define MISC_H
#include <QObject>
#include "SimpleIni.h"
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

    static void msgBox(QString text, QString infText);

    static void iniWrite(const QString &&section,
                         const QString &&parameter,
                         const QString &value,
                         CSimpleIniA *ini);
    static void iniWrite(const QString &section,
                         const QString &parameter,
                         int value,
                         CSimpleIniA *ini);
};

#endif // MISC_H
