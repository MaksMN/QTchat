#ifndef DB_H
#define DB_H

#include <QMessageBox>
#include <QObject>
#include <QtSql>
#include "user.h"

typedef unsigned int uint;
typedef unsigned long long ullong;

class DB
{
private:
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    QString db_error_message;
    QString db_error_code;

    std::string server = "127.0.0.1";
    std::string port = "5432";
    std::string dbuser = "qt_chat";
    std::string dbpass = "qt_chat";
    std::string dbname = "qt_chat";
    std::string odbc_driver = "PostgreSQL ANSI";
    std::string db_character_set = "UTF8";
    uint db_errno = 0;

public:
    DB();
    ~DB() = default;

    bool dbExec(const QString &str_query, QSqlQuery &query);

    std::shared_ptr<chat::User> getUserByLogin(const QString &login);
    std::shared_ptr<chat::User> getUserByID(ullong &id);
    QVector<std::shared_ptr<chat::User>> getUsers(const QString &where,
                                                  uint limit1,
                                                  uint limit2 = 0);
    bool saveUser(std::shared_ptr<chat::User>);

    QString getDBErrorMsg() const;
    void setDBErrorMsg(const QString &newDBErrorMsg);
    QString getDBErrorCode() const;
    void setDBErrorCode(const QString &newDBErrorCode);
    void errorsClear();
    void printError(const QString &query_str = QString());
    void initialise();
    void dbClose();
};

#endif // DB_H
