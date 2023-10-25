#include "misc.h"
#include <QDateTime>
#include <QLocale>
#include <QMessageBox>
#include "random"
Misc::Misc()
{
    
}

qlonglong Misc::randomKey()
{
    std::random_device rd;
    std::mt19937_64 generator(rd());
    std::uniform_int_distribution<long long> distribution;
    return distribution(generator);
}

bool Misc::iniWrite(const QString &section,
                    const QString &parameter,
                    const QString &value,
                    CSimpleIniA *ini,
                    const QString &path)
{
    if (ini == nullptr) {
        return false;
    }

    ini->SetValue(section.toStdString().data(),
                  parameter.toStdString().data(),
                  value.toStdString().data());
    SI_Error rc = ini->SaveFile(path.toStdString().data());
    if (rc < 0) {
        return false;
    };
    return true;
}

bool Misc::iniWrite(const QString &section,
                    const QString &parameter,
                    int value,
                    CSimpleIniA *ini,
                    const QString &path)
{
    if (ini == nullptr) {
        return false;
    }

    ini->SetValue(section.toStdString().data(),
                  parameter.toStdString().data(),
                  QString::number(value).toStdString().data());
    SI_Error rc = ini->SaveFile(path.toStdString().data());
    if (rc < 0) {
        return false;
    };
    return true;
}

QString Misc::stampTotime(qlonglong timestamp)
{
    QLocale systemLocale = QLocale::system();
    QString dateFormat = systemLocale.dateFormat(QLocale::ShortFormat);
    QString timeFormat = systemLocale.timeFormat(QLocale::ShortFormat);

    QDateTime dateTime;
    dateTime.setSecsSinceEpoch(timestamp);

    QString dateString = dateTime.toString(dateFormat);
    QString timeString = dateTime.toString(timeFormat);

    return dateString + " " + timeString;
}
