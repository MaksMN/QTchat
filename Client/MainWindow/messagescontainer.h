#ifndef MESSAGESCONTAINER_H
#define MESSAGESCONTAINER_H

#include <QListWidgetItem>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "messagewidget.h"

class MessagesContainer : public QObject
{
    Q_OBJECT
    QListWidget *_list = nullptr;

    int _count = 0;

public:
    MessagesContainer(QListWidget *list);
    void Update(QVector<std::shared_ptr<chat::Message>> &messages);
};

#endif // MESSAGESCONTAINER_H
