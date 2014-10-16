#ifndef DISPOSABLE_H
#define DISPOSABLE_H

#include <QObject>

class Disposable
{
public:
    virtual void dispose() = 0;
};

Q_DECLARE_INTERFACE(Disposable, "")

void dispose_children(QObject* self);

#endif // DISPOSABLE_H
