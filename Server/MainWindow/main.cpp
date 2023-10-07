#include <QApplication>
#include <QTranslator>
#include "flags.h"
#include "mainwindow.h"
#include "user.h"

enum flgs {
    f1 = 1,
    f2 = 2,
    f3 = 4

};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QTranslator translator;
    auto t = translator.load("my_ru.qm", "translations/");
    if(t)
        a.installTranslator(&translator);
    chat::User u;
    u.ban();

    chat::Flags<flgs> f;
    auto ff = f.flagsReplace(flgs::f1, flgs::f2, flgs::f3);

    MainWindow w;
    w.show();    
    w.setWindowTitle("test");
    return a.exec();
}
