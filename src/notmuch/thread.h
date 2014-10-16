#ifndef NOTMUCH_THREAD_H
#define NOTMUCH_THREAD_H

#include <QObject>
#include <QDateTime>
#include <notmuch.h>
#include "disposable.h"
#include "tags.h"

namespace notmuch {

class Thread : public QObject, protected Disposable
{
    Q_OBJECT
    Q_INTERFACES(Disposable)
private:
    QString subject() const;
    QString authors() const;
    QDateTime datetime() const;
    Tags* tags();
public:
    explicit Thread(QObject *parent = 0);
    virtual void dispose();
    virtual ~Thread();

    Q_PROPERTY(QString subject READ subject CONSTANT)
    Q_PROPERTY(QString authors READ authors CONSTANT)
    Q_PROPERTY(QDateTime datetime READ datetime CONSTANT)
    Q_PROPERTY(QObject* tags READ tags CONSTANT)


signals:

public slots:

private:
    Thread(notmuch_thread_t* libnotmuch_thread, QObject *parent);
    notmuch_thread_t* libnotmuch_thread;
    friend class Threads;
};

} // namespace notmuch

#endif // NOTMUCH_THREAD_H
