#include "mainwindow.h"
#include <QScrollBar>
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
    _messages = new MessagesContainer(ui->listMessages);
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

void MainWindow::updateUsers(QVector<std::shared_ptr<chat::User>> users)
{
    _users->Update(users);
}

void MainWindow::updateMessages(QVector<std::shared_ptr<chat::Message>> messages)
{
    _messages->Update(messages);
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
