#include "db.h"
#include "SimpleIni.h"
#include "misc.h"
#include "strings.h"
DB::DB() {}

void DB::updateConfig()
{
    CSimpleIniA ini; // https://github.com/brofield/simpleini/tree/master
    SI_Error rc = ini.LoadFile("server.ini");
    if (rc < 0) {
        Misc::msgBox(Strings::SERVER_INI_NOTFOUND, Strings::DB_USE_DEFAULT_SETTINGS);
    } else {
        server = ini.GetValue("DB", "server", "127.0.0.1");
        port = ini.GetValue("DB", "port", "5432");
        dbuser = ini.GetValue("DB", "dbuser", "qt_chat");
        dbpass = ini.GetValue("DB", "dbpass", "qt_chat");
        dbname = ini.GetValue("DB", "dbname", "qt_chat");
        odbc_driver = ini.GetValue("DB", "odbc_driver", "PostgreSQL ANSI");
        db_character_set = ini.GetValue("DB", "odbc_driver", "UTF8");
    }
}
