#include "useritem.h"

UserItem::UserItem()
{
    userWidget->setUser(nullptr);
}

UserItem::UserItem(const std::shared_ptr<chat::User> &user)

    : _user(user)
{
    userWidget->setUser(_user);
}

void UserItem::Update()
{
    if (_user == nullptr) {
        this->setHidden(true);
        return;
    }
    userWidget->setUser(_user);
    this->setHidden(false);
}

void UserItem::Update(const std::shared_ptr<chat::User> user)
{
    _user = user;
    Update();
}
