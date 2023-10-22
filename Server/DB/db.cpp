#include "db.h"
#include "SimpleIni.h"
#include "misc.h"
#include "strings.h"

DB::DB(APP *_app)
    : app(_app)
{}

DB::~DB() {}

bool DB::dbExec(QSqlQuery &query)
{
    bool qresult = query.exec();
    if (!qresult) {
        printQueryError(query);
    }
    return qresult;
}

std::shared_ptr<chat::User> DB::getUserByLogin(const QString &login)
{
    QSqlQuery query(db);

    bool qp = query.prepare("SELECT * FROM users WHERE login = :login");
    if (qp) {
        query.bindValue(":login", login);
    } else {
        app->ConsoleWrite("❌ Filed query.prepare(\"SELECT * FROM users WHERE login = :login\");");
        app->ConsoleWrite("❌ :login = " + login);
        return nullptr;
    }

    if (!dbExec(query))
        return nullptr;
    if (query.numRowsAffected() > 0) {
        query.next();
        return getUser(query);
    }

    return std::shared_ptr<chat::User>();
}

std::shared_ptr<chat::User> DB::getUserByID(qlonglong &id)
{
    QSqlQuery query(db);

    bool qp = query.prepare("SELECT * FROM users WHERE id = :id");
    if (qp) {
        query.bindValue(":id", id);
    } else {
        app->ConsoleWrite("❌ Filed query.prepare(\"SELECT * FROM users WHERE login = :login\");");
        app->ConsoleWrite("❌ :id = " + QString::number(id));
        return nullptr;
    }

    if (!dbExec(query))
        return nullptr;
    if (query.numRowsAffected() > 0) {
        query.next();
        return getUser(query);
    }

    return nullptr;
}

std::shared_ptr<chat::User> DB::getUserByID(qlonglong &&id)
{
    return getUserByID(id);
}

void DB::deleteUserByID(qlonglong &id)
{
    QSqlQuery query(db);
    if (id < 2) {
        return;
    }

    bool qp = query.prepare("DELETE FROM users WHERE id = :id");
    if (qp) {
        query.bindValue(":id", id);
    } else {
        app->ConsoleWrite("❌ Filed query.prepare(\"DELETE * FROM users WHERE login = :login\");");
        app->ConsoleWrite("❌ :id = " + QString::number(id));
    }

    dbExec(query);
}

QVector<std::shared_ptr<chat::User>> DB::getUsers(const QString &keyword,
                                                  quint32 offset,
                                                  quint32 limit)
{
    QString query_str = "SELECT * FROM users ";
    if (!keyword.isEmpty())
        query_str += "WHERE "
                     "login ILIKE :pattern OR "
                     "first_name ILIKE :pattern OR "
                     "last_name ILIKE :pattern "
                     "ORDER BY login ASC ";
    else
        query_str += "ORDER BY id ASC ";

    if (offset > 0)
        query_str += "OFFSET :offset ";

    query_str += "LIMIT :limit";

    QSqlQuery query(db);

    bool qp = query.prepare(query_str);
    if (qp) {
        query.bindValue(":pattern", "%" + keyword + "%");
        query.bindValue(":offset", offset);
        query.bindValue(":limit", limit);
    } else {
        app->ConsoleWrite("❌ Filed query.prepare " + query.executedQuery());
        return QVector<std::shared_ptr<chat::User>>();
    }
    //app->ConsoleWrite(query.executedQuery());
    if (!dbExec(query))
        return QVector<std::shared_ptr<chat::User>>();
    auto users = QVector<std::shared_ptr<chat::User>>();
    if (query.numRowsAffected() > 0) {
        while (query.next()) {
            auto user = getUser(query);
            users.push_back(user);
        }
    }
    return users;
}

bool DB::createUser(std::shared_ptr<chat::User> user, bool &login_busy, bool &email_busy)
{
    login_busy = count("users", "login", user->login()) > 0;
    email_busy = count("users", "email", user->email()) > 0;
    if (login_busy || email_busy)
        return false;
    QString query_str
        = "INSERT INTO users "
          "(login, email, first_name, last_name, registered, status, session_key, hash,salt) "
          "VALUES "
          "(:login, :email, :first_name, :last_name, :registered, :status, :session, :hash, :salt)";
    QSqlQuery query(db);
    bool qp = query.prepare(query_str);
    if (qp) {
        query.bindValue(":login", user->login());
        query.bindValue(":email", user->email());
        query.bindValue(":first_name", user->first_name());
        query.bindValue(":last_name", user->last_name());
        query.bindValue(":registered", user->registered());
        query.bindValue(":status", user->status());
        query.bindValue(":session", user->session_key());
        query.bindValue(":hash", user->pass_hash());
        query.bindValue(":salt", user->pass_salt());

    } else {
        app->ConsoleWrite("❌ Filed query.prepare " + query.executedQuery());
        return 0;
    }
    bool ex = dbExec(query);
    if (query.numRowsAffected() < 1) {
        login_busy = count("users", "login", user->login()) > 0;
        email_busy = count("users", "email", user->email()) > 0;
    }
    return ex;
}

