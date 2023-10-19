#include "messagewidget.h"
#include "ui_messagewidget.h"

MessageWidget::MessageWidget(QWidget *parent)
    : QWidget(parent)
    , _message(nullptr)
    , ui(new Ui::MessageWidget)
{
    ui->setupUi(this);
    this->setVisible(false);
}

MessageWidget::~MessageWidget()
{
    delete ui;
}

void MessageWidget::setMessage(std::shared_ptr<chat::Message> message)
{
    _message = message;
    if (message == nullptr) {
        this->setVisible(false);
        return;
    }
    ui->labelUser->setText(message->author()->FullName());
    ui->labelText->setText(message->text());
    ui->labelTime->setText(message->pubDateTime());
    this->setVisible(true);
}
