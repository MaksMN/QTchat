#include <QApplication>
#include <QDebug>
#include <QTranslator>
#include "mainthread.h"
#include "mainwindow.h"
#include "server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    auto t = translator.load("qtChat_ru.qm", "translations/");
    if(t)
        a.installTranslator(&translator);

    MainWindow w;
    w.show();

    /*
     * Здесь запускается второй поток.
     * Он нужен для того чтобы не блокировать основной.
     */

    Server s;
    MainThread th(&w, &s);

    QObject::connect(&w, &MainWindow::mainWindowClosed, &th, &MainThread::handleMainWindowClosed);
    //QObject::connect(&w, &MainWindow::mainWindowClosed, &s, &Server::handleMainWindowClosed);
    th.start();
    s.start();

    return a.exec();
}
