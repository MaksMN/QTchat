#ifndef DB_H
#define DB_H

#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QtSql>
#include "app.h"
#include "user.h"
#include <memory>
typedef unsigned int uint;
typedef unsigned long long ullong;

class DB
{
private:
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    QString server = "127.0.0.1";
    QString port = "5432";
    QString dbuser = "qt_chat";
    QString dbpass = "qt_chat";
    QString dbname = "qt_chat";
    QString odbc_driver = "PostgreSQL ANSI";
    QString db_character_set = "utf8";
    APP *app;

public:
    explicit DB(APP *app = nullptr);
    ~DB();

    bool dbExec(QSqlQuery &query);

    std::shared_ptr<chat::User> getUserByLogin(const QString &login);
    std::shared_ptr<chat::User> getUserByID(qulonglong &id);
    std::shared_ptr<chat::User> getUserByID(qulonglong &&id);
    QVector<std::shared_ptr<chat::User>> getUsers(const QString &keyword = QString(),
                                                  uint offset = 0,
                                                  uint limit = 100);
    bool createUser(std::shared_ptr<chat::User> user, bool &login_busy, bool &email_busy);

    qulonglong count(const QString &table,
                     const QString &column = QString(),
                     QVariant value = NULL,
                     bool t = false);

    void printDBError();
    void printQueryError(const QSqlQuery &query);
    void initialize();
    void dbClose();

private:
    std::shared_ptr<chat::User> getUser(const QSqlQuery &query);
};

#endif // DB_H
