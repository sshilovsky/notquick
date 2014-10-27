#include "fileentity.h"
#include <QFile>
#include <QDebug>

#include "log.h"

namespace mime {

QString FileEntity::body() const
{
    if(!gmime_message)
        return QString();

    // TODO check content-type; charset&crlf filter

    QString result;
    GMimeDataWrapper* gmime_wrapper = 0;
    GMimeStream* gmime_data = 0;
    GByteArray* g_bytearray = 0;

    // TODO error checking
    gmime_wrapper = g_mime_part_get_content_object(gmime_part);
    if(!gmime_wrapper) {
        LOG_GMIME_ERROR_NULL("g_mime_part_get_content_object");
        goto cleanup;
    }

    gmime_data = g_mime_stream_mem_new();
    if(!gmime_data) {
        LOG_GMIME_ERROR_NULL("g_mime_stream_mem_new");
        goto cleanup;
    }

    if(-1 == g_mime_data_wrapper_write_to_stream(gmime_wrapper, gmime_data)) {
        LOG_GMIME_ERROR_NULL("g_mime_data_wrapper_write_to_stream");
        goto cleanup;
    }

    g_bytearray = g_mime_stream_mem_get_byte_array(GMIME_STREAM_MEM(gmime_data)); // no error ?

    result = QString::fromUtf8(QByteArray::fromRawData((const char*)(g_bytearray->data), g_bytearray->len));

cleanup:
    /*if(g_bytearray)
        g_byte_array_free(g_bytearray, false);*/
    if(gmime_data)
        g_object_unref(gmime_data);
    if(gmime_wrapper)
        g_object_unref(gmime_wrapper);

    return result;
}

FileEntity::FileEntity(QString filename, QObject *parent) :
    QObject(parent),
    file(filename),
    file_memory(0),
    gmime_message(0),
    gmime_stream(0)
{
    GMimeParser* gmime_parser = 0;

    qDebug() << "opening " << filename;
    if(!file.open(QIODevice::ReadOnly)) {
        qCritical() << "error opening " << filename << ": " << file.errorString();
        return;
    }
    file_memory = file.map(0, file.size());
    if(!file_memory) {
        qCritical() << "error mmapping " << filename << ": " << file.errorString();
        return;
    }
    gmime_stream = g_mime_stream_mem_new_with_buffer((char*)file_memory, file.size());
    if(!gmime_stream) {
        LOG_GMIME_ERROR_NULL("g_mime_stream_mem_new_with_buffer: error");
        return;
    }
    g_mime_stream_mem_set_owner(GMIME_STREAM_MEM(gmime_stream), false);

    gmime_parser = g_mime_parser_new_with_stream(gmime_stream);
    if(!gmime_parser) {
        LOG_GMIME_ERROR_NULL("g_mime_parser_new_with_stream: error");
        goto cleanup;
    }

    gmime_message = g_mime_parser_construct_message(gmime_parser);
    if(!gmime_message) {
        LOG_GMIME_ERROR_NULL("g_mime_parser_construct_message");
        goto cleanup;
    }

    gmime_part = GMIME_PART(g_mime_message_get_mime_part(gmime_message));
    if(!gmime_part) {
        LOG_GMIME_ERROR_NULL("g_mime_message_get_mime_part");
        goto cleanup;
    }

cleanup:
    if(gmime_parser)
        g_object_unref(gmime_parser);
}

FileEntity::~FileEntity()
{
    //if(gmime_part) // TODO uncomment ?
    //    g_object_unref(gmime_part);
    //if(gmime_message) // TODO uncomment ?
    //    g_object_unref(gmime_message);
    if(gmime_stream)
        g_object_unref(gmime_stream);
    if(file_memory) {
        if(!file.unmap(file_memory)) {
            qDebug()  << "unmap failed";
            qFatal("unmap failed");
        }
    }
    file.close();
}

} // namespace mail
