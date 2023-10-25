#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QTranslator>
#include "auth.h"
#include "client.h"
#include "strings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    auto t = translator.load("qtChat_ru.qm", "translations/");
    if (t)
        a.installTranslator(&translator);
    bool closeApp = true;
    QString authMsg;

    do {
        closeApp = true;
        Auth au;
        au.setLabelMsgText(authMsg);
        au.exec();
        if (au.authorized()) {
            MainWindow w(closeApp);
            w.setUser(au.user);
            Client cl(&w);

            w.show();
            QObject::connect(&w,
                             &MainWindow::mainWindowClosed,
                             &cl,
                             &Client::handleMainWindowClosed);

            cl.start();
            a.exec();
            if (!closeApp) {
                authMsg = Strings::t(Strings::SESSION_TERMINATED_BY_SERVER);
            } else {
                authMsg.clear();
            }
        }
    } while (!closeApp);

    return 0;
}
