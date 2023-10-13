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
    static const QString SERVER_INI_NOTFOUND;
    static const QString DB_USE_DEFAULT_SETTINGS;
    static const QString SETTINGS_CANNOT_BE_SAVED;
    static const QString FAILED_TO_SAVE_SETTINGS_TO_INI_FILE;
    static QString t(const QString &s);
};

#endif // STRINGS_H
