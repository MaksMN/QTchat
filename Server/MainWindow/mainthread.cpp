#include "mainthread.h"

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
    timer.setInterval(1000); // Интервал в миллисекундах (1000 мс = 1 сек)
    timer.setSingleShot(false); // Установите в true, если нужен однократный запуск таймера

    QObject::connect(&timer, &QTimer::timeout, [&]() {
        if (!updated)
            timer.stop();
        qDebug("сработал таймер");
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

void MainThread::UpdateUsers(const QVector<std::shared_ptr<chat::User> > &users)
{
    QMetaObject::invokeMethod(mainWindow,
                              "updateUsers",
                              Qt::QueuedConnection,
                              Q_ARG(QVector<std::shared_ptr<chat::User> >, users));
}

void MainThread::Updater()
{
    auto users = db.getUsers();
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
