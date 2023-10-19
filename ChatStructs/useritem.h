#ifndef USERITEM_H
#define USERITEM_H

#include <QListWidgetItem>
#include <QObject>
#include <QWidget>
#include "user.h"
#include "userwidget.h"

class UserItem : public QWidget, QListWidgetItem
{
    Q_OBJECT
private:
public:
    explicit UserItem(QWidget *parent = nullptr);

signals:

};

#endif // USERITEM_H
