#include "misc.h"
#include <QMessageBox>
#include "random"
#include "strings.h"
Misc::Misc()
{
    
}

ullong Misc::randomKey()
{
    std::random_device rd;
    std::mt19937_64 generator(rd());
    std::uniform_int_distribution<unsigned long long> distribution;
    return distribution(generator);
}
void Misc::msgBox(QString text, QString infText)
{
    QMessageBox messageBox;
    QIcon icon("app.ico");
    messageBox.setWindowIcon(icon);
    //messageBox.setWindowTitle();
    messageBox.setText(Strings::t(text));
    messageBox.setInformativeText(Strings::t(infText));
    messageBox.setIcon(QMessageBox::Information);
    messageBox.setDefaultButton(QMessageBox::Ok);
    messageBox.exec();
}

void Misc::iniWrite(const QString &&section,
                    const QString &&parameter,
                    const QString &value,
                    CSimpleIniA *ini,
                    std::string path)
{
    if (ini == nullptr) {
        msgBox(Strings::t(Strings::FAILED_TO_SAVE_SETTINGS_TO_INI_FILE), QString());
        return;
    }
    QByteArray section_b = section.toUtf8();
    const char *section_c = section_b.data();

    QByteArray parameter_b = parameter.toUtf8();
    const char *parameter_c = parameter_b.data();

    QByteArray value_b = value.toUtf8();
    const char *value_c = value_b.data();

    ini->SetValue(section_c, parameter_c, value_c);
    SI_Error rc = ini->SaveFile(path.data());
    if (rc < 0) {
        msgBox(Strings::t(Strings::FAILED_TO_SAVE_SETTINGS_TO_INI_FILE), QString());
    };
}

void Misc::iniWrite(
    const QString &section, const QString &parameter, int value, CSimpleIniA *ini, std::string path)
{
    if (ini == nullptr) {
        msgBox(Strings::t(Strings::FAILED_TO_SAVE_SETTINGS_TO_INI_FILE), QString());
        return;
    }
    QByteArray section_b = section.toUtf8();
    const char *section_c = section_b.data();

    QByteArray parameter_b = parameter.toUtf8();
    const char *parameter_c = parameter_b.data();

    QString value_s = QString::number(value);
    QByteArray value_b = value_s.toUtf8();
    const char *value_c = value_b.data();
    ini->SetValue(section_c, parameter_c, value_c);
    SI_Error rc = ini->SaveFile(path.data());
    if (rc < 0) {
        msgBox(Strings::t(Strings::FAILED_TO_SAVE_SETTINGS_TO_INI_FILE), QString());
    };
}
