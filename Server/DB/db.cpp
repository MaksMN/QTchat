#include "db.h"
#include "SimpleIni.h"
#include "misc.h"
#include "strings.h"

DB::DB(APP *_app)
    : app(_app)
{}

DB::~DB() {}

bool DB::dbExec(QSqlQuery &query)
{
    bool qresult = query.exec();
    if (!qresult) {
        printQueryError(query);
    }
    return qresult;
}

std::shared_ptr<chat::User> DB::getUserByLogin(const QString &login)
{
    QSqlQuery query(db);

    bool qp = query.prepare("SELECT * FROM users WHERE login = :login");
    if (qp) {
        query.bindValue(":login", login);
    } else {
        app->ConsoleWrite("❌ Filed query.prepare(\"SELECT * FROM users WHERE login = :login\");");
        app->ConsoleWrite("❌ :login = " + login);
        return nullptr;
    }

    if (!dbExec(query))
        return nullptr;
    if (query.numRowsAffected() > 0) {
        query.next();
        return getUser(query);
    }

    return std::shared_ptr<chat::User>();
}

std::shared_ptr<chat::User> DB::getUserByID(qulonglong &id)
{
    QSqlQuery query(db);

    bool qp = query.prepare("SELECT * FROM users WHERE id = :id");
    if (qp) {
        query.bindValue(":id", id);
    } else {
        app->ConsoleWrite("❌ Filed query.prepare(\"SELECT * FROM users WHERE login = :login\");");
        app->ConsoleWrite("❌ :id = " + QString::number(id));
        return nullptr;
    }

    if (!dbExec(query))
        return nullptr;
    if (query.numRowsAffected() > 0) {
        query.next();
        return getUser(query);
    }

    return std::shared_ptr<chat::User>();
}

std::shared_ptr<chat::User> DB::getUserByID(qulonglong &&id)
{
    return getUserByID(id);
}

QVector<std::shared_ptr<chat::User>> DB::getUsers(const QString &keyword, uint offset, uint limit)
{
    //SELECT * FROM users WHERE first_name = 'aaa' offset 0 limit 100;
    QString query_str = "SELECT * FROM users";
    if (!keyword.isEmpty())
        query_str += " WHERE "
                     "login ILIKE :pattern OR "
                     "first_name ILIKE :pattern OR "
                     "last_name ILIKE :pattern";
    if (offset > 0)
        query_str += " OFFSET :offset" + QString::number(offset);

    query_str += " LIMIT :limit";

    QSqlQuery query(db);

    bool qp = query.prepare(query_str);
    if (qp) {
        query.bindValue(":pattern", "%" + keyword + "%");
        query.bindValue(":offset", offset);
        query.bindValue(":limit", limit);
    } else {
        app->ConsoleWrite("❌ Filed query.prepare " + query.executedQuery());
        return QVector<std::shared_ptr<chat::User>>();
    }
    app->ConsoleWrite(query.executedQuery());
    if (!dbExec(query))
        return QVector<std::shared_ptr<chat::User>>();
    auto users = QVector<std::shared_ptr<chat::User>>();
    if (query.numRowsAffected() > 0) {
        while (query.next()) {
            auto user = getUser(query);
            users.push_back(user);
        }
    }
    return users;
}

bool DB::saveUser(std::shared_ptr<chat::User>)
{
    return bool();
}

void DB::printDBError()
{
    app->ConsoleWrite("❌ " + Strings::t(Strings::DATABASE_ERROR));
    app->ConsoleWrite("Error code: " + db.lastError().nativeErrorCode());
    app->ConsoleWrite("Error message: " + db.lastError().text());
}

void DB::printQueryError(const QSqlQuery &query)
{
    app->ConsoleWrite("❌ " + Strings::t(Strings::DATABASE_QUERY_ERROR));
    app->ConsoleWrite("Error code: " + query.lastError().nativeErrorCode());
    app->ConsoleWrite("Error message: " + query.lastError().text());
    app->ConsoleWrite("Query string: " + query.lastQuery());
}

void DB::initialize()
{
    CSimpleIniA ini; // https://github.com/brofield/simpleini/tree/master
    SI_Error rc = ini.LoadFile("server.ini");
    if (rc < 0) {
        app->ConsoleWrite(Strings::t(Strings::SERVER_INI_NOTFOUND));
        app->ConsoleWrite(Strings::t(Strings::DB_USE_DEFAULT_SETTINGS));
    } else {
        server = ini.GetValue("DB", "server", "127.0.0.1");
        port = ini.GetValue("DB", "port", "5432");
        dbuser = ini.GetValue("DB", "dbuser", "qt_chat");
        dbpass = ini.GetValue("DB", "dbpass", "qt_chat");
        dbname = ini.GetValue("DB", "dbname", "qt_chat");
        odbc_driver = ini.GetValue("DB", "odbc_driver", "PostgreSQL ANSI");
        db_character_set = ini.GetValue("DB", "db_character_set", "UTF8");
    }

    QString connectString = "DRIVER=" + odbc_driver + ";CHARSET=" + db_character_set
                            + ";SERVER=" + server + ";PORT=" + port + ";UID=" + dbuser
                            + ";PWD=" + dbpass + ";DATABASE=" + dbname + ";SCROLLABLERESULT=true";
    db.setDatabaseName(connectString);

    app->ConsoleWrite((Strings::t(Strings::CONNECTING_TO_THE_DATABASE_SERVER)));

    if (db.open()) {
        app->ConsoleWrite(("✅ " + Strings::t(Strings::CONNECTION_TO_THE_DATABASE_WAS_SUCCESSFUL)));
    } else {
        app->ConsoleWrite(("❌ " + Strings::t(Strings::FAILED_CONNECTION_TO_THE_DATABASE)));
        app->ConsoleWrite(("Error code: " + db.lastError().nativeErrorCode()));
        app->ConsoleWrite(("Error message: " + db.lastError().text()));
    }
}

void DB::dbClose()
{
    if (db.isOpen())
        db.close();
}

std::shared_ptr<chat::User> DB::getUser(const QSqlQuery &query)
{
    bool init = true;
    qulonglong id = query.value("id").toULongLong();
    QString login = query.value("login").toString();
    QString email = query.value("email").toString();
    QString first_name = query.value("first_name").toString();
    QString last_name = query.value("last_name").toString();
    qulonglong registered = query.value("registered").toULongLong();
    chat::user::status status = (chat::user::status) query.value("status").toUInt();
    qulonglong session_key = query.value("session_key").toULongLong();
    QString hash = query.value("hash").toString();
    QString salt = query.value("salt").toString();

    auto user = std::make_shared<chat::User>(
        init, id, login, email, first_name, last_name, registered, status, session_key, hash, salt);

    return user;
}
