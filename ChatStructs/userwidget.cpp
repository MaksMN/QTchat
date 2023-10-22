#include "userwidget.h"
#include "ui_userwidget.h"

UserWidget::UserWidget(QWidget *parent)
    : QWidget(parent)
    , _user(nullptr)
    , ui(new Ui::UserWidget)

{
    ui->setupUi(this);

    _item->setHidden(true);
}

UserWidget::~UserWidget()
{
    delete ui;
}

void UserWidget::Update(const std::shared_ptr<chat::User> &user)
{
    _user = user;
    Update();
}

void UserWidget::Update()
{
    if (_user == nullptr) {
        _item->setHidden(true);
        return;
    }
    QString status = _user->getGroup();
    ui->labelUserLogin->setText("@" + _user->login() + " (" + status + ")");
    ui->labelUserName->setText(_user->FullName());
    ui->labelUserReg->setText(_user->regDateTime());

    _item->setHidden(false);
    _item->setSizeHint(this->sizeHint());
}

int UserWidget::id() const
{
    return _id;
}

void UserWidget::setId(int id)
{
    _id = id;
}

QListWidgetItem *UserWidget::item() const
{
    return _item;
}

std::shared_ptr<chat::User> UserWidget::user() const
{
    return _user;
}

void UserWidget::setUser(const std::shared_ptr<chat::User> &user)
{
    _user = user;
}
