#ifndef USER_H
#define USER_H
#include <QObject>
#include "ChatStructs_global.h"
#include "SHA1.h"
#include "flags.h"
#include "misc.h"
#include <string>

typedef unsigned int uint;
typedef unsigned long long ullong;

namespace chat {

namespace user{
enum status{
    common = 1,
    admin = 2,
    service_admin = 4,
    banned = 8,
};
}

class CHATSTRUCTS_EXPORT User
{
private:
    bool _init = false; // признак наличия пользователя в БД
    ullong _id = 0;
    std::string _login;
    std::string _email;
    std::string _first_name;
    std::string _last_name;
    std::string _pass_hash;
    std::string _pass_salt;
    user::status _status = user::status::common;
    ullong _registered = 0;
    ullong _session_key = 0;

    Flags<user::status> flags;
    SHA1 sha1;

public:
    User();

    /*!
     * \brief User Конструктор для использования на клиенте. Скрыты секретные данные.
     */
    User(ullong id,
         const std::string &login,
         const std::string &first_name,
         const std::string &last_name,
         user::status status);

    /*!
     * \brief Конструктор создания нового пользователя для добавления в базу данных
     */
    User(const std::string &login,
         const std::string &email,
         const std::string &first_name,
         const std::string &last_name,
         const std::string &pass_hash,
         const std::string &pass_salt,
         ullong registered,
         ullong session_key);

    /*!
     * \brief Конструктор для получения пользователя из базы данных
     */
    User(bool init,
         ullong id,
         const std::string &login,
         const std::string &email,
         const std::string &first_name,
         const std::string &last_name,
         const std::string &pass_hash,
         const std::string &pass_salt,
         ullong registered,
         ullong session_key);

    ullong id();

    /*!
     * \brief Пользователь есть в базе данных
     * \return
     */
    bool init();

    std::string login();
    void setLogin(const std::string &login);

    std::string email();
    void setEmail(const std::string &email);

    std::string first_name();
    void setFirstName(const std::string &first_name);

    std::string last_name();
    void setLastName(const std::string &last_name);

    /*!
     * \brief Получить имя и фамилию.
     * \return
     */
    std::string FullName();

    /*!
     * \brief создает новые соль и хеш пароля. 
     * Внимание! Пароль по ссылке уничтожается, его нельзя использовать повторно.
     */
    void setPass(std::string &pass);

    /*!
     * \brief Проверяет пароль.
     * Внимание! Пароль по ссылке уничтожается, его нельзя использовать повторно.
     */
    bool validatePass(std::string &pass);

    user::status status();
    void setStatus(user::status status);

    ullong registered();

    ullong session_key();
    void setSessionKey(const ullong &session_key);
    bool validateSessionKey(const ullong &session_key);

    void ban();
    void unban();
    bool isBanned();

    bool isAdmin();
    bool isServiceAdmin();
    void toAdmin();
    void toUser();

    QString getGroup();
};
} // namespace chat
#endif // USER_H
