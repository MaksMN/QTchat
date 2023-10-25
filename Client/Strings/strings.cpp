#include "strings.h"

/*Strings*/
const QString Strings::MESSAGE_HAS_BEEN_SENT = QObject::tr("Message has been sent");
const QString Strings::FAILED_TO_SEND_MESSAGE = QObject::tr("Failed to send message");
const QString Strings::YOU_HAVE_TO_ENTER_THE_TEXT = QObject::tr("You have to enter the text");
const QString Strings::SESSION_TERMINATED_BY_SERVER = QObject::tr("The session is terminated by the server");
const QString Strings::FORBIDDEN_PERSONAL_MESSAGES_YOURSELF = QObject::tr("It is forbidden to have personal conversations with yourself");
const QString Strings::USER_BANNED = QObject::tr("User banned");
const QString Strings::INVALID_USERNAME_OR_PASSWORD = QObject::tr("Unsuccessful. Invalid username or password.");
const QString Strings::EMAIL_BUSY = QObject::tr("Email busy");
const QString Strings::LOGIN_BUSY = QObject::tr("Login busy");
const QString Strings::UNKNOWN_REASON = QObject::tr("Unknown reason");
const QString Strings::CONNECTION_TO_SERVER = QObject::tr("Connection to server...");
const QString Strings::UNKNOWN_ERROR = QObject::tr("Unknown error");
const QString Strings::NO_SERVER_RESPONSE = QObject::tr("No server response");
const QString Strings::ALL_FIELDS_MUST_BE_FILLED_IN = QObject::tr("All fields must be filled in");
const QString Strings::SERVER_USE_THE_SETTINGS = QObject::tr("The server will use the default settings");
const QString Strings::MESSAGE_NOT_SELECTED = QObject::tr("Message not selected");
const QString Strings::FAILED_TO_DISCONNECT_THE_USER = QObject::tr("Failed to disconnect the user");
const QString Strings::USER_SESSION_IS_DISABLED = QObject::tr("User session is disabled");
const QString Strings::BAN = QObject::tr("Ban");
const QString Strings::UNBAN = QObject::tr("Unban");
const QString Strings::NOT_APPLICABLE_FOR_SERVICE_USERS = QObject::tr("Not applicable for service users");
const QString Strings::CANNOT_DELETE_SERVICE_USERS = QObject::tr("Cannot delete service users");
const QString Strings::USER_NOT_SELECTED = QObject::tr("User not selected");
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
