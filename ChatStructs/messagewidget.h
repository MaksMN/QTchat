#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QListWidgetItem>
#include <QWidget>
#include "ChatStructs_global.h"
#include "message.h"
#include <memory>
namespace Ui {
class MessageWidget;
}

class CHATSTRUCTS_EXPORT MessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MessageWidget(QWidget *parent = nullptr);
    ~MessageWidget();
    void Update(std::shared_ptr<chat::Message> message);
    QListWidgetItem *item() const;

private:
    Ui::MessageWidget *ui;
    std::shared_ptr<chat::Message> _message = nullptr;
    int _id = -1;
    QListWidgetItem *_item{new QListWidgetItem()};
};

#endif // MESSAGEWIDGET_H
