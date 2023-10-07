#include "user.h"

chat::User::User() {}

ullong chat::User::getId()
{
    return _id;
}

bool chat::User::init()
{
    return _init;
}

std::string chat::User::login()
{
    return _login;
}

void chat::User::setLogin(const std::string &login)
{
    _login = login;
}

std::string chat::User::email()
{
    return _email;
}

void chat::User::setEmail(const std::string &email)
{
    _email = email;
}

std::string chat::User::first_name()
{
    return _first_name;
}

void chat::User::setFirstName(const std::string &first_name)
{
    _first_name = first_name;
}

std::string chat::User::last_name()
{
    return _last_name;
}

void chat::User::setLastName(const std::string &last_name)
{
    _last_name = last_name;
}

std::string chat::User::FullName()
{
    auto name = _last_name.empty() ? _first_name : _first_name + " " + _last_name;
    return name;
}

void chat::User::setPass(const std::string &pass) {}

bool chat::User::validatePass(const std::string &pass)
{
    return bool();
}

chat::user::status chat::User::status()
{
    return _status;
}

void chat::User::setStatus(user::status status)
{
    _status = status;
}

ullong chat::User::registered()
{
    return _registered;
}

ullong chat::User::session_key()
{
    return _session_key;
}

void chat::User::setSessionKey(const ullong &session_key)
{
    _session_key = session_key;
}

bool chat::User::validateSessionKey(const ullong &session_key)
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

namespace chat {
User::User(const std::string &login,
           const std::string &email,
           const std::string &first_name,
           const std::string &last_name,
           const std::string &pass_hash,
           const std::string &pass_salt,
           ullong registered,
           ullong session_key)
    : _login(login)
    , _email(email)
    , _first_name(first_name)
    , _last_name(last_name)
    , _pass_hash(pass_hash)
    , _pass_salt(pass_salt)
    , _registered(std::move(registered))
    , _session_key(std::move(session_key))
{}

User::User(bool init,
           ullong id,
           const std::string &login,
           const std::string &email,
           const std::string &first_name,
           const std::string &last_name,
           const std::string &pass_hash,
           const std::string &pass_salt,
           ullong registered,
           ullong session_key)
    : _init(init)
    , _id(std::move(id))
    , _login(login)
    , _email(email)
    , _first_name(first_name)
    , _last_name(last_name)
    , _pass_hash(pass_hash)
    , _pass_salt(pass_salt)
    , _registered(std::move(registered))
    , _session_key(std::move(session_key))
{}

} // namespace chat
