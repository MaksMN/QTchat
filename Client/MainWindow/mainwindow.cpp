#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "auth.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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
}
