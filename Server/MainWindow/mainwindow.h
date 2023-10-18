#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QEvent>
#include <QLabel>
#include <QMainWindow>
#include <QMutex>
#include <QTranslator>
#include "console.h"

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
    QString s = "test;";
    QString *s2 = &s;
    Ui::MainWindow *ui;

    Console console{nullptr};
    QMutex mutex;
};
#endif // MAINWINDOW_H
