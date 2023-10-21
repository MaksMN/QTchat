#ifndef USERSCONTAINER_H
#define USERSCONTAINER_H

#include <QListWidgetItem>
#include <QObject>
#include "user.h"
#include "userwidget.h"

class UsersContainer : public QObject
{
    Q_OBJECT
private:
    QListWidget *_list = nullptr;
    QVector<std::shared_ptr<chat::User>> _users;
    QVector<UserWidget *> _widgets;
    int _count = 100;

public:
    UsersContainer();
    UsersContainer(QListWidget *list);
    void Update(QVector<std::shared_ptr<chat::User>> &users);
    UserWidget *getWidget(int id = 0);
};

#endif // USERSCONTAINER_H
