#ifndef STRINGS_H
#define STRINGS_H
#include <QApplication>
#include <QObject>
#include <QString>
#include <QTranslator>

/*!
 * \brief Класс для хранения строковых переменных. Для них работает перевод.
 */
class Strings : public QObject
{
private:
public:
    /*Strings*/
	static const QString MESSAGE_HAS_BEEN_SENT;
	static const QString FAILED_TO_SEND_MESSAGE;
	static const QString YOU_HAVE_TO_ENTER_THE_TEXT;
	static const QString SESSION_TERMINATED_BY_SERVER;
	static const QString FORBIDDEN_PERSONAL_MESSAGES_YOURSELF;
	static const QString USER_BANNED;
	static const QString INVALID_USERNAME_OR_PASSWORD;
	static const QString EMAIL_BUSY;
	static const QString LOGIN_BUSY;
	static const QString UNKNOWN_REASON;
    static const QString CONNECTION_TO_SERVER;
    static const QString UNKNOWN_ERROR;
    static const QString NO_SERVER_RESPONSE;
	static const QString ALL_FIELDS_MUST_BE_FILLED_IN;
	static const QString SERVER_USE_THE_SETTINGS;
	static const QString MESSAGE_NOT_SELECTED;
	static const QString FAILED_TO_DISCONNECT_THE_USER;
	static const QString USER_SESSION_IS_DISABLED;
	static const QString BAN;
	static const QString UNBAN;
	static const QString NOT_APPLICABLE_FOR_SERVICE_USERS;
	static const QString CANNOT_DELETE_SERVICE_USERS;
	static const QString USER_NOT_SELECTED;
	static const QString DATABASE_QUERY_ERROR;
	static const QString DATABASE_ERROR;
	static const QString FAILED_CONNECTION_TO_THE_DATABASE;
	static const QString CONNECTION_TO_THE_DATABASE_WAS_SUCCESSFUL;	
    static const QString THE_TEST_TEXT;
    static const QString CONNECTING_TO_THE_DATABASE_SERVER;
    static const QString SETTINGS_SAVED_RESTART_THE_SERVER;
    static const QString SERVER_INI_NOTFOUND;
    static const QString DB_USE_DEFAULT_SETTINGS;
    static const QString SETTINGS_CANNOT_BE_SAVED;
    static const QString FAILED_TO_SAVE_SETTINGS_TO_INI_FILE;
    /********/
    static QString t(const QString &s);
};

#endif // STRINGS_H
