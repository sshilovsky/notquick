#include "disposable.h"
#include <QObject>

void dispose_children(QObject* self) {
    foreach(QObject* child, self->children()) {
        Disposable* disposable = qobject_cast<Disposable*>(child);
        if(disposable)
            disposable->dispose();
    }
}

