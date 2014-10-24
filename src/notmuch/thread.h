#ifndef NOTMUCH_THREAD_H
#define NOTMUCH_THREAD_H

#include <QObject>
#include <QDateTime>
#include <notmuch.h>
#include "disposable.h"
#include "tags.h"
#include "messages.h"

namespace notmuch {

class Thread : public QObject, protected Disposable
{
    Q_OBJECT
    Q_INTERFACES(Disposable)
private:
    QString id() const;
    Messages *messages();
    QString authors() const;
    QString subject() const;
    QDateTime newestDate() const;
    Tags *tags();
public:
    explicit Thread(QObject *parent = 0);
    virtual void dispose();
    virtual ~Thread();

    Q_PROPERTY(QString id READ id CONSTANT)
    //Q_PROPERTY(int totalMessages READ totalMessages CONSTANT)
    Q_PROPERTY(QObject *messages READ messages CONSTANT)
    // Q_PROPERTY(QObject* toplevelMessages READ toplevelMessages CONSTANT)
    //Q_PROPERTY(int matchedMessages READ matchedMessages CONSTANT)
    Q_PROPERTY(QString authors READ authors CONSTANT)
    Q_PROPERTY(QString subject READ subject CONSTANT)
    //Q_PROPERTY(QDateTime oldestDate READ oldestDate CONSTANT)
    Q_PROPERTY(QDateTime newestDate READ newestDate CONSTANT) // TODO modifiable
    Q_PROPERTY(QObject *tags READ tags CONSTANT)


    Q_INVOKABLE bool dropTag(QString name);


private:
    Thread(notmuch_thread_t* libnotmuch_thread, QObject *parent);
    notmuch_thread_t* libnotmuch_thread;
    notmuch_query_t* dispose_libnotmuch_query;
    Messages *m_messages;
    Tags* m_tags;
    friend class Database;
    friend class Threads;
};

} // namespace notmuch

#endif // NOTMUCH_THREAD_H
