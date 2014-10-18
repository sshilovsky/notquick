#include "threads.h"
#include "thread.h"
#include "log.h"

namespace notmuch {

Threads::Threads(QObject *parent)
    : Threads(0, parent)
{
}

int Threads::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return threads.size();
}

QVariant Threads::data(const QModelIndex &index, int role) const
{
    return QVariant::fromValue(threads[index.row()]);
}

QHash<int, QByteArray> Threads::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[0] = "thread";
    return roles;
}

Threads::~Threads()
{
    dispose();
}

void Threads::dispose()
{
    dispose_children(this);
    if(libnotmuch_threads) {
        notmuch_threads_destroy(libnotmuch_threads);
        libnotmuch_threads = 0;
    }
    if(dispose_libnotmuch_query) {
        notmuch_query_destroy(dispose_libnotmuch_query);
        dispose_libnotmuch_query = 0;
    }
}

void Threads::loadAll()
{
    // TODO beginInsert, notifications etc
    // TODO loadMore()
    if(!libnotmuch_threads)
        return;
    while(notmuch_threads_valid(libnotmuch_threads)) {
        notmuch_thread_t* libnotmuch_thread = notmuch_threads_get(libnotmuch_threads);
        if(!libnotmuch_thread) {
            LOG_NOTMUCH_INSUFFICIENT_MEMORY("notmuch_threads_get");
            return;
        }
        notmuch_threads_move_to_next(libnotmuch_threads);

        threads.append(new Thread(libnotmuch_thread, (QAbstractListModel*)this));
    }

}

Threads::Threads(notmuch_threads_t *libnotmuch_threads, QObject *parent)
    : QAbstractListModel(parent),
      libnotmuch_threads(libnotmuch_threads),
      dispose_libnotmuch_query(0)
{
}


} // namespace notmuch
