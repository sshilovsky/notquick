#include "messages.h"
#include "log.h"
#include "message.h"

namespace notmuch {

Messages::Messages(QObject *parent) :
    Messages(0, parent)
{
}

void Messages::dispose()
{
    dispose_children(this);
    if(libnotmuch_messages) {
        notmuch_messages_destroy(libnotmuch_messages);
        libnotmuch_messages = 0;
    }
}

Messages::~Messages()
{
    dispose();
}

int Messages::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return messages.size();
}

QVariant Messages::data(const QModelIndex &index, int role) const
{
    return QVariant::fromValue(messages[index.row()]);
}

QHash<int, QByteArray> Messages::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[0] = "object";
    roles[1] = "message";
    return roles;
}

void Messages::loadAll()
{
    // TODO beginInsert, notifications etc
    // TODO loadMore()
    if(!libnotmuch_messages)
        return;
    while(notmuch_messages_valid(libnotmuch_messages)) {
        notmuch_message_t* libnotmuch_message = notmuch_messages_get(libnotmuch_messages);
        if(!libnotmuch_message) {
            LOG_NOTMUCH_INSUFFICIENT_MEMORY("notmuch_threads_get");
            return;
        }
        notmuch_messages_move_to_next(libnotmuch_messages);
        Message* message = new Message(libnotmuch_message, this);
        messages.append(message);

    }
}

Messages::Messages(notmuch_messages_t *libnotmuch_messages, QObject *parent)
    : QAbstractListModel(parent),
      libnotmuch_messages(libnotmuch_messages)
{
}

} // namespace notmuch
