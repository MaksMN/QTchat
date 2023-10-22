#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <QMutex>
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
    QMutex mutex;
signals:
    void mainWindowClosed();
public slots:
    void handleMainWindowClosed();

    void deleteUserByID(qlonglong id);
    void banUserByID(qlonglong id);
    void unloginUserByID(qlonglong id);
    void deleteMessage(qlonglong id);
    void hideMessage(qlonglong id);

public:
    explicit MainThread(MainWindow *_mainWindow, QObject *parent = nullptr);

    void run() override;
    void ConsoleWrite(const QString &line) override;
    void ConsoleWrite(const QString &&line) override;
    void UpdateUsers(QVector<std::shared_ptr<chat::User>> users);
    void UpdateMessages(QVector<std::shared_ptr<chat::Message>> messages);

    void Updater();
};

#endif // MAINTHREAD_H
