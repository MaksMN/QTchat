#ifndef USERITEM_H
#define USERITEM_H

#include <QListWidgetItem>
#include <QObject>
#include <QWidget>
#include "user.h"
#include "userwidget.h"

class UserItem : public QListWidgetItem
{
    Q_OBJECT
private:
    std::shared_ptr<chat::User> _user = nullptr;
    std::shared_ptr<UserWidget> userWidget{};

public:
    explicit UserItem();
    UserItem(const std::shared_ptr<chat::User> &user = nullptr);

    void Update();
    void Update(const std::shared_ptr<chat::User> user);
    void setUser(const std::shared_ptr<chat::User> user);

signals:
};

#endif // USERITEM_H
