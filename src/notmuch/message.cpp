#include "message.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "log.h"
#include "mime/fileentity.h"

namespace notmuch {

QString Message::header(QString name) const
{
    if(!libnotmuch_message)
        return QString();
    return QString(notmuch_message_get_header(libnotmuch_message, name.toLocal8Bit().data())).simplified();
}

bool Message::dropTag(QString name)
{
    if(!libnotmuch_message) {
        // TODO qdebug
        return false;
    }
    ON_NOTMUCH_ERROR(notmuch_message_remove_tag(libnotmuch_message, name.toLocal8Bit().data())) {
        LOG_NOTMUCH_ERROR("notmuch_message_remove_tag");
        return false;
    }
    // TODO optionally drop tag from the thread
    return true;
}

QObject *Message::createMimeEntity() const
{
    return new mime::FileEntity(filename(), 0);
}

QString Message::filename() const
{
    if(!libnotmuch_message)
        return QString();
    return QString(notmuch_message_get_filename(libnotmuch_message));
}

QDateTime Message::date() const
{
    QDateTime datetime;
    if(libnotmuch_message)
        datetime.setTime_t(notmuch_message_get_date(libnotmuch_message));
    return datetime;
}

QString Message::id() const
{
    if(!libnotmuch_message)
        return QString();
    return QString(notmuch_message_get_message_id(libnotmuch_message));
}

Tags *Message::tags()
{
    if(!m_tags) {
        if(!libnotmuch_message)
            return 0;
        notmuch_tags_t* libnotmuch_tags = notmuch_message_get_tags(libnotmuch_message);
        m_tags = new Tags(libnotmuch_tags, this);
        // m_tags.loadAll()
    }
    return m_tags;
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
      libnotmuch_message(libnotmuch_message),
      m_tags(0)
{
}

} // namespace notmuch
