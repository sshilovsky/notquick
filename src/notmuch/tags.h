#ifndef NOTMUCH_TAGS_H
#define NOTMUCH_TAGS_H

#include <QAbstractListModel>
#include <notmuch.h>

namespace notmuch {

class Tags : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit Tags(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

private:
    Tags(notmuch_tags_t* libnotmuch_tags, QObject *parent);
    QStringList tags;

    friend class Database;
    friend class Thread;
};

} // namespace notmuch

#endif // NOTMUCH_TAGS_H
