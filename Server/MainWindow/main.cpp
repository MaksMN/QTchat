#include <QApplication>
#include <QTranslator>
#include "mainwindow.h"
#include "misc.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    auto t = translator.load("qtChat_ru.qm", "translations/");
    if(t)
        a.installTranslator(&translator);

    MainWindow w;
    w.show();
    return a.exec();
}
