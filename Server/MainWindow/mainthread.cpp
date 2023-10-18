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

void MainThread::Updater()
{
    qDebug("updater runing1");
    QThread::currentThread()->sleep(5);
    qDebug("updater runing2");
    QThread::currentThread()->sleep(5);
}
void MainThread::handleMainWindowClosed()
{
    qDebug("stop");
    updated = false;
    mainWindow->setVisible(false);
    this->quit();
    this->wait();
}
