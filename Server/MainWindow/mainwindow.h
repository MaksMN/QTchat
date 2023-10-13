#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QEvent>
#include <QLabel>
#include <QMainWindow>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{

    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionShut_Down_triggered();

    void on_actionServer_Settings_triggered();

private:
    QString s = "test;";
    QString *s2 = &s;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
