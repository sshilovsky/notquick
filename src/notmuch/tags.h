#ifndef NOTMUCH_TAGS_H
#define NOTMUCH_TAGS_H

#include <QAbstractListModel>
#include <notmuch.h>
#include <QSet>

namespace notmuch {

class Tags : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit Tags(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE bool canDrop(QString tag) const;
    Q_INVOKABLE bool drop(QString tag);

private:
    Tags(notmuch_tags_t* libnotmuch_tags, QObject *parent);
    void load(notmuch_tags_t* libnotmuch_tags);
    QStringList tags;
    QSet<QString> unique_list;

    friend class Database;
    friend class Thread;
    friend class Message;
};

} // namespace notmuch

#endif // NOTMUCH_TAGS_H
