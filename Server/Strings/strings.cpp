#include "strings.h"

const QString Strings::SERVER_INI_NOTFOUND = QObject::tr("File server.ini not found");
const QString Strings::DB_USE_DEFAULT_SETTINGS = QObject::tr(
    "Default settings will be used to connect to the database");
const QString Strings::SETTINGS_CANNOT_BE_SAVED = QObject::tr("Settings cannot be saved");

const QString Strings::FAILED_TO_SAVE_SETTINGS_TO_INI_FILE = QObject::tr(
    "Не удалось сохранить настройки в ini файл");

QString Strings::t(const QString &s)
{
    return QCoreApplication::translate("QObject", s.toUtf8().constData());
}
