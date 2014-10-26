#include "fileentity.h"
#include <QFile>
#include <QDebug>

#include <fstream>

namespace mime {

QString FileEntity::body() const
{
    if(!mimeticEntity)
        return QString();
    return QString(mimeticEntity->body().c_str());
}

FileEntity::FileEntity(QString filename, QObject *parent) :
    QObject(parent)
{
    qDebug() << "opening " << filename;
    // TODO error messages to qCritical()
    std::ifstream f(filename.toLocal8Bit().data());
    mimeticEntity = new mimetic::MimeEntity();
    mimeticEntity->load(f, mimetic::imChildParts | mimetic::imEpilogue | mimetic::imPreamble);
}

FileEntity::~FileEntity()
{
    if(mimeticEntity)
        delete mimeticEntity;
}

} // namespace mail
