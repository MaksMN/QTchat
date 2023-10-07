#include <QApplication>
#include <QTranslator>
#include "../DB/db.h"
#include "mainwindow.h"
const char config_file[]{"server.ini"};

class TranslationManager
{
public:
    static QString getTranslatedString(const QString &key)
    {
        return QCoreApplication::translate("TranslationManager", key.toUtf8().constData());
    }

    static QString staticString() { return getTranslatedString("Hello, World!"); }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    auto t = translator.load("qtChat_ru.qm", "translations/");
    if(t)
        a.installTranslator(&translator);
    DB db;

    MainWindow w;
    w.show();    
    return a.exec();
}
