#ifndef NOTMUCH_MESSAGE_H
#define NOTMUCH_MESSAGE_H

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
    QString subject() const;
    QString from() const;
    QString filename() const;
    QString raw() const;
    QString id() const;
    Tags* tags();

public:
    explicit Message(QObject *parent = 0);
    virtual ~Message();
    virtual void dispose();

    Q_PROPERTY(QString subject READ subject CONSTANT)
    Q_PROPERTY(QString from READ from CONSTANT)
    Q_PROPERTY(QString filename READ filename CONSTANT)
    Q_PROPERTY(QString raw READ raw CONSTANT)
    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QObject* tags READ tags CONSTANT)

    Q_INVOKABLE QString header(QString name) const;

private:
    Message(notmuch_message_t* libnotmuch_message, QObject* parent);
    notmuch_message_t* libnotmuch_message;
    Tags* m_tags;

    friend class Messages;
};

} // namespace notmuch

#endif // NOTMUCH_MESSAGE_H
