#include "mainthread.h"
#include <QDebug>
#include <QScrollBar>
#include "ui_mainwindow.h"
MainThread::MainThread(MainWindow *_mainWindow, QObject *parent)
    : QThread(parent)
    , mainWindow(_mainWindow)
{}

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

void MainThread::Updater()
{
    //auto users_count = db.count("users");
    int offset = mainWindow->getTopUserItem();
    auto users = db.getUsers(QString(), offset, 100);
    UpdateUsers(users);
}
void MainThread::handleMainWindowClosed()
{
    qDebug("stop");
    updated = false;
    mainWindow->setVisible(false);
    this->quit();
    this->wait();
}
