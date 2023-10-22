#include "mainwindow.h"
#include <QScrollBar>
#include "./ui_mainwindow.h"
#include "mainthread.h"
#include "serversettings.h"
#include "strings.h"
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
    delete _messages;
}

void MainWindow::ConsoleWrite(const QString &line)
{
    consoleWrite(line);
}

void MainWindow::ConsoleWrite(const QString &&line)
{
    consoleWrite(line);
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

void MainWindow::on_btnUserDelete_clicked()
{
    userActions("deleteUserByID", true);
}

void MainWindow::on_btnUserBan_clicked()
{
    userActions("banUserByID");
    if (ui->btnUserBan->text() == Strings::t(Strings::BAN))
        ui->btnUserBan->setText(Strings::t(Strings::UNBAN));
    else
        ui->btnUserBan->setText(Strings::t(Strings::BAN));
}

void MainWindow::on_btnUserUnlogin_clicked()
{
    userActions("unloginUserByID");
}

void MainWindow::on_btnMessageDelete_clicked()
{
    messageActions("deleteMessage", true);
}

void MainWindow::on_btnMessageHide_clicked()
{
    messageActions("hideMessage");
}

void MainWindow::userActions(const QString &&method, bool deleteItem)
{
    QListWidgetItem *item = ui->listUsers->selectedItems().isEmpty()
                                ? nullptr
                                : ui->listUsers->selectedItems()[0];
    if (item == nullptr) {
        consoleWrite(Strings::t(Strings::USER_NOT_SELECTED));
        return;
    }
    UserWidget *w = qobject_cast<UserWidget *>(ui->listUsers->itemWidget(item));
    auto u = w->user()->id();
    if (u < 2) {
        ConsoleWrite(Strings::t(Strings::NOT_APPLICABLE_FOR_SERVICE_USERS));
        return;
    }
    if (deleteItem) {
        delete ui->listUsers->takeItem(ui->listUsers->row(item));
        delete w;
    }
    QMetaObject::invokeMethod(mainThread,
                              method.toStdString().data(),
                              Qt::QueuedConnection,
                              Q_ARG(qlonglong, u));
}

void MainWindow::messageActions(const QString &&method, bool deleteItem)
{
    QListWidgetItem *item = ui->listMessages->selectedItems().isEmpty()
                                ? nullptr
                                : ui->listMessages->selectedItems()[0];
    if (item == nullptr) {
        consoleWrite(Strings::t(Strings::MESSAGE_NOT_SELECTED));
        return;
    }
    MessageWidget *w = qobject_cast<MessageWidget *>(ui->listMessages->itemWidget(item));
    auto m = w->message()->id();

    if (deleteItem) {
        delete ui->listMessages->takeItem(ui->listMessages->row(item));
        delete w;
    }
    QMetaObject::invokeMethod(mainThread,
                              method.toStdString().data(),
                              Qt::QueuedConnection,
                              Q_ARG(qlonglong, m));
}

void MainWindow::on_listUsers_itemSelectionChanged()
{
    QListWidgetItem *item = ui->listUsers->selectedItems().isEmpty()
                                ? nullptr
                                : ui->listUsers->selectedItems()[0];
    if (item == nullptr) {
        consoleWrite(Strings::t(Strings::USER_NOT_SELECTED));
        return;
    }
    UserWidget *w = qobject_cast<UserWidget *>(ui->listUsers->itemWidget(item));
    if (w->user()->isBanned()) {
        w->user()->unban();
        ui->btnUserBan->setText(Strings::t(Strings::UNBAN));
    } else {
        w->user()->ban();
        ui->btnUserBan->setText(Strings::t(Strings::BAN));
    }
}
