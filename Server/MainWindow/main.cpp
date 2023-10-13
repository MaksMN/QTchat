#include <QApplication>
#include <QTranslator>
#include <QtSql>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    auto t = translator.load("qtChat_ru.qm", "translations/");
    if(t)
        a.installTranslator(&translator);
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    QString connectString = QStringLiteral("DRIVER=PostgreSQL Unicode;"
                                           "SERVERNODE=127.0.0.1:5432;"
                                           "UID=qt_chat;"
                                           "PWD=qt_chat;"
                                           "DATABASE=qt_chat;"
                                           "SCROLLABLERESULT=true");
    db.setDatabaseName(connectString);

    if (db.open()) {
        // Выполнение запроса
        QSqlQuery query;
        query.exec("SELECT * FROM users");

        // Обработка результатов запроса
        while (query.next()) {
            // Получение значений колонок
            QString column1 = query.value(0).toString();
            QString column2 = query.value(4).toString();

            // Дальнейшая обработка данных...
        }

        // Закрытие соединения с базой данных
        db.close();
    } else {
        // Обработка ошибок подключения к базе данных
        QString error = db.lastError().text();
    }
    MainWindow w;
    w.show();

    return a.exec();
}
