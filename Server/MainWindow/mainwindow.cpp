#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "serversettings.h"
#include "user.h"
#include "userscontainer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    console.setConsole(ui->console);
    _users = new UsersContainer(ui->listUsers);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _users;
}

void MainWindow::consoleWrite(QString line)
{
    QMutexLocker locker(&mutex);
    console.writeLine(line);
}

void MainWindow::updateUsers(const QVector<std::shared_ptr<chat::User>> &users)
{
    _users->Update(users);
}

void MainWindow::on_actionShut_Down_triggered()
{
    close();
}

void MainWindow::on_actionServer_Settings_triggered()
{
    ServerSettings ss(this);
    ss.show();
    ss.exec();
}
