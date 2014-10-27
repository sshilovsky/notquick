#ifndef MAIL_ENTITY_H
#define MAIL_ENTITY_H

#include <glib.h>
#include <gmime/gmime.h>

#include <QObject>
#include <QFile>

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
    QFile file;
    uchar* file_memory;
    GMimeStream* gmime_stream;
    GMimeMessage* gmime_message;
    GMimePart* gmime_part;





};

} // namespace mail

#endif // MAIL_ENTITY_H
