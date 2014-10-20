#include "message.h"
#include <QFile>
#include <QTextStream>

namespace notmuch {

QString Message::subject() const
{
    // TODO drop extra whitespaces
    if(!libnotmuch_message)
        return QString();
    return QString(notmuch_message_get_header(libnotmuch_message, "subject"));
}

QString Message::from() const
{
    if(!libnotmuch_message)
        return QString();
    return QString(notmuch_message_get_header(libnotmuch_message, "from"));
}

QString Message::filename() const
{
    if(!libnotmuch_message)
        return QString();
    return QString(notmuch_message_get_filename(libnotmuch_message));
}

QString Message::raw() const
{
    QFile f(filename());
    if(!f.open(QFile::ReadOnly|QFile::Text)) {
        // TODO error message
    }
    QTextStream in(&f);
    return filename() + "\n\n" + in.readAll();
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
