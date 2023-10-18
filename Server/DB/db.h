#ifndef DB_H
#define DB_H

#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QtSql>
#include "app.h"
#include "message.h"
#include "user.h"
#include <memory>

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
    std::shared_ptr<chat::User> getUserByID(qlonglong &id);
    std::shared_ptr<chat::User> getUserByID(qlonglong &&id);
    QVector<std::shared_ptr<chat::User>> getUsers(const QString &keyword = QString(),
                                                  quint32 offset = 0,
                                                  quint32 limit = 100);
    /// Добавляет нового пользователя в БД
    bool createUser(std::shared_ptr<chat::User> user, bool &login_busy, bool &email_busy);
    /// Обновляет данные существующего пользователя в БД
    bool updateUser(std::shared_ptr<chat::User> user, bool &login_busy, bool &email_busy);

    QVector<std::shared_ptr<chat::Message>> getPubMessages(quint32 offset = 0, quint32 limit = 100);
    bool createMessage(std::shared_ptr<chat::Message> message);
    bool updateMessage(std::shared_ptr<chat::Message>);

    QVector<std::shared_ptr<chat::Message>> getPrivateMessages(qlonglong reader_id,
                                                               qlonglong interlocutor_id,
                                                               quint32 offset = 0,
                                                               quint32 limit = 100);

    /*!
     * получает количество записей в БД
     * \param table Таблица
     * \param column Колонка
     * \param value Значение колонки. 
     * \param comparison Сравнение:
     * " = " " != " - для целочисленных типов value;
     * " = " для строковых типов value будет преобразовано в LIKE;
     * " != " для строковых типов value будет преобразовано в NOT LIKE;      
     * \param t = true - добавит символ шаблона к строковой %value%
     * \return 
     */
    qlonglong count(const QString &table,
                    const QString &column = QString(),
                    QVariant value = NULL,
                    QString comparison = " = ",
                    bool t = false);

    void printDBError();
    void printQueryError(const QSqlQuery &query);
    void initialize();
    void dbClose();

private:
    std::shared_ptr<chat::User> getUser(const QSqlQuery &query);
    std::shared_ptr<chat::User> getUser(const QSqlQuery &query, int offset);
    std::shared_ptr<chat::Message> getMessage(const QSqlQuery &query);
};

#endif // DB_H
