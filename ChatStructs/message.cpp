#include "message.h"

chat::Message::Message() {}

namespace chat {

std::shared_ptr<chat::User> Message::recipient() const
{
    return _recipient;
}

void Message::setRecipient(std::shared_ptr<chat::User> newRecipient)
{
    _recipient = newRecipient;
}

QString Message::pubDateTime()
{
    return Misc::stampTotime(_published);
}

std::shared_ptr<chat::User> Message::author() const
{
    return _author;
}

void Message::setAuthor(std::shared_ptr<chat::User> newAuthor)
{
    _author = newAuthor;
}

bool Message::init() const
{
    return _init;
}

void Message::setInit(bool newInit)
{
    _init = newInit;
}

qlonglong Message::id() const
{
    return _id;
}

qlonglong Message::author_id() const
{
    return _author_id;
}

qlonglong Message::recipient_id() const
{
    return _recipient_id;
}

QString Message::text()
{
    if (isHidden()) {
        return "Message is hidden";
    }
    return _text;
}

QString Message::real_text()
{
    return _text;
}

void Message::setText(const QString &newText)
{
    _text = newText;
}

qlonglong Message::published() const
{
    return _published;
}

msg::status Message::status() const
{
    return _status;
}

void Message::setStatus(msg::status newStatus)
{
    _status = newStatus;
}

bool Message::isHidden()
{
    return flags.hasFlag(_status, msg::status::hidden);
}

bool Message::isPublic()
{
    return flags.hasFlag(_status, msg::status::public_);
}

bool Message::isPrivate()
{
    return flags.hasFlag(_status, msg::status::private_);
}

bool Message::isAuthorDeleted()
{
    return flags.hasFlag(_status, msg::status::author_deleted);
}

bool Message::isDelivered()
{
    return flags.hasFlag(_status, msg::status::message_delivered);
}

bool Message::isRead()
{
    return flags.hasFlag(_status, msg::status::message_read);
}

void Message::hide()
{
    _status = flags.addFlag(_status, msg::status::hidden);
}

void Message::unhide()
{
    _status = flags.removeFlag(_status, msg::status::hidden);
}

Message::Message(qlonglong author_id, const QString &text, qlonglong published)
    : _author_id(std::move(author_id))
    , _text(text)
    , _published(std::move(published))
    , _status(msg::status::public_)
{
    if (published == 0) {
        _published = QDateTime::currentSecsSinceEpoch();
    }
}

Message::Message(bool init,
                 qlonglong id,
                 qlonglong author_id,
                 const QString &text,
                 qlonglong published,
                 msg::status status)
    : _init(init)
    , _id(std::move(id))
    , _author_id(std::move(author_id))
    , _text(text)
    , _published(std::move(published))
    , _status(status)
{
    if (published == 0) {
        _published = QDateTime::currentSecsSinceEpoch();
    }
}

Message::Message(qlonglong author_id,
                 qlonglong recipient_id,
                 const QString &text,
                 qlonglong published)
    : _author_id(std::move(author_id))
    , _recipient_id(std::move(recipient_id))
    , _text(text)
    , _published(std::move(published))
    , _status(msg::status::private_)
{
    if (published == 0) {
        _published = QDateTime::currentSecsSinceEpoch();
    }
}

Message::Message(bool init,
                 qlonglong id,
                 qlonglong author_id,
                 qlonglong recipient_id,
                 const QString &text,
                 qlonglong published,
                 msg::status status)
    : _init(init)
    , _id(std::move(id))
    , _author_id(std::move(author_id))
    , _recipient_id(std::move(recipient_id))
    , _text(text)
    , _published(std::move(published))
    , _status(status)
{
    if (published == 0) {
        _published = QDateTime::currentSecsSinceEpoch();
    }
}

} // namespace chat
