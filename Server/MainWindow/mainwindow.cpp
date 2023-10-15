#include "mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include "../ServerSettings/serversettings.h"
#include "./ui_mainwindow.h"
#include "console.h"
#include "user.h"
#include "userwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Console::setConsole(ui->console);

    UserWidget *userwidget = new UserWidget();
    chat::User user(1, "login", "name", "family", chat::user::common);

    userwidget->setUser(&user);

    QListWidgetItem *item1 = new QListWidgetItem();
    item1->setSizeHint(userwidget->sizeHint());
    ui->listUsers->addItem(item1);
    ui->listUsers->setItemWidget(item1, userwidget);
}

MainWindow::~MainWindow()
{
    delete ui;
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
