#ifndef NOTMUCH_MESSAGE_H
#define NOTMUCH_MESSAGE_H

#include <QDateTime>
#include <QObject>
#include "disposable.h"
#include <notmuch.h>
#include "tags.h"

namespace notmuch {

class Message : public QObject, protected Disposable
{
    Q_OBJECT
    Q_INTERFACES(Disposable)
private:
    QString id() const;
    QString filename() const;
    QDateTime date() const;
    QString raw() const;
    Tags* tags();

public:
    explicit Message(QObject *parent = 0);
    virtual ~Message();
    virtual void dispose();

    Q_PROPERTY(QString id READ id CONSTANT)
    //Q_PROPERTY(QString threadId READ threadId CONSTANT)
    //Q_PROPERTY(QObject *thread READ thread CONSTANT)
    //Q_PROPERTY(QObject *replies READ replies CONSTANT)
    Q_PROPERTY(QString filename READ filename CONSTANT)
    //Q_PROPERTY(QStringList filenames READ filenames CONSTANT)
    // get_flag/set_flag
    Q_PROPERTY(QDateTime date READ date CONSTANT)
    Q_INVOKABLE QString header(QString name) const;
    /*Q_PROPERTY(QString subject READ subject CONSTANT)
    Q_PROPERTY(QString from READ from CONSTANT)*/
    Q_PROPERTY(QObject* tags READ tags CONSTANT)

    Q_PROPERTY(QString raw READ raw CONSTANT)

    Q_INVOKABLE bool dropTag(QString name);

private:
    Message(notmuch_message_t* libnotmuch_message, QObject* parent);
    notmuch_message_t* libnotmuch_message;
    Tags* m_tags;

    friend class Messages;
    friend class Thread;
};

} // namespace notmuch

#endif // NOTMUCH_MESSAGE_H
