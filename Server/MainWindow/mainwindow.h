#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QEvent>
#include <QLabel>
#include <QMainWindow>
#include <QMutex>
#include <QTranslator>
#include "console.h"
#include "user.h"
#include "userscontainer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void consoleWrite(QString line);
    void updateUsers(const QVector<std::shared_ptr<chat::User>> &users);
private slots:
    void on_actionShut_Down_triggered();
    void on_actionServer_Settings_triggered();
signals:
    void mainWindowClosed();

protected:
    void closeEvent(QCloseEvent *event) override
    {
        emit mainWindowClosed();
        QMainWindow::closeEvent(event);
    }

private:
    Ui::MainWindow *ui;
    UsersContainer *_users{};
    Console console{nullptr};
    QMutex mutex;
};
#endif // MAINWINDOW_H
