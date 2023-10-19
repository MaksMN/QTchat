#include "userwidget.h"
#include "ui_userwidget.h"

UserWidget::UserWidget(QWidget *parent)
    : QWidget(parent)
    , _user(nullptr)
    , ui(new Ui::UserWidget)

{
    ui->setupUi(this);
    this->setVisible(false);
}

UserWidget::~UserWidget()
{
    delete ui;
}

void UserWidget::setUser(std::shared_ptr<chat::User> user)
{
    if (user == nullptr) {
        this->setVisible(false);
        return;
    }
    _user = user;
    _userID = user->id();
    ui->labelUserLogin->setText(user->login());
    ui->labelUserName->setText(user->FullName());
    ui->labelUserReg->setText(user->regDateTime());
    this->setVisible(true);
}

ullong UserWidget::userID()
{
    return _userID;
}
