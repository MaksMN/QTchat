#include "strings.h"

const QString Strings::SERVER_INI_NOTFOUND = QObject::tr("File server.ini not found");
const QString Strings::DB_USE_DEFAULT_SETTINGS = QObject::tr(
    "Default settings will be used to connect to the database");

QString Strings::t(const QString &s)
{
    return QCoreApplication::translate("QObject", s.toUtf8().constData());
}
