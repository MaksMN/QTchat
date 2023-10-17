#ifndef USER_H
#define USER_H
#include <QObject>
#include "ChatStructs_global.h"
#include "SHA1.h"
#include "flags.h"

#include <string>

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
    qlonglong _id = 0;
    QString _login;
    QString _email;
    QString _first_name;
    QString _last_name;
    qlonglong _registered = 0;
    user::status _status = user::status::common;
    qlonglong _session_key = 0;
    QString _pass_hash;
    QString _pass_salt;

    Flags<user::status> flags;
    SHA1 sha1;

public:
    User();

    /*!
     * \brief User Конструктор для использования на клиенте. Скрыты секретные данные.
     */
    User(qlonglong id,
         const QString &login,
         const QString &first_name,
         const QString &last_name,
         qlonglong registered,
         user::status status);

    /*!
     * \brief Конструктор создания нового пользователя для добавления в базу данных
     */
    User(const QString &login,
         const QString &email,
         const QString &first_name,
         const QString &last_name,
         qlonglong registered,
         user::status status,
         qlonglong session_key,
         const QString &pass_hash,
         const QString &pass_salt);

    /*!
     * \brief Конструктор для получения пользователя из базы данных
     */
    User(bool init,
         qlonglong id,
         const QString &login,
         const QString &email,
         const QString &first_name,
         const QString &last_name,
         qlonglong registered,
         user::status status,
         qlonglong session_key,
         const QString &pass_hash,
         const QString &pass_salt);

    qlonglong id();

    /*!
     * \brief Пользователь есть в базе данных
     * \return
     */
    bool init();

    QString login();
    void setLogin(const QString &login);

    QString email();
    void setEmail(const QString &email);

    QString first_name();
    void setFirstName(const QString &first_name);

    QString last_name();
    void setLastName(const QString &last_name);

    /*!
     * \brief Получить имя и фамилию.
     * \return
     */
    QString FullName();

    /*!
     * \brief создает новые соль и хеш пароля. 
     * Внимание! Пароль по ссылке уничтожается, его нельзя использовать повторно.
     */
    void setPass(QString &pass);

    /*!
     * \brief Проверяет пароль.
     * Внимание! Пароль по ссылке уничтожается, его нельзя использовать повторно.
     */
    bool validatePass(QString &pass);

    user::status status();
    void setStatus(user::status status);

    qlonglong registered();

    qlonglong session_key();
    void setSessionKey(const qlonglong &session_key);
    bool validateSessionKey(const qlonglong &session_key);

    void ban();
    void unban();
    bool isBanned();

    bool isAdmin();
    bool isServiceAdmin();
    void toAdmin();
    void toUser();

    QString getGroup();
    QString pass_hash() const;
    QString pass_salt() const;
};
} // namespace chat
#endif // USER_H
