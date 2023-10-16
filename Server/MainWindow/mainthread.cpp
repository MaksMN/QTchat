#include "mainthread.h"

MainThread::MainThread(MainWindow *_mainWindow, QObject *parent)
    : QThread(parent)
    , mainWindow(_mainWindow)
{}

void MainThread::run()
{
    ConsoleWrite("✅ MainThread Start");
    db.initialize();
    auto test = db.getUserByLogin("admin");
    auto test2 = db.getUserByID(1);
    auto test3 = db.getUsers("f", 0, 100);
    ConsoleWrite("✅ DB Initialized End");
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
