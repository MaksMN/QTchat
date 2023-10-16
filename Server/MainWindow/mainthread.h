#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <QObject>
#include <QThread>
#include "app.h"
#include "db.h"
#include "mainwindow.h"

class MainThread : public QThread, APP
{
    Q_OBJECT
private:
    MainWindow *mainWindow;
    DB db{this};

public:
    explicit MainThread(MainWindow *_mainWindow, QObject *parent = nullptr);

    void run() override;

    void ConsoleWrite(const QString &line) override;
    void ConsoleWrite(const QString &&line) override;
};

#endif // MAINTHREAD_H
