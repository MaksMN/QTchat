#ifndef APP_H
#define APP_H

#include <QObject>

class APP
{
public:
    APP();

    virtual void ConsoleWrite(const QString &line) = 0;
    virtual void ConsoleWrite(const QString &&line) = 0;
};

#endif // APP_H