bool DB::updateUser(std::shared_ptr<chat::User> user, bool &login_busy, bool &email_busy, bool force)
{
    login_busy = count("users", "login", user->login()) > 0;
    email_busy = count("users", "email", user->email()) > 0;
    if ((login_busy || email_busy) && !force)
        return false;
    QString query_str = "UPDATE users SET "
                        "login = :login, "
                        "email = :email, "
                        "first_name = :first_name, "
                        "last_name =:last_name, "
                        "status = :status, "
                        "session_key = :session_key, "
                        "hash = :hash, "
                        "salt = :salt "
                        "WHERE id = :id;";
    QSqlQuery query(db);
    bool qp = query.prepare(query_str);
    if (qp) {
        query.bindValue(":login", user->login());
        query.bindValue(":email", user->email());
        query.bindValue(":first_name", user->first_name());
        query.bindValue(":last_name", user->last_name());
        query.bindValue(":status", user->status());
        query.bindValue(":session", user->session_key());
        query.bindValue(":hash", user->pass_hash());
        query.bindValue(":salt", user->pass_salt());
        query.bindValue(":id", user->id());

    } else {
        app->ConsoleWrite("❌ Filed query.prepare " + query.executedQuery());
        return 0;
    }
    bool ex = dbExec(query);
    if (query.numRowsAffected() < 1) {
        login_busy = count("users", "login", user->login()) > 0;
        email_busy = count("users", "email", user->email()) > 0;
    }
    return ex;
}

bool DB::updateUser(std::shared_ptr<chat::User> user, QString parameter, QVariant value)
{
    QString query_str = "UPDATE users SET " + parameter
                        + " = :value "
                          "WHERE id = :id;";
    QSqlQuery query(db);
    bool qp = query.prepare(query_str);
    if (qp) {
        query.bindValue(":value", value);
        query.bindValue(":id", user->id());

    } else {
        app->ConsoleWrite("❌ Filed query.prepare " + query.executedQuery());
        return 0;
    }
    bool ex = dbExec(query);
    if (query.numRowsAffected() < 1) {
        return false;
    }
    return ex;
}

QVector<std::shared_ptr<chat::Message>> DB::getPubMessages(quint32 offset, quint32 limit)
{
    QString query_str = "SELECT * FROM pub_messages INNER JOIN users on "
                        "users.id = CASE WHEN pub_messages.author_id IS NULL THEN 0 ELSE "
                        "pub_messages.author_id END "
                        "ORDER BY pub_messages.published ASC";

    if (offset > 0)
        query_str += " OFFSET :offset" + QString::number(offset);

    query_str += " LIMIT :limit";

    QSqlQuery query(db);

    bool qp = query.prepare(query_str);
    if (qp) {
        query.bindValue(":offset", offset);
        query.bindValue(":limit", limit);
    } else {
        app->ConsoleWrite("❌ Filed query.prepare " + query.executedQuery());
        return QVector<std::shared_ptr<chat::Message>>();
    }
    //app->ConsoleWrite(query.executedQuery());
    if (!dbExec(query))
        return QVector<std::shared_ptr<chat::Message>>();
    auto messages = QVector<std::shared_ptr<chat::Message>>();
    if (query.numRowsAffected() > 0) {
        while (query.next()) {
            auto message = getMessage(query);
            messages.push_back(message);
        }
    }
    return messages;
}

