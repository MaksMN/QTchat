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

int MainWindow::getTopUserItem()
{
    QPoint topLeft = ui->listUsers->viewport()->rect().topLeft();
    QListWidgetItem *topItem = ui->listUsers->itemAt(topLeft);
    int topItemID = ui->listUsers->row(topItem);
    if (topItemID < 0)
        topItemID = 0;

    return topItemID;
}

qlonglong MainWindow::getUserInTopItem()
{
    auto user = _users->getWidget(getTopUserItem())->user();
    if (user == nullptr) {
        return -1;
    }
    return user->id();
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
