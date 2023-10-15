#include "db.h"
#include "SimpleIni.h"
#include "console.h"
#include "misc.h"
#include "strings.h"
DB::DB() {}

bool DB::dbExec(const QString &str_query, QSqlQuery &query)
{
    bool qresult = query.exec(str_query);
    if (!qresult) {
        setDBErrorCode(query.lastError().nativeErrorCode());
        setDBErrorMsg(query.lastError().text());
    }
    return qresult;
}

std::shared_ptr<chat::User> DB::getUserByLogin(const QString &login)
{
    QString query_str = "SELECT * FROM users WHERE login='" + login + "';";
    QSqlQuery query;
    if (!query.exec(query_str)) {
    }

    return nullptr;
}

std::shared_ptr<chat::User> DB::getUserByID(ullong &id)
{
    return nullptr;
}

QVector<std::shared_ptr<chat::User> > DB::getUsers(const QString &where, uint limit1, uint limit2)
{
    return QVector<std::shared_ptr<chat::User> >();
}

bool DB::saveUser(std::shared_ptr<chat::User>)
{
    return bool();
}

QString DB::getDBErrorMsg() const
{
    return db_error_message;
}

void DB::setDBErrorMsg(const QString &newDBErrorMsg)
{
    db_error_message = newDBErrorMsg;
}

QString DB::getDBErrorCode() const
{
    return db_error_code;
}

void DB::setDBErrorCode(const QString &newDBErrorCode)
{
    db_error_code = newDBErrorCode;
}

void DB::errorsClear()
{
    db_error_code = QString();
    db_error_message = QString();
}

void DB::printError(const QString &query_str)
{
    Console::writeLine("❌ " + Strings::t(Strings::DATABASE_ERROR));
    Console::writeLine("Error code: " + db.lastError().nativeErrorCode());
    Console::writeLine("Error message: " + db.lastError().text());
    if (!query_str.isEmpty()) {
        Console::writeLine("Query string: " + query_str);
    }
}

void DB::initialise()
{
    CSimpleIniA ini; // https://github.com/brofield/simpleini/tree/master
    SI_Error rc = ini.LoadFile("server.ini");
    if (rc < 0) {
        Misc::msgBox(Strings::SERVER_INI_NOTFOUND, Strings::DB_USE_DEFAULT_SETTINGS);
    } else {
        server = ini.GetValue("DB", "server", "127.0.0.1");
        port = ini.GetValue("DB", "port", "5432");
        dbuser = ini.GetValue("DB", "dbuser", "qt_chat");
        dbpass = ini.GetValue("DB", "dbpass", "qt_chat");
        dbname = ini.GetValue("DB", "dbname", "qt_chat");
        odbc_driver = ini.GetValue("DB", "odbc_driver", "PostgreSQL ANSI");
        db_character_set = ini.GetValue("DB", "odbc_driver", "UTF8");
    }

    QString connectString = QString::fromStdString("DRIVER=" + odbc_driver
                                                   + ";"
                                                     "SERVERNODE="
                                                   + server + ":" + port
                                                   + ";"
                                                     "UID=qt_chat"
                                                   + dbuser
                                                   + ";"
                                                     "PWD="
                                                   + dbpass
                                                   + ";"
                                                     "DATABASE="
                                                   + dbname
                                                   + ";"
                                                     "SCROLLABLERESULT=true");
    db.setDatabaseName(connectString);

    Console::writeLine(Strings::t(Strings::CONNECTING_TO_THE_DATABASE_SERVER));
    dbClose();
    if (db.open()) {
        Console::writeLine("✅ " + Strings::t(Strings::CONNECTION_TO_THE_DATABASE_WAS_SUCCESSFUL));
    } else {
        Console::writeLine("❌ " + Strings::t(Strings::FAILED_CONNECTION_TO_THE_DATABASE));
        Console::writeLine("Error code: " + db.lastError().nativeErrorCode());
        Console::writeLine("Error message: " + db.lastError().text());
    }
}

void DB::dbClose()
{
    if (db.isOpen())
        db.close();
}
