#include "message.h"

chat::Message::Message() {}

namespace chat {
bool Message::init() const
{
    return _init;
}

void Message::setInit(bool newInit)
{
    _init = newInit;
}

ullong Message::id() const
{
    return _id;
}

ullong Message::author_id() const
{
    return _author_id;
}

ullong Message::recipient_id() const
{
    return _recipient_id;
}

std::string Message::text() const
{
    return _text;
}

void Message::setText(const std::string &newText)
{
    _text = newText;
}

ullong Message::published() const
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
    flags.addFlag(_status, msg::status::hidden);
}

void Message::unhide()
{
    flags.removeFlag(_status, msg::status::hidden);
}

Message::Message(ullong author_id, const std::string &text, ullong published)
    : _author_id(std::move(author_id))
    , _text(text)
    , _published(std::move(published))
    , _status(msg::status::public_)
{}

Message::Message(bool init,
                 ullong id,
                 ullong author_id,
                 const std::string &text,
                 ullong published,
                 msg::status status)
    : _init(init)
    , _id(std::move(id))
    , _author_id(std::move(author_id))
    , _text(text)
    , _published(std::move(published))
    , _status(status)
{}

Message::Message(ullong author_id, ullong recipient_id, const std::string &text, ullong published)
    : _author_id(std::move(author_id))
    , _recipient_id(std::move(recipient_id))
    , _text(text)
    , _published(std::move(published))
    , _status(msg::status::private_)
{}

Message::Message(bool init,
                 ullong id,
                 ullong author_id,
                 ullong recipient_id,
                 const std::string &text,
                 ullong published,
                 msg::status status)
    : _init(init)
    , _id(std::move(id))
    , _author_id(std::move(author_id))
    , _recipient_id(std::move(recipient_id))
    , _text(text)
    , _published(std::move(published))
    , _status(status)
{}

} // namespace chat
