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
    chat::User user(1, "login", "name", "family", 0, chat::user::common);

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
