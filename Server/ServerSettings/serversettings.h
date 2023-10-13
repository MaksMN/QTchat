#ifndef SERVERSETTINGS_H
#define SERVERSETTINGS_H

#include <QDialog>
#include "SimpleIni.h"

namespace Ui {
class ServerSettings;
}

class ServerSettings : public QDialog
{
    Q_OBJECT
private:
    CSimpleIniA ini{};

public:
    explicit ServerSettings(QWidget *parent = nullptr);
    ~ServerSettings();

private slots:
    void on_sv_address_textEdited(const QString &arg1);

    void on_sv_port_valueChanged(int arg1);

    void on_db_address_textEdited(const QString &arg1);

    void on_db_port_valueChanged(int arg1);

    void on_db_user_textEdited(const QString &arg1);

    void on_db_pass_textEdited(const QString &arg1);

    void on_db_name_textEdited(const QString &arg1);

    void on_db_odbc_driver_textEdited(const QString &arg1);

    void on_db_charset_textEdited(const QString &arg1);

private:
    bool changes_allowed = false;
    Ui::ServerSettings *ui;
};

#endif // SERVERSETTINGS_H
