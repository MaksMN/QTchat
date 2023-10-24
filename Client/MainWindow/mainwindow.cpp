#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "auth.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _users = new UsersContainer(ui->listUsers);
    _messages = new MessagesContainer(ui->listMessages);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _users;
    delete _messages;
}

bool MainWindow::AuthPage()
{
    Auth auth(this);
    auth.show();
    auth.exec();
    return auth.authorized();
}

void MainWindow::setUser(std::shared_ptr<chat::User> &_user)
{
    user = _user;
    ui->labelUserInfo->setText(user->FullName() + " " + user->login());
}

int MainWindow::getTopUserItem()
{
    QPoint topLeft = ui->listUsers->viewport()->rect().topLeft();
    QListWidgetItem *topItem = ui->listUsers->itemAt(topLeft);
    int topItemID = ui->listUsers->row(topItem);
    if (topItemID < 0)
        topItemID = 0;

    return topItemID;
}

int MainWindow::getTopMessageItem()
{
    QPoint topLeft = ui->listMessages->viewport()->rect().topLeft();
    QListWidgetItem *topItem = ui->listMessages->itemAt(topLeft);
    int topItemID = ui->listMessages->row(topItem);
    if (topItemID < 0)
        topItemID = 0;
    return topItemID;
}

void MainWindow::updateUsers(QVector<std::shared_ptr<chat::User>> users)
{
    _users->Update(users);
}

void MainWindow::updateMessages(QVector<std::shared_ptr<chat::Message>> messages)
{
    _messages->Update(messages);
}
