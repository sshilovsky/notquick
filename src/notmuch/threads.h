#ifndef NOTMUCH_THREADS_H
#define NOTMUCH_THREADS_H

#include <QAbstractItemModel>
#include <QHash>
#include <QByteArray>
#include <notmuch.h>
#include "thread.h"
#include "disposable.h"

namespace notmuch {

class Threads : public QAbstractListModel, protected Disposable
{
    Q_OBJECT
    Q_INTERFACES(Disposable)
public:
    explicit Threads(QObject* parent = 0);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual QHash<int, QByteArray> roleNames() const;

    virtual ~Threads();

    void dispose();
signals:

public slots:
    void loadAll();

private:
    Threads(notmuch_threads_t* libnotmuch_threads, QObject* parent);

    notmuch_threads_t* libnotmuch_threads;
    notmuch_query_t* dispose_libnotmuch_query;
    QList<Thread*> threads;

    friend class Database;
};

} // namespace notmuch

#endif // NOTMUCH_THREADS_H
