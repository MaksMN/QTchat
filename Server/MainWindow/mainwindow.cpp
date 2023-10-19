#include "mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include "./ui_mainwindow.h"
#include "serversettings.h"
#include "user.h"
#include "userwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    console.setConsole(ui->console);

    UserWidget *userwidget = new UserWidget();
    std::shared_ptr<chat::User> user
        = std::make_shared<chat::User>(1, "login", "name", "family", 0, chat::user::common);
    userwidget->setUser(user);
    QListWidgetItem *item1 = new QListWidgetItem();
    item1->setSizeHint(userwidget->sizeHint());
    ui->listUsers->addItem(item1);
    ui->listUsers->setItemWidget(item1, userwidget);

    UserWidget *userwidget2 = new UserWidget();
    std::shared_ptr<chat::User> user2 = nullptr;
    // = std::make_shared<chat::User>(2, "login2", "name2", "family2", 0, chat::user::common);

    QListWidgetItem *item2 = new QListWidgetItem();
    item2->setSizeHint(userwidget2->sizeHint());
    ui->listUsers->addItem(item2);
    ui->listUsers->setItemWidget(item2, userwidget2);
    userwidget2->setUser(user2);
    userwidget2->setHidden(true);
    // item2->setHidden(true);

    UserWidget *userwidget3 = new UserWidget();
    std::shared_ptr<chat::User> user3
        = std::make_shared<chat::User>(3, "login3", "name3", "family3", 0, chat::user::common);
    userwidget3->setUser(user3);
    QListWidgetItem *item3 = new QListWidgetItem();
    item3->setSizeHint(userwidget3->sizeHint());
    ui->listUsers->addItem(item3);
    ui->listUsers->setItemWidget(item3, userwidget3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::consoleWrite(QString line)
{
    QMutexLocker locker(&mutex);
    console.writeLine(line);
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
