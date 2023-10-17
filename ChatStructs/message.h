#ifndef MESSAGE_H
#define MESSAGE_H
#include <QObject>
#include "ChatStructs_global.h"
#include "flags.h"
#include "user.h"

namespace chat {
namespace msg {

enum status {
    hidden = 1,   // сообщение скрыто
    public_ = 2,  // публичное сообщение
    private_ = 4, // личное сообщение
    // complain = 8, // жалоба
    author_deleted = 16,
    message_delivered = 32,
    message_read = 64
};

} // namespace msg
class CHATSTRUCTS_EXPORT Message
{
private:
    bool _init = false;
    qlonglong _id;
    qlonglong _author_id;
    std::shared_ptr<chat::User> _author = nullptr;
    qlonglong _recipient_id;
    std::shared_ptr<chat::User> _recipient = nullptr;
    QString _text;
    qlonglong _published;
    msg::status _status;
    Flags<msg::status> flags;

public:
    Message();

    /*!
     * \brief Создает публичное сообщение для добавления в базу данных
     */
    Message(qlonglong author_id, const QString &text, qlonglong published);
    /*!
     * \brief Создает публичное сообщение из базы данных
     */
    Message(bool init,
            qlonglong id,
            qlonglong author_id,
            const QString &text,
            qlonglong published,
            msg::status status);

    /*!
     * \brief Создает приватное сообщение для добавления в базу данных
     */
    Message(qlonglong author_id, qlonglong recipient_id, const QString &text, qlonglong published);
    /*!
     * \brief Создает приватное сообщение из базы данных.
     */
    Message(bool init,
            qlonglong id,
            qlonglong author_id,
            qlonglong recipient_id,
            const QString &text,
            qlonglong published,
            msg::status status);

    bool init() const;
    void setInit(bool newInit);
    qlonglong id() const;
    qlonglong author_id() const;
    qlonglong recipient_id() const;
    QString text() const;
    void setText(const QString &newText);
    qlonglong published() const;
    msg::status status() const;
    void setStatus(msg::status newStatus);

    bool isHidden();
    bool isPublic();
    bool isPrivate();
    bool isAuthorDeleted();
    bool isDelivered();
    bool isRead();
    void hide();
    void unhide();
    std::shared_ptr<chat::User> author() const;
    void setAuthor(std::shared_ptr<chat::User> newAuthor);
    std::shared_ptr<chat::User> recipient() const;
    void setRecipient(std::shared_ptr<chat::User> newRecipient);
};
} // namespace chat
#endif // MESSAGE_H
