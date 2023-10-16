#include "strings.h"

/*Strings*/
const QString Strings::DATABASE_QUERY_ERROR = QObject::tr("Database query error");
const QString Strings::DATABASE_ERROR = QObject::tr("Database error");
const QString Strings::FAILED_CONNECTION_TO_THE_DATABASE = QObject::tr("Failed connection to the database");
const QString Strings::CONNECTION_TO_THE_DATABASE_WAS_SUCCESSFUL = QObject::tr("Connection to the database was successful");
const QString Strings::CONNECTING_TO_THE_DATABASE_SERVER = QObject::tr(
    "Connecting to the database server...");
const QString Strings::SETTINGS_SAVED_RESTART_THE_SERVER = QObject::tr(
    "Settings are saved, restart the server.");
const QString Strings::SERVER_INI_NOTFOUND = QObject::tr("File server.ini not found");
const QString Strings::DB_USE_DEFAULT_SETTINGS = QObject::tr(
    "Default settings will be used to connect to the database");
const QString Strings::SETTINGS_CANNOT_BE_SAVED = QObject::tr("Settings cannot be saved");
const QString Strings::FAILED_TO_SAVE_SETTINGS_TO_INI_FILE = QObject::tr(
    "Failed to save settings to ini file");
/********/

QString Strings::t(const QString &s)
{
    return QCoreApplication::translate("QObject", s.toUtf8().constData());
}
