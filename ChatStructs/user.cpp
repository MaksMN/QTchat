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
    _status = (user::status)(user::status::common | user::status::banned);
}

void chat::User::unban()
{
    _status = flags.removeFlag(_status, user::status::banned);
}

bool chat::User::isBanned()
{
    return flags.hasFlag(_status, user::status::banned);
}

bool chat::User::isAdmin()
{
    return flags.hasFlag(_status, user::status::admin);
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
    if (isAdmin())
        return "Admin";
    else
        return "User";
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
{}

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
{}

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
{}

} // namespace chat
