#ifndef NOTMUCH_DATABASE_H
#define NOTMUCH_DATABASE_H

#include <QObject>
#include <notmuch.h>
#include "notmuch/threads.h"
#include "disposable.h"

namespace notmuch {

class Database : public QObject, protected Disposable
{
    Q_OBJECT
    Q_INTERFACES(Disposable)
public:
    explicit Database(QObject *parent = 0);
    virtual ~Database();

    virtual bool open(QString path = QString(), bool readonly = false);
    virtual bool openReadonly(QString path = QString());
    virtual void dispose();

    Q_INVOKABLE QObject *queryThreads(QString query_string = "*");
    Q_INVOKABLE QObject *findThread(QString thread_id);

signals:

public slots:

private:
    notmuch_database_t* libnotmuch_database;
};

class DatabaseProxy : public QObject {
    Q_OBJECT
public:
    DatabaseProxy(Database* database);
    Q_INVOKABLE QObject *queryThreads(QString query_string = "*");
    Q_INVOKABLE QObject *findThread(QString thread_id);
private:
    Database* database;
};

} // namespace notmuch

#endif // NOTMUCH_DATABASE_H
