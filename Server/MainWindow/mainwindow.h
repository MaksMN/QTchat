#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QEvent>
#include <QMainWindow>
#include <QMutex>
#include <QTranslator>
#include "app.h"
#include "console.h"
#include "message.h"
#include "messagescontainer.h"
#include "user.h"
#include "userscontainer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainThread;

class MainWindow : public QMainWindow, APP
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ConsoleWrite(const QString &line) override;
    void ConsoleWrite(const QString &&line) override;
public slots:
    void consoleWrite(QString line);

    void updateUsers(QVector<std::shared_ptr<chat::User>> users);
    void updateMessages(QVector<std::shared_ptr<chat::Message>> messages);

    /// Индекс элемента вверху окна списка
    int getTopUserItem();
    int getTopMessageItem();

private slots:
    void on_actionShut_Down_triggered();
    void on_actionServer_Settings_triggered();

    void on_btnUserDelete_clicked();

    void on_btnUserBan_clicked();

    void on_btnUserUnlogin_clicked();

    void on_btnMessageDelete_clicked();

    void on_btnMessageHide_clicked();

    void on_listUsers_itemSelectionChanged();

signals:
    void mainWindowClosed();

protected:
    void closeEvent(QCloseEvent *event) override
    {
        emit mainWindowClosed();
        QMainWindow::closeEvent(event);
    }

public:
    Ui::MainWindow *ui;
    MainThread *mainThread = nullptr;

private:
    UsersContainer *_users{};
    MessagesContainer *_messages{};
    Console console{nullptr};
    void userActions(const QString &&method, bool deleteItem = false);
    void messageActions(const QString &&method, bool deleteItem = false);
    QMutex mutex;
};
#endif // MAINWINDOW_H
