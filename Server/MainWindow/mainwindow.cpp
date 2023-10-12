#include "mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include "./ui_mainwindow.h"
#include "user.h"
#include "userwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

void MainWindow::on_pushButton_clicked() {}
