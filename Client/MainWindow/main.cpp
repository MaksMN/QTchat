#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include "auth.h"
#include "client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    auto t = translator.load("qtChat_ru.qm", "translations/");
    if (t)
        a.installTranslator(&translator);

    Auth au;
    au.exec();
    if (au.authorized()) {
        MainWindow w;
        w.setUser(au.user);
        Client cl(&w);

        w.show();
        QObject::connect(&w, &MainWindow::mainWindowClosed, &cl, &Client::handleMainWindowClosed);
        cl.start();
        a.exec();
    }

    return 0;
}
