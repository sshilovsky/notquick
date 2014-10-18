#ifndef NOTMUCH_MESSAGE_H
#define NOTMUCH_MESSAGE_H

#include <QObject>
#include "disposable.h"
#include <notmuch.h>

namespace notmuch {

class Message : public QObject, protected Disposable
{
    Q_OBJECT
    Q_INTERFACES(Disposable)
private:
    QString subject() const;
public:
    explicit Message(QObject *parent = 0);
    virtual ~Message();
    virtual void dispose();

    Q_PROPERTY(QString subject READ subject CONSTANT)

private:
    Message(notmuch_message_t* libnotmuch_message, QObject* parent);
    notmuch_message_t* libnotmuch_message;

    friend class Messages;
};

} // namespace notmuch

#endif // NOTMUCH_MESSAGE_H
