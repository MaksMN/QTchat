#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "auth.h"
#include "strings.h"

MainWindow::MainWindow(bool &close_app, QWidget *parent)
    : QMainWindow(parent)
    , _close_app(close_app)
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

void MainWindow::setUser(std::shared_ptr<chat::User> &_user)
{
    user = _user;
    ui->labelUserInfo->setText(user->FullName() + " " + user->login());
}

QPushButton *MainWindow::getSendButton()
{
    return ui->btnSend;
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

qlonglong MainWindow::getSelectedUserID() const
{
    QListWidgetItem *item = ui->listUsers->selectedItems().isEmpty()
                                ? nullptr
                                : ui->listUsers->selectedItems()[0];
    if (item == nullptr) {
        return -1;
    }
    UserWidget *w = qobject_cast<UserWidget *>(ui->listUsers->itemWidget(item));
    return w->user()->id();
}

qlonglong MainWindow::getCurrentUserID() const
{
    if (!user)
        return -1;
    else
        return user->id();
}

qlonglong MainWindow::getCurrentUserSessionKey() const
{
    if (!user)
        return 0;
    else
        return user->session_key();
}

QString MainWindow::getTextLine()
{
    return ui->lineEdit->text();
}

void MainWindow::setStatusText(QString text)
{
    ui->labelStatus->setText(text);
}

void MainWindow::app_close_no()
{
    _close_app = false;
    close();
}

void MainWindow::updateUsers(QVector<std::shared_ptr<chat::User>> users)
{
    _users->Update(users);
}

void MainWindow::updateMessages(QVector<std::shared_ptr<chat::Message>> messages)
{
    _messages->Update(messages);
}

Commands MainWindow::getCommand() const
{
    return command;
}

void MainWindow::on_btnPubChat_clicked()
{
    ui->btnSend->setEnabled(true);
    ui->lineEdit->setEnabled(true);
    ui->labelStatus->setText(QString());
    command = public_chat;
}

void MainWindow::on_listUsers_itemSelectionChanged()
{
    QListWidgetItem *item = ui->listUsers->selectedItems().isEmpty()
                                ? nullptr
                                : ui->listUsers->selectedItems()[0];
    if (item == nullptr) {
        command = public_chat;
        return;
    }
    UserWidget *w = qobject_cast<UserWidget *>(ui->listUsers->itemWidget(item));
    if (w->user()->id() == user->id()) {
        ui->btnSend->setEnabled(false);
        ui->lineEdit->setEnabled(false);
        ui->labelStatus->setText(Strings::t(Strings::FORBIDDEN_PERSONAL_MESSAGES_YOURSELF));
        command = public_chat;
        return;
    }
    ui->listMessages->clear();
    ui->btnSend->setEnabled(true);
    ui->lineEdit->setEnabled(true);
    ui->labelStatus->setText(QString());

    command = private_chat;
}

void MainWindow::on_btnSend_clicked()
{
    if (ui->lineEdit->text().isEmpty()) {
        ui->labelStatus->setText(Strings::t(Strings::YOU_HAVE_TO_ENTER_THE_TEXT));
        return;
    }
    QJsonObject request;
    request["command"] = "sendMessage";
    request["status"] = command == private_chat ? "private" : "public";
    request["reader_id"] = getCurrentUserID();
    request["interlocutor_id"] = getSelectedUserID();
    request["text"] = ui->lineEdit->text();
    request["user_id"] = getCurrentUserID();
    request["user_session_key"] = getCurrentUserSessionKey();
    QJsonDocument jdoc(request);

    Client cl;

    QJsonDocument response = cl.send(jdoc, 3, false);

    if (response["response"].toString() == "fail") {
        ui->labelStatus->setText(Strings::t(Strings::FAILED_TO_SEND_MESSAGE));
    } else {
        ui->lineEdit->clear();
        ui->listMessages->scrollToBottom();
    }
}

void MainWindow::on_actionShut_Down_triggered()
{
    close();
}

void MainWindow::on_actionExit_triggered()
{
    app_close_no();
}
