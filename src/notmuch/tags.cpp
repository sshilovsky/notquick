#include "tags.h"
#include <QMetaMethod>

namespace notmuch {

Tags::Tags(QObject *parent) :
    Tags(0, parent)
{
}

int Tags::rowCount(const QModelIndex &parent) const
{
    return tags.size();
}

QVariant Tags::data(const QModelIndex &index, int role) const
{
    return QVariant::fromValue(tags[index.row()]);
}

QHash<int, QByteArray> Tags::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[0] = "name";
    return roles;
}

bool Tags::canDrop(QString tag) const
{
    if(parent() == 0)
        return false;
    int index = parent()->metaObject()->indexOfMethod("dropTag(QString)");
    if(index == -1)
        return false;
    if(tag == "signed" || tag == "attachment" || tag == "encrypted")
        return false;
    return true;
}

bool Tags::drop(QString tag)
{
    int methodIndex = parent()->metaObject()->indexOfMethod("dropTag(QString)");
    if(methodIndex == -1)
        return false;
    bool dropped;
    parent()->metaObject()->method(methodIndex).invoke(parent(), Q_RETURN_ARG(bool, dropped), Q_ARG(QString, tag));

    if(dropped) {
        int index = tags.indexOf(QRegExp(tag, Qt::CaseSensitive, QRegExp::FixedString));
        if(index >= 0) {
            beginRemoveRows(QModelIndex(), index, index);
            tags.removeAt(index);
            unique_list.remove(tag);
            endRemoveRows();
        }
    }
    return dropped;
}

Tags::Tags(notmuch_tags_t *libnotmuch_tags, QObject *parent)
    : QAbstractListModel(parent)
{
    if(libnotmuch_tags) {
        load(libnotmuch_tags);
    }
}

void Tags::load(notmuch_tags_t *libnotmuch_tags)
{
    while(notmuch_tags_valid(libnotmuch_tags)) {
        QString tag_name = notmuch_tags_get(libnotmuch_tags);
        if(!unique_list.contains(tag_name)) {
            unique_list.insert(tag_name);
            tags.append(tag_name);
        }

        notmuch_tags_move_to_next(libnotmuch_tags);
    }
}

} // namespace notmuch
