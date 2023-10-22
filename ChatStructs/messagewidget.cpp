#include "messagewidget.h"
#include "ui_messagewidget.h"

MessageWidget::MessageWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MessageWidget)
{
    ui->setupUi(this);

    _item->setHidden(true);
}

MessageWidget::~MessageWidget()
{
    delete ui;
}

void MessageWidget::Update(std::shared_ptr<chat::Message> message)
{
    _message = message;
    if (message == nullptr) {
        this->setVisible(false);
        return;
    }
    ui->labelUser->setText(message->author()->FullName());
    ui->labelText->setText(message->text());
    ui->labelTime->setText(message->pubDateTime());
    _item->setSizeHint(this->sizeHint());
    this->setVisible(true);
}

QListWidgetItem *MessageWidget::item() const
{
    return _item;
}

std::shared_ptr<chat::Message> MessageWidget::message() const
{
    return _message;
}