std::shared_ptr<chat::Message> DB::getPubMessageByID(qlonglong id)
{
    QString query_str = "SELECT * FROM pub_messages INNER JOIN users on "
                        "users.id = CASE WHEN pub_messages.author_id IS NULL THEN 0 ELSE "
                        "pub_messages.author_id END "
                        " WHERE pub_messages.id = :id "
                        "ORDER BY pub_messages.published ASC";

    QSqlQuery query(db);

    bool qp = query.prepare(query_str);
    if (qp) {
        query.bindValue(":id", id);
    } else {
        app->ConsoleWrite("❌ Filed query.prepare " + query.executedQuery());
        return nullptr;
    }
    //app->ConsoleWrite(query.executedQuery());
    if (!dbExec(query))
        return nullptr;
    std::shared_ptr<chat::Message> message = nullptr;
    if (query.numRowsAffected() > 0) {
        while (query.next()) {
            message = getMessage(query);
        }
    }
    return message;
}

bool DB::createMessage(std::shared_ptr<chat::Message> message)
{
    QString query_str;
    if (message->isPublic())
        query_str = "INSERT INTO pub_messages (author_id, text, published, status) "
                    "VALUES (:author_id, :text, :published, :status)";
    else
        query_str
            = "INSERT INTO private_messages (author_id, recipient_id, text, published, status) "
              "VALUES (:author_id, :recipient_id, :text, :published, :status)";
    QSqlQuery query(db);
    bool qp = query.prepare(query_str);
    if (qp) {
        query.bindValue(":author_id", message->author_id());
        query.bindValue(":recipient_id", message->recipient_id());
        query.bindValue(":text", message->real_text());
        query.bindValue(":published", message->published());
        query.bindValue(":status", (int) message->status());
    } else {
        app->ConsoleWrite("❌ Filed query.prepare " + query.executedQuery());
        return 0;
    }
    bool ex = dbExec(query);
    if (query.numRowsAffected() < 1) {
        app->ConsoleWrite("❌ Filed query: " + query.executedQuery());
    }
    return ex;
}

bool DB::updateMessage(std::shared_ptr<chat::Message> message)
{
    QString query_str;

    if (message->isPublic())
        query_str = "UPDATE pub_messages SET "
                    "author_id = :author_id, "
                    "text = :text, "
                    "published = :published, "
                    "status =:status "
                    "WHERE id = :id";
    else
        query_str
            = "UPDATE private_messages SET author_id = :author_id, recipient_id = :recipient_id, "
              "text = :text, published = :published, status = :status WHERE id = :id";

    QSqlQuery query(db);
    bool qp = query.prepare(query_str);
    if (qp) {
        query.bindValue(":author_id", message->author_id());
        if (message->isPrivate())
            query.bindValue(":recipient_id", message->recipient_id());
        query.bindValue(":text", message->real_text());
        query.bindValue(":published", message->published());
        query.bindValue(":status", message->status());
        query.bindValue(":id", message->id());

    } else {
        app->ConsoleWrite("❌ Filed query.prepare " + query.executedQuery());
        return 0;
    }
    bool ex = dbExec(query);
    if (query.numRowsAffected() < 1) {
        app->ConsoleWrite("❌ Filed query: " + query.executedQuery());
    }
    return ex;
}

std::shared_ptr<chat::Message> DB::getMessageByID(qlonglong &id)
{
    return nullptr;
}

bool DB::deleteItem(qlonglong id, QString table)
{
    QSqlQuery query(db);

    bool qp = query.prepare("DELETE FROM " + table + " WHERE id = :id");
    if (qp) {
        query.bindValue(":id", id);
    } else {
        app->ConsoleWrite("❌ Filed query.prepare(\"DELETE * FROM users WHERE login = :login\");");
        app->ConsoleWrite("❌ :id = " + QString::number(id));
    }

    return dbExec(query);
}

QVector<std::shared_ptr<chat::Message>> DB::getPrivateMessages(qlonglong reader_id,
                                                               qlonglong interlocutor_id,
                                                               quint32 offset,
                                                               quint32 limit)
{
    QString query_str = "SELECT * FROM private_messages as pm "
                        "INNER JOIN users as u1 on "
                        "u1.id = CASE WHEN pm.author_id IS NULL THEN 0  ELSE pm.author_id END "
                        "INNER JOIN users as u2 on "
                        "u2.id = CASE WHEN pm.recipient_id IS NULL THEN 0 ELSE pm.recipient_id END "
                        "WHERE "
                        "(pm.author_id = :reader_id AND pm.recipient_id = :interlocutor_id) OR "
                        "(pm.author_id = :interlocutor_id AND pm.recipient_id = :reader_id) "
                        "ORDER BY pm.published ASC";

    if (offset > 0)
        query_str += " OFFSET :offset" + QString::number(offset);

    query_str += " LIMIT :limit";

    QSqlQuery query(db);

    bool qp = query.prepare(query_str);
    if (qp) {
        query.bindValue(":reader_id", reader_id);
        query.bindValue(":interlocutor_id", interlocutor_id);
        query.bindValue(":offset", offset);
        query.bindValue(":limit", limit);
    } else {
        app->ConsoleWrite("❌ Filed query.prepare " + query.executedQuery());
        return QVector<std::shared_ptr<chat::Message>>();
    }
    //app->ConsoleWrite(query.executedQuery());
    if (!dbExec(query))
        return QVector<std::shared_ptr<chat::Message>>();
    auto messages = QVector<std::shared_ptr<chat::Message>>();
    if (query.numRowsAffected() > 0) {
        while (query.next()) {
            auto message = getMessage(query);
            messages.push_back(message);
        }
    }
    return messages;
}

