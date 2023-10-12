#include "userwidget.h"
#include "ui_userwidget.h"

UserWidget::UserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWidget)
{
    ui->setupUi(this);
}

UserWidget::~UserWidget()
{
    delete ui;
}

void UserWidget::setUser(chat::User *user)
{
    _user = user;
    _userID = user->id();
    ui->labelUserLogin->setText(user->login().data());
    ui->labelUserName->setText(user->FullName().data());
}

ullong UserWidget::userID()
{
    return _userID;
}
