#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "commands.h"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    std::shared_ptr<chat::User> current_user = nullptr;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Commands command = not_registered;
    int topUserItem = 0;
    int topMessageItem = 0;
    bool AuthPage();
    void setUser(std::shared_ptr<chat::User> &_user);

    /// Индекс элемента вверху окна списка
    int getTopUserItem();
    int getTopMessageItem();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<chat::User> user = nullptr;

signals:
    void mainWindowClosed();

protected:
    void closeEvent(QCloseEvent *event) override
    {
        emit mainWindowClosed();
        QMainWindow::closeEvent(event);
    }
};

#endif // MAINWINDOW_H
