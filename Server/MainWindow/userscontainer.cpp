#include "userscontainer.h"

UsersContainer::UsersContainer() {}

UsersContainer::UsersContainer(QListWidget *list)
    : _list(list)
{
    
}

void UsersContainer::Update(QVector<std::shared_ptr<chat::User>> &users)
{
    QPoint topLeft = _list->viewport()->rect().topLeft();
    QListWidgetItem *topItem = _list->itemAt(topLeft);
    int topItemID = _list->row(topItem);
    if (topItemID < 0)
        topItemID = 0;

    if (topItemID + users.size() > _list->count()) {
        int ex = topItemID + users.size() - _list->count();
        for (int i = 0; i < ex; ++i) {
            QListWidgetItem *item = new QListWidgetItem();
            _list->addItem(item);
        }
    }
    //auto test = _list->count();
    for (int i = 0; i < users.size(); ++i) {
        _list->item(i + topItemID)
            ->setText(users[i]->FullName() + "\n" + users[i]->login() + "\n"
                      + users[i]->regDateTime());
        continue;
    }
    if (_list->count() > topItemID + users.size()) {
        int start_delete = topItemID + users.size();
        for (int i = start_delete; i < _list->count(); ++i) {
            delete _list->takeItem(i);
        }
    }
}

UserWidget *UsersContainer::getWidget(int id)
{
    return _widgets[id];
}
