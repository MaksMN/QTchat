#include "messagescontainer.h"
#include <QScrollBar>

MessagesContainer::MessagesContainer(QListWidget *list)
    : _list(list)
{}

void MessagesContainer::Update(QVector<std::shared_ptr<chat::Message> > &messages)
{
    if (messages.isEmpty() && _list->count() > 0) {
        _list->clear();
        return;
    }
    bool scroll_down = false;
    QPoint topLeft = _list->viewport()->rect().topLeft();
    QListWidgetItem *topItem = _list->itemAt(topLeft);
    int topItemID = _list->row(topItem);
    if (topItemID < 0)
        topItemID = 0;
    auto sb_val = _list->verticalScrollBar()->value();
    if (sb_val > _list->verticalScrollBar()->maximum() - 1)
        scroll_down = true;
    else
        scroll_down = false;

    if (topItemID + messages.size() > _list->count()) {
        int ex = topItemID + messages.size() - _list->count();
        for (int i = 0; i < ex; ++i) {
            MessageWidget *w = new MessageWidget();
            _list->addItem(w->item());
            _list->setItemWidget(w->item(), w);
        }
    }

    for (int i = 0; i < messages.size(); ++i) {
        MessageWidget *w = qobject_cast<MessageWidget *>(
            _list->itemWidget(_list->item(i + topItemID)));
        w->Update(messages[i]);
    }
    if (_list->count() > topItemID + messages.size()) {
        int start_delete = topItemID + messages.size();
        for (int i = start_delete; i < _list->count(); ++i) {
            QWidget *widget = _list->itemWidget(_list->item(i));
            delete _list->takeItem(i);
            delete widget;
        }
    }
    if (scroll_down)
        _list->scrollToBottom();
}
