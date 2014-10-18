#include "tags.h"

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

Tags::Tags(notmuch_tags_t *libnotmuch_tags, QObject *parent)
    : QAbstractListModel(parent)
{
    if(libnotmuch_tags) {
        while(notmuch_tags_valid(libnotmuch_tags)) {
            tags.append(notmuch_tags_get(libnotmuch_tags));
            notmuch_tags_move_to_next(libnotmuch_tags);
        }
    }
    // TODO notmuch_tags_destroy (?)
}

} // namespace notmuch
