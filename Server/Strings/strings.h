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
