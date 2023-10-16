#include <QApplication>
#include <QDebug>
#include <QTranslator>
#include "mainthread.h"
#include "mainwindow.h"

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
    MainThread th(&w);
    th.start();

    return a.exec();
}
