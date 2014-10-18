#ifndef NOTMUCH_MESSAGES_H
#define NOTMUCH_MESSAGES_H

#include <QAbstractListModel>
#include "disposable.h"
#include <notmuch.h>

namespace notmuch {

class Message;

class Messages : public QAbstractListModel, protected Disposable
{
    Q_OBJECT
    Q_INTERFACES(Disposable)
public:
    explicit Messages(QObject *parent = 0);
    void dispose();
    virtual ~Messages();

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    void loadAll();
    QHash<int, QByteArray> roleNames() const;

private:
    Messages(notmuch_messages_t* libnotmuch_messages, QObject* parent = 0);
    notmuch_messages_t* libnotmuch_messages;
    QList<Message*> messages;

    friend class Database;
    friend class Thread;
};

} // namespace notmuch

#endif // NOTMUCH_MESSAGES_H
