#ifndef MAIL_ENTITY_H
#define MAIL_ENTITY_H

#include <QObject>
#include <QFile>
#include <mimetic/mimeentity.h>

namespace mime {

class FileEntity : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString body READ body CONSTANT)

    QString body() const;
public:
    explicit FileEntity(QString filename = QString(), QObject *parent = 0);
    virtual ~FileEntity();

private:
    mimetic::MimeEntity* mimeticEntity;




};

} // namespace mail

#endif // MAIL_ENTITY_H
