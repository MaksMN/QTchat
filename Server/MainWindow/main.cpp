#include <QApplication>
#include <QTranslator>

#include "mainwindow.h"
#include "misc.h"

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

    while (1) {
        auto v1 = Misc::randomKey();
        auto v2 = Misc::randomKey();
        auto v3 = Misc::randomKey();
        auto v4 = Misc::randomKey();
        auto v5 = Misc::randomKey();
        auto v6 = Misc::randomKey();
        auto v7 = Misc::randomKey();
        auto v8 = Misc::randomKey();
        auto v9 = Misc::randomKey();
    }
    MainWindow w;
    w.show();    
    w.setWindowTitle("test");
    return a.exec();
}
