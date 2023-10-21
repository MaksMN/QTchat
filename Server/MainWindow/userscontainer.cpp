#include "userscontainer.h"

UsersContainer::UsersContainer() {}

UsersContainer::UsersContainer(QListWidget *list)
    : _list(list)
{}

void UsersContainer::Update(QVector<std::shared_ptr<chat::User>> &users)
{
    if (users.isEmpty() && _list->count() > 0) {
        _list->clear();
        return;
    }
    QPoint topLeft = _list->viewport()->rect().topLeft();
    QListWidgetItem *topItem = _list->itemAt(topLeft);
    int topItemID = _list->row(topItem);
    if (topItemID < 0)
        topItemID = 0;

    if (topItemID + users.size() > _list->count()) {
        int ex = topItemID + users.size() - _list->count();
        for (int i = 0; i < ex; ++i) {
            UserWidget *w = new UserWidget();
            _list->addItem(w->item());
            _list->setItemWidget(w->item(), w);
        }
    }

    for (int i = 0; i < users.size(); ++i) {
        UserWidget *w = qobject_cast<UserWidget *>(_list->itemWidget(_list->item(i + topItemID)));
        w->Update(users[i]);
    }
    if (_list->count() > topItemID + users.size()) {
        int start_delete = topItemID + users.size();
        for (int i = start_delete; i < _list->count(); ++i) {
            QWidget *widget = _list->itemWidget(_list->item(i));
            delete _list->takeItem(i);
            delete widget;
        }
    }
}

UserWidget *UsersContainer::getWidget(int id)
{
    return _widgets[id];
}