std::shared_ptr<chat::Message> DB::getPrivateMessageByID(qlonglong id)
{
    QString query_str = "SELECT * FROM private_messages as pm "
                        "INNER JOIN users as u1 on "
                        "u1.id = CASE WHEN pm.author_id IS NULL THEN 0  ELSE pm.author_id END "
                        "INNER JOIN users as u2 on "
                        "u2.id = CASE WHEN pm.recipient_id IS NULL THEN 0 ELSE pm.recipient_id END "
                        "WHERE "
                        "(pm.author_id = :reader_id AND pm.recipient_id = :interlocutor_id) OR "
                        "(pm.author_id = :interlocutor_id AND pm.recipient_id = :reader_id) "
                        "ORDER BY pm.published ASC WHERE pm.id = :id";

    QSqlQuery query(db);

    bool qp = query.prepare(query_str);
    if (qp) {
        query.bindValue(":id", id);

    } else {
        app->ConsoleWrite("❌ Filed query.prepare " + query.executedQuery());
        return nullptr;
    }
    //app->ConsoleWrite(query.executedQuery());
    if (!dbExec(query))
        return nullptr;
    std::shared_ptr<chat::Message> message = nullptr;
    if (query.numRowsAffected() > 0) {
        while (query.next()) {
            message = getMessage(query);
        }
    }
    return message;
}

qlonglong DB::count(
    const QString &table, const QString &column, QVariant value, QString comparison, bool t)
{
    QString query_str = "SELECT COUNT(*) FROM " + table;
    if (value != NULL) {
        if (!column.isEmpty())
            query_str += " WHERE " + column;

        if (value.userType() == QMetaType::UInt || value.userType() == QMetaType::ULongLong
            || value.userType() == QMetaType::Int)
            query_str += comparison + ":value";

        if (value.userType() == QMetaType::QString) {
            if (t)
                value = "%" + value.toString() + "%";
            if (comparison.trimmed() == "!=") {
                comparison = " NOT ";
            } else {
                comparison = " ";
            }
            query_str += comparison + "LIKE :value";
        }
    }
    QSqlQuery query(db);

    bool qp = query.prepare(query_str);
    if (qp) {
        query.bindValue(":value", value);
    } else {
        app->ConsoleWrite("❌ Filed query.prepare " + query.executedQuery());
        return 0;
    }
    //app->ConsoleWrite(query.executedQuery());
    if (!dbExec(query))
        return 0;

    query.next();
    return query.value(0).toULongLong();
}

void DB::printDBError()
{
    app->ConsoleWrite("❌ " + Strings::t(Strings::DATABASE_ERROR));
    app->ConsoleWrite("Error code: " + db.lastError().nativeErrorCode());
    app->ConsoleWrite("Error message: " + db.lastError().text());
}

void DB::printQueryError(const QSqlQuery &query)
{
    app->ConsoleWrite("❌ " + Strings::t(Strings::DATABASE_QUERY_ERROR));
    app->ConsoleWrite("Error code: " + query.lastError().nativeErrorCode());
    app->ConsoleWrite("Error message: " + query.lastError().text());
    app->ConsoleWrite("Query string: " + query.lastQuery());
}

