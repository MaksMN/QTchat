#include "serversettings.h"
#include "SimpleIni.h"
#include "misc.h"
#include "strings.h"
#include "ui_serversettings.h"
#include <string>

ServerSettings::ServerSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerSettings)
{
    ui->setupUi(this);

    changes_allowed = false;
    SI_Error rc = ini.LoadFile("server.ini");
    if (rc < 0) {
        Misc::msgBox(Strings::SERVER_INI_NOTFOUND, Strings::SETTINGS_CANNOT_BE_SAVED);
    } else {
        ui->sv_address->setText(ini.GetValue("GENERAL", "sv_address", "127.0.0.1"));
        ui->sv_port->setValue(ini.GetLongValue("GENERAL", "sv_address", 7777));

        ui->db_address->setText(ini.GetValue("DB", "server", "127.0.0.1"));
        ui->db_port->setValue(ini.GetLongValue("DB", "port", 5432));
        ui->db_user->setText(ini.GetValue("DB", "dbuser", "qt_chat"));
        ui->db_pass->setText(ini.GetValue("DB", "dbpass", "qt_chat"));
        ui->db_name->setText(ini.GetValue("DB", "dbname", "qt_chat"));
        ui->db_odbc_driver->setText(ini.GetValue("DB", "odbc_driver", "PostgreSQL ANSI"));
        ui->db_charset->setText(ini.GetValue("DB", "db_character_set", "UTF8"));
    }
    changes_allowed = true;
}

ServerSettings::~ServerSettings()
{
    delete ui;
}

void ServerSettings::on_sv_address_textEdited(const QString &arg1)
{
    if (!changes_allowed)
        return;
    Misc::iniWrite("GENERAL", "sv_address", arg1, &ini);
}

void ServerSettings::on_sv_port_valueChanged(int arg1)
{
    if (!changes_allowed)
        return;
    Misc::iniWrite("GENERAL", "sv_port", arg1, &ini);
}

void ServerSettings::on_db_address_textEdited(const QString &arg1)
{
    Misc::iniWrite("DB", "server", arg1, &ini);
}

void ServerSettings::on_db_port_valueChanged(int arg1)
{
    Misc::iniWrite("DB", "port", arg1, &ini);
}

void ServerSettings::on_db_user_textEdited(const QString &arg1)
{
    Misc::iniWrite("DB", "dbuser", arg1, &ini);
}

void ServerSettings::on_db_pass_textEdited(const QString &arg1)
{
    Misc::iniWrite("DB", "dbpass", arg1, &ini);
}
void ServerSettings::on_db_name_textEdited(const QString &arg1)
{
    Misc::iniWrite("DB", "dbname", arg1, &ini);
}

void ServerSettings::on_db_odbc_driver_textEdited(const QString &arg1)
{
    Misc::iniWrite("DB", "odbc_driver", arg1, &ini);
}

void ServerSettings::on_db_charset_textEdited(const QString &arg1)
{
    Misc::iniWrite("DB", "db_character_set", arg1, &ini);
}
