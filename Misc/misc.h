#ifndef MISC_H
#define MISC_H
#include <QObject>
#include "SimpleIni.h"

typedef unsigned int uint;
typedef unsigned long long ullong;

class Misc
{
public:
    Misc();

    static qlonglong randomKey();

    static void msgBox(QString text, QString infText);

    static bool iniWrite(const QString &section,
                         const QString &parameter,
                         const QString &value,
                         CSimpleIniA *ini,
                         const QString &path);
    static bool iniWrite(const QString &section,
                         const QString &parameter,
                         int value,
                         CSimpleIniA *ini,
                         const QString &path);
    static QString stampTotime(qlonglong timestamp);
};

#endif // MISC_H
