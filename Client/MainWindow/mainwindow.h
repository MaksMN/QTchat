#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "commands.h"
#include "messagescontainer.h"
#include "user.h"
#include "userscontainer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    std::shared_ptr<chat::User> current_user = nullptr;

public:
    MainWindow(bool &close_app, QWidget *parent = nullptr);
    ~MainWindow();

    int topUserItem = 0;
    int topMessageItem = 0;

    void setUser(std::shared_ptr<chat::User> &_user);
    QPushButton *getSendButton();

public slots:
    void updateUsers(QVector<std::shared_ptr<chat::User>> users);
    void updateMessages(QVector<std::shared_ptr<chat::Message>> messages);
    /// Индекс элемента вверху окна списка
    int getTopUserItem();
    int getTopMessageItem();

    Commands getCommand() const;
    qlonglong getSelectedUserID() const;
    qlonglong getCurrentUserID() const;
    qlonglong getCurrentUserSessionKey() const;
    QString getTextLine();
    void setStatusText(QString text);

    void app_close_no();

private:
    bool &_close_app;
    Ui::MainWindow *ui;
    std::shared_ptr<chat::User> user = nullptr;
    UsersContainer *_users{};
    MessagesContainer *_messages{};
    Commands command = public_chat;
    qlonglong selected_user = -1;

signals:
    void mainWindowClosed();

protected:
    void closeEvent(QCloseEvent *event) override
    {
        emit mainWindowClosed();
        QMainWindow::closeEvent(event);
    }
private slots:
    void on_btnPubChat_clicked();
    void on_listUsers_itemSelectionChanged();
    void on_btnSend_clicked();
    void on_actionShut_Down_triggered();
    void on_actionExit_triggered();
};

#endif // MAINWINDOW_H
