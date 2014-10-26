#ifndef MYTEST_H
#define MYTEST_H

#include <QObject>

class MyTest : public QObject
{
    Q_OBJECT
public:
    explicit MyTest(QObject *parent = 0);

signals:

public slots:

};

#endif // MYTEST_H
