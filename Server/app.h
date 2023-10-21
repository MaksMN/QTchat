#ifndef APP_H
#define APP_H

#include <QObject>
#include "message.h"
#include "user.h"

class APP
{
public:
    APP();

    virtual void ConsoleWrite(const QString &line) = 0;
    virtual void ConsoleWrite(const QString &&line) = 0;
    virtual void UpdateUsers(QVector<std::shared_ptr<chat::User>> users) = 0;
    virtual void UpdateMessages(QVector<std::shared_ptr<chat::Message>> messages) = 0;
};

#endif // APP_H