void DB::initialize()
{
    CSimpleIniA ini; // https://github.com/brofield/simpleini/tree/master
    SI_Error rc = ini.LoadFile("server.ini");
    if (rc < 0) {
        app->ConsoleWrite(Strings::t(Strings::SERVER_INI_NOTFOUND));
        app->ConsoleWrite(Strings::t(Strings::DB_USE_DEFAULT_SETTINGS));
    } else {
        server = ini.GetValue("DB", "server", "127.0.0.1");
        port = ini.GetValue("DB", "port", "5432");
        dbuser = ini.GetValue("DB", "dbuser", "qt_chat");
        dbpass = ini.GetValue("DB", "dbpass", "qt_chat");
        dbname = ini.GetValue("DB", "dbname", "qt_chat");
        odbc_driver = ini.GetValue("DB", "odbc_driver", "PostgreSQL ANSI");
        db_character_set = ini.GetValue("DB", "db_character_set", "UTF8");
    }

    QString connectString = "DRIVER=" + odbc_driver + ";CHARSET=" + db_character_set
                            + ";SERVER=" + server + ";PORT=" + port + ";UID=" + dbuser
                            + ";PWD=" + dbpass + ";DATABASE=" + dbname + ";SCROLLABLERESULT=true";
    db.setDatabaseName(connectString);

    app->ConsoleWrite((Strings::t(Strings::CONNECTING_TO_THE_DATABASE_SERVER)));

    if (db.open()) {
        app->ConsoleWrite(("✅ " + Strings::t(Strings::CONNECTION_TO_THE_DATABASE_WAS_SUCCESSFUL)));
    } else {
        app->ConsoleWrite(("❌ " + Strings::t(Strings::FAILED_CONNECTION_TO_THE_DATABASE)));
        app->ConsoleWrite(("Error code: " + db.lastError().nativeErrorCode()));
        app->ConsoleWrite(("Error message: " + db.lastError().text()));
    }
}

void DB::dbClose()
{
    if (db.isOpen())
        db.close();
}

std::shared_ptr<chat::User> DB::getUser(const QSqlQuery &query)
{
    bool init = true;
    qlonglong id = query.value("id").toLongLong();
    QString login = query.value("login").toString();
    QString email = query.value("email").toString();
    QString first_name = query.value("first_name").toString();
    QString last_name = query.value("last_name").toString();
    qlonglong registered = query.value("registered").toULongLong();
    chat::user::status status = (chat::user::status) query.value("status").toUInt();
    qlonglong session_key = query.value("session_key").toULongLong();
    QString hash = query.value("hash").toString();
    QString salt = query.value("salt").toString();

    auto user = std::make_shared<chat::User>(
        init, id, login, email, first_name, last_name, registered, status, session_key, hash, salt);

    return user;
}

std::shared_ptr<chat::User> DB::getUser(const QSqlQuery &query, int offset)
{
    bool init = true;
    qlonglong id = query.value(offset).toLongLong();
    QString login = query.value(++offset).toString();
    QString email = query.value(++offset).toString();
    QString first_name = query.value(++offset).toString();
    QString last_name = query.value(++offset).toString();
    qlonglong registered = query.value(++offset).toULongLong();
    chat::user::status status = (chat::user::status) query.value(++offset).toUInt();
    qlonglong session_key = query.value(++offset).toULongLong();
    QString hash = query.value(++offset).toString();
    QString salt = query.value(++offset).toString();

    auto user = std::make_shared<chat::User>(
        init, id, login, email, first_name, last_name, registered, status, session_key, hash, salt);

    return user;
}

std::shared_ptr<chat::Message> DB::getMessage(const QSqlQuery &query)
{
    QString fieldName = "id";
    int msg_index = query.record().indexOf(fieldName);
    int author_id_index = -1;
    int recipient_id_index = -1;

    for (int i = msg_index + 1; i < query.record().count(); i++) {
        if (author_id_index == -1 && query.record().fieldName(i) == fieldName) {
            author_id_index = i;
            continue;
        }
        if (author_id_index > msg_index && query.record().fieldName(i) == fieldName) {
            recipient_id_index = i;
            break;
        }
    }

    bool init = true;
    qlonglong id = query.value("id").toLongLong();
    qlonglong author_id = query.value("author_id").toLongLong();

    qlonglong recipient_id = recipient_id_index > author_id_index
                                 ? query.value("recipient_id").toLongLong()
                                 : 0;
    QString text = query.value("text").toString();
    qlonglong published = query.value("published").toLongLong();
    chat::msg::status status = (chat::msg::status) query.value("status").toUInt();

    auto message = std::make_shared<chat::Message>(init,
                                                   id,
                                                   author_id,
                                                   recipient_id,
                                                   text,
                                                   published,
                                                   status);
    auto author = getUser(query, author_id_index);
    message->setAuthor(author);
    if (recipient_id_index > author_id_index) {
        auto recipient = getUser(query, recipient_id_index);
        message->setRecipient(recipient);
    }
    return message;
}
