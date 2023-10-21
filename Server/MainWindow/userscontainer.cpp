#include "userscontainer.h"

UsersContainer::UsersContainer() {}

UsersContainer::UsersContainer(QListWidget *list)
    : _list(list)
{
    for (int i = 0; i < _count; ++i) {
        UserWidget *w = new UserWidget();
        _widgets.push_back(w);
        _list->addItem(w->item());
        _list->setItemWidget(w->item(), w);
        w->item()->setHidden(true);
        w->setId(i);
    }
}

void UsersContainer::Update(QVector<std::shared_ptr<chat::User>> &users)
{
    if (_count < users.size()) {
        int ex = users.size() - _count;
        for (int i = 0; i < ex; ++i) {
            UserWidget *w = new UserWidget();
            _widgets.push_back(w);
            _list->addItem(w->item());
            _list->setItemWidget(w->item(), w);
            w->item()->setHidden(true);
            w->setId(i);
        }
    }
    _count = users.size();
    _users = users;
    for (int i = 0; i < _count; ++i) {
        if (users.size() > i) {
            _widgets[i]->Update(users[i]);
            continue;
        }
        _widgets[i]->Update(nullptr);
    }
}

UserWidget *UsersContainer::getWidget(int id)
{
    return _widgets[id];
}
