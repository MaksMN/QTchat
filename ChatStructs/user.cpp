#include "user.h"

#include "misc.h"
chat::User::User() {}

qlonglong chat::User::id()
{
    return _id;
}

bool chat::User::init()
{
    return _init;
}

QString chat::User::login()
{
    return _login;
}

void chat::User::setLogin(const QString &login)
{
    _login = login;
}

QString chat::User::email()
{
    return _email;
}

void chat::User::setEmail(const QString &email)
{
    _email = email;
}

QString chat::User::first_name()
{
    return _first_name;
}

void chat::User::setFirstName(const QString &first_name)
{
    _first_name = first_name;
}

QString chat::User::last_name()
{
    return _last_name;
}

void chat::User::setLastName(const QString &last_name)
{
    _last_name = last_name;
}

QString chat::User::FullName()
{
    auto name = _last_name.isEmpty() ? _first_name : _first_name + " " + _last_name;
    return name;
}

void chat::User::setPass(QString &pass)
{
    _pass_salt = sha1.hash(QString::number(Misc::randomKey()));
    _pass_hash = sha1.hash(pass + _pass_salt);
    // уничтожение пароля
    for (int i = 0; i < pass.size(); ++i) {
        pass.data()[i] = '\0';
    }
}

bool chat::User::validatePass(QString &pass)
{
    if (_pass_hash.isEmpty())
        return false;
    QString pass_hash = sha1.hash(pass + _pass_salt);
    // уничтожение пароля
    for (int i{0}; i < pass.size(); i++)
        pass.data()[i] = '\0';
    return pass_hash == _pass_hash;
}

chat::user::status chat::User::status()
{
    return _status;
}

void chat::User::setStatus(user::status status)
{
    _status = status;
}

qlonglong chat::User::registered()
{
    return _registered;
}

qlonglong chat::User::session_key()
{
    return _session_key;
}

void chat::User::setSessionKey(const qlonglong &session_key)
{
    _session_key = session_key;
}

bool chat::User::validateSessionKey(const qlonglong &session_key)
{
    if (_session_key == 0)
        return false;
    return _session_key == session_key;
}

void chat::User::ban()
{
    if (isServiceAdmin())
        return;
    _status = static_cast<user::status>(user::banned | user::common);
}

void chat::User::unban()
{
    _status = flags.removeFlag(_status, user::banned);
}

bool chat::User::isBanned()
{
    return flags.hasFlag(_status, user::status::banned);
}

bool chat::User::isAdmin()
{
    return flags.hasFlag(_status, user::status::admin)
           || flags.hasFlag(_status, user::status::service_admin);
}

bool chat::User::isServiceAdmin()
{
    return flags.hasFlag(_status, user::status::service_admin);
}

void chat::User::toAdmin()
{
    if (isServiceAdmin())
        return;
    _status = flags.flagsReplace(_status,
                                 user::status::admin,
                                 (user::status)(user::status::common | user::status::banned));
}

void chat::User::toUser()
{
    if (isServiceAdmin())
        return;
    _status = flags.flagsReplace(_status, user::status::common, user::status::admin);
}

QString chat::User::getGroup()
{
    QString group;
    if (isAdmin())
        group += "Admin";
    else
        group += "User";

    if (isBanned())
        group += "banned";
    return group;
}

namespace chat {

QString User::pass_hash() const
{
    return _pass_hash;
}

QString User::pass_salt() const
{
    return _pass_salt;
}

QString User::regDateTime()
{
    return Misc::stampTotime(_registered);
}

QJsonObject User::serialiseJson() const
{
    QJsonObject jsonObject;
    jsonObject["id"] = _id;
    jsonObject["login"] = _login;
    jsonObject["email"] = _email;
    jsonObject["first_name"] = _first_name;
    jsonObject["last_name"] = _last_name;
    jsonObject["registered"] = _registered;
    jsonObject["status"] = (int) _status;
    jsonObject["session_key"] = _session_key;
    jsonObject["pass_hash"] = _pass_hash;
    jsonObject["pass_salt"] = _pass_salt;
    return jsonObject;
}

void User::deserialiseJson(const QJsonObject &jsonObject)
{
    _id = jsonObject["id"].toInteger(0);
    _login = jsonObject["login"].toString();
    _email = jsonObject["email"].toString();
    _first_name = jsonObject["first_name"].toString();
    _last_name = jsonObject["last_name"].toString();
    _registered = jsonObject["registered"].toInteger();
    _status = (user::status) jsonObject["status"].toInt();
    _session_key = jsonObject["session_key"].toInteger();
    _pass_hash = jsonObject["pass_hash"].toString();
    _pass_salt = jsonObject["pass_salt"].toString();
}

User::User(const QString &login,
           const QString &email,
           const QString &first_name,
           const QString &last_name,
           qlonglong registered,
           user::status status,
           qlonglong session_key,
           const QString &pass_hash,
           const QString &pass_salt)
    : _login(login)
    , _email(email)
    , _first_name(first_name)
    , _last_name(last_name)
    , _registered(std::move(registered))
    , _status(status)
    , _session_key(std::move(session_key))
    , _pass_hash(pass_hash)
    , _pass_salt(pass_salt)
{
    if (registered == 0) {
        _registered = QDateTime::currentSecsSinceEpoch();
    }
}

User::User(qlonglong id,
           const QString &login,
           const QString &first_name,
           const QString &last_name,
           qlonglong registered,
           user::status status)
    : _id(std::move(id))
    , _login(login)
    , _first_name(first_name)
    , _last_name(last_name)
    , _registered(std::move(registered))
    , _status(status)
{
    if (registered == 0) {
        _registered = QDateTime::currentSecsSinceEpoch();
    }
}

User::User(bool init,
           qlonglong id,
           const QString &login,
           const QString &email,
           const QString &first_name,
           const QString &last_name,
           qlonglong registered,
           user::status status,
           qlonglong session_key,
           const QString &pass_hash,
           const QString &pass_salt)
    : _init(init)
    , _id(std::move(id))
    , _login(login)
    , _email(email)
    , _first_name(first_name)
    , _last_name(last_name)
    , _registered(std::move(registered))
    , _status(status)
    , _session_key(std::move(session_key))
    , _pass_hash(pass_hash)
    , _pass_salt(pass_salt)
{
    if (registered == 0) {
        _registered = QDateTime::currentSecsSinceEpoch();
    }
}

} // namespace chat
