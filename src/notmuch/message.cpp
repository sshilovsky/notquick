#include "message.h"

namespace notmuch {

QString Message::subject() const
{
    if(!libnotmuch_message)
        return QString();
    return QString(notmuch_message_get_header(libnotmuch_message, "subject"));
}

Message::Message(QObject *parent) :
    Message(0, parent)
{
}

Message::~Message()
{
    dispose();
}

void Message::dispose()
{
    dispose_children(this);
    if(libnotmuch_message) {
        notmuch_message_destroy(libnotmuch_message);
        libnotmuch_message = 0;
    }
}

Message::Message(notmuch_message_t *libnotmuch_message, QObject *parent)
    : QObject(parent),
      libnotmuch_message(libnotmuch_message)
{
}

} // namespace notmuch
