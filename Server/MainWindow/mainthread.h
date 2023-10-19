#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <QObject>
#include <QThread>
#include "app.h"
#include "db.h"
#include "mainwindow.h"
#include <memory>

class MainThread : public QThread, APP
{
    Q_OBJECT
private:
    MainWindow *mainWindow;
    DB db{this};
    bool updated = true;
signals:
    void mainWindowClosed();
public slots:
    void handleMainWindowClosed();

public:
    explicit MainThread(MainWindow *_mainWindow, QObject *parent = nullptr);

    void run() override;
    void ConsoleWrite(const QString &line) override;
    void ConsoleWrite(const QString &&line) override;

    void Updater();
};

#endif // MAINTHREAD_H
