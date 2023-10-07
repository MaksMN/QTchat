#ifndef MESSAGE_H
#define MESSAGE_H
#include <QObject>
#include "ChatStructs_global.h"
#include "flags.h"

typedef unsigned int uint;
typedef unsigned long long ullong;

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
    ullong _id;
    ullong _author_id;
    ullong _recipient_id;
    std::string _text;
    ullong _published;
    msg::status _status;
    Flags<msg::status> flags;

public:
    Message();

    /*!
     * \brief Создает публичное сообщение для добавления в базу данных
     */
    Message(ullong author_id, const std::string &text, ullong published);
    /*!
     * \brief Создает публичное сообщение из базы данных
     */
    Message(bool init,
            ullong id,
            ullong author_id,
            const std::string &text,
            ullong published,
            msg::status status);

    /*!
     * \brief Создает приватное сообщение для добавления в базу данных
     */
    Message(ullong author_id, ullong recipient_id, const std::string &text, ullong published);
    /*!
     * \brief Создает приватное сообщение из базы данных.
     */
    Message(bool init,
            ullong id,
            ullong author_id,
            ullong recipient_id,
            const std::string &text,
            ullong published,
            msg::status status);

    bool init() const;
    void setInit(bool newInit);
    ullong id() const;
    ullong author_id() const;
    ullong recipient_id() const;
    std::string text() const;
    void setText(const std::string &newText);
    ullong published() const;
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
};
} // namespace chat
#endif // MESSAGE_H
