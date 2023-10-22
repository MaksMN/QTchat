#include "mainthread.h"
#include <QDebug>
#include <QScrollBar>
#include "strings.h"

MainThread::MainThread(MainWindow *_mainWindow, QObject *parent)
    : QThread(parent)
    , mainWindow(_mainWindow)
{
    mainWindow->mainThread = this;
}

void MainThread::run()
{
    ConsoleWrite("✅MainThread Start");
    db.initialize();
    ConsoleWrite("✅DB Initialized");
    QTimer timer;
    timer.setInterval(2000); // Интервал в миллисекундах (1000 мс = 1 сек)
    timer.setSingleShot(false); // Установите в true, если нужен однократный запуск таймера

    QObject::connect(&timer, &QTimer::timeout, [&]() {
        if (!updated)
            timer.stop();        
        Updater();
    });

    timer.start();

    QEventLoop loop;
    loop.exec();
}

void MainThread::ConsoleWrite(const QString &line)
{
    QMetaObject::invokeMethod(mainWindow,
                              "consoleWrite",
                              Qt::QueuedConnection,
                              Q_ARG(QString, line));
}

void MainThread::ConsoleWrite(const QString &&line)
{
    ConsoleWrite(line);
}

void MainThread::UpdateUsers(QVector<std::shared_ptr<chat::User>> users)
{
    QMetaObject::invokeMethod(mainWindow,
                              "updateUsers",
                              Qt::QueuedConnection,
                              Q_ARG(QVector<std::shared_ptr<chat::User>>, users));
}

void MainThread::UpdateMessages(QVector<std::shared_ptr<chat::Message>> messages)
{
    QMetaObject::invokeMethod(mainWindow,
                              "updateMessages",
                              Qt::QueuedConnection,
                              Q_ARG(QVector<std::shared_ptr<chat::Message>>, messages));
}

void MainThread::Updater()
{
    int offset = mainWindow->getTopUserItem() + 1;
    auto users = db.getUsers(QString(), offset, 100);
    UpdateUsers(users);
    offset = mainWindow->getTopMessageItem();
    auto messages = db.getPubMessages(offset, 100);
    UpdateMessages(messages);
}
void MainThread::handleMainWindowClosed()
{
    qDebug("stop");
    updated = false;
    mainWindow->setVisible(false);
    this->quit();
    this->wait();
}

void MainThread::deleteUserByID(qlonglong id)
{
    db.deleteUserByID(id);
}

void MainThread::banUserByID(qlonglong id)
{
    auto user = db.getUserByID(id);
    if (!user)
        return;
    if (user->isBanned())
        user->unban();
    else
        user->ban();

    db.updateUser(user, "status", (int) user->status());
}

void MainThread::unloginUserByID(qlonglong id)
{
    auto user = db.getUserByID(id);
    if (!user)
        return;

    if (db.updateUser(user, "session_key", 0)) {
        ConsoleWrite(Strings::t(Strings::USER_SESSION_IS_DISABLED) + " (" + user->login() + ")");
    } else {
        ConsoleWrite(Strings::t(Strings::FAILED_TO_DISCONNECT_THE_USER) + " (" + user->login()
                     + ")");
    }
}

void MainThread::deleteMessage(qlonglong id)
{
    db.deleteItem(id);
}

void MainThread::hideMessage(qlonglong id)
{
    auto msg = db.getPubMessageByID(id);
    if (!msg)
        return;
    if (msg->isHidden())
        msg->unhide();
    else
        msg->hide();
    db.updateMessage(msg);
}
