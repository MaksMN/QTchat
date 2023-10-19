#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>
#include "message.h"

namespace Ui {
class MessageWidget;
}

class MessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MessageWidget(QWidget *parent = nullptr);
    ~MessageWidget();
    void setMessage(std::shared_ptr<chat::Message> message);

private:
    Ui::MessageWidget *ui;
    std::shared_ptr<chat::Message> _message = nullptr;
};

#endif // MESSAGEWIDGET_H
