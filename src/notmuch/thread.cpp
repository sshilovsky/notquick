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
}

Thread::~Thread()
{
    dispose();
}

Thread::Thread(notmuch_thread_t *libnotmuch_thread, QObject *parent)
    :QObject(parent),
      libnotmuch_thread(libnotmuch_thread)
{

}

QString Thread::subject() const
{
    return QString(notmuch_thread_get_subject(libnotmuch_thread));
}

QString Thread::authors() const
{
    return QString(notmuch_thread_get_authors(libnotmuch_thread));
}

QDateTime Thread::datetime() const
{
    return QDateTime(QDate(2014,12,31), QTime(20,10));
}

Tags *Thread::tags()
{
    notmuch_tags_t* libnotmuch_tags = notmuch_thread_get_tags(libnotmuch_thread);
    Tags* tags = new Tags(libnotmuch_tags, this);
    return tags;
}

} // namespace notmuch
