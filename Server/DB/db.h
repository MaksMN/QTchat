#ifndef DB_H
#define DB_H

#include <QMessageBox>
#include <QObject>
#include "../strings/strings.h"
#include "SimpleIni.h"

typedef unsigned int uint;
typedef unsigned long long ullong;
const extern char config_file[];

class DB
{
protected:
    std::string server = "127.0.0.1";
    std::string port = "5432";
    std::string dbuser = "qt_chat";
    std::string dbpass = "qt_chat";
    std::string dbname = "qt_chat";
    std::string odbc_driver = "PostgreSQL ANSI";
    std::string db_character_set = "UTF8";
    uint db_errno = 0;

public:
    DB();

    virtual ~DB() = default;
};

#endif // DB_H
