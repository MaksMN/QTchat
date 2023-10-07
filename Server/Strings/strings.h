#ifndef STRINGS_H
#define STRINGS_H
#include <QApplication>
#include <QObject>
#include <QString>
#include <QTranslator>

class Strings : public QObject
{
private:
public:
    static const QString SERVER_INI_NOTFOUND;
    static const QString DB_USE_DEFAULT_SETTINGS;
    static QString t(const QString &s);
};

#endif // STRINGS_H
