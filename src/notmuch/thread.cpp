#include "src/notmuch/thread.h"
#include "tags.h"

namespace notmuch {

Thread::Thread(QObject *parent) :
    Thread(0, parent)
{
}

void Thread::dispose()
{
    dispose_children(this);
    if(libnotmuch_thread) {
        notmuch_thread_destroy(libnotmuch_thread);
        libnotmuch_thread = 0;
    }
    if(dispose_libnotmuch_query) {
        notmuch_query_destroy(dispose_libnotmuch_query);
        dispose_libnotmuch_query = 0;
    }
}

Thread::~Thread()
{
    dispose();
}

Thread::Thread(notmuch_thread_t *libnotmuch_thread, QObject *parent)
    :QObject(parent),
      libnotmuch_thread(libnotmuch_thread),
      dispose_libnotmuch_query(0),
      m_messages(0)
{

}

QString Thread::subject() const
{
    if(!libnotmuch_thread)
        return QString();
    return QString(notmuch_thread_get_subject(libnotmuch_thread));
}

QString Thread::authors() const
{
    if(!libnotmuch_thread)
        return QString();
    return QString(notmuch_thread_get_authors(libnotmuch_thread));
}

QDateTime Thread::datetime() const
{
    if(!libnotmuch_thread)
        return QDateTime();
    return QDateTime(QDate(2014,12,31), QTime(20,10));
}

Tags *Thread::tags()
{
    if(!libnotmuch_thread)
        return 0;
    notmuch_tags_t* libnotmuch_tags = notmuch_thread_get_tags(libnotmuch_thread);
    Tags* tags = new Tags(libnotmuch_tags, this);
    // tags.loadAll()
    return tags;
}

Messages *Thread::messages()
{
    if(!libnotmuch_thread)
        return 0;
    if(!m_messages) {
        notmuch_messages_t* libnotmuch_messages = notmuch_thread_get_messages(libnotmuch_thread);
        m_messages = new Messages(libnotmuch_messages, this);
        m_messages->loadAll();
    }
    return m_messages;
}

} // namespace notmuch
