#ifndef DISPOSABLE_H
#define DISPOSABLE_H

#include <QObject>

class Disposable
        // TODO !!! (?) backward property referencing the parent
{
public:
    virtual void dispose() = 0;
};

Q_DECLARE_INTERFACE(Disposable, "")

void dispose_children(QObject* self);

#endif // DISPOSABLE_H
