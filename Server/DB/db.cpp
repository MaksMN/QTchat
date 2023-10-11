#include "db.h"
#include "../strings/strings.h"
#include "SimpleIni.h"
DB::DB()
{
    CSimpleIniA ini; // https://github.com/brofield/simpleini/tree/master
    SI_Error rc = ini.LoadFile("server.ini");
    if (rc < 0) {
        QMessageBox msgBox;
        QIcon icon("app.ico");
        msgBox.setWindowIcon(icon);
        msgBox.setText(Strings::t(Strings::SERVER_INI_NOTFOUND));
        msgBox.setInformativeText(Strings::t(Strings::DB_USE_DEFAULT_SETTINGS));
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
}
