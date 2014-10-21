#ifndef LOG_H
#define LOG_H

#include <notmuch.h>
#include <QDebug>

static thread_local notmuch_status_t notmuch_status; \

#define ON_NOTMUCH_ERROR(funccall) \
    if ((notmuch_status = (funccall)) != NOTMUCH_STATUS_SUCCESS)

#define LOG_NOTMUCH_ERROR(msg) do { \
        qWarning() << (msg) << ": " << notmuch_status_to_string(notmuch_status); \
    } while(0)

#define LOG_NOTMUCH_INSUFFICIENT_MEMORY(msg) do { \
        notmuch_status = NOTMUCH_STATUS_OUT_OF_MEMORY; \
        LOG_NOTMUCH_ERROR(msg); \
    } while(0)

#define LOG_NOTMUCH_XAPIAN_EXCEPTION(msg) do { \
        notmuch_status = NOTMUCH_STATUS_XAPIAN_EXCEPTION; \
        LOG_NOTMUCH_ERROR(msg); \
    } while(0)

#define LOG_UNKNOWN_ERROR(msg) do { \
        qWarning() << (msg) << ": Unknown error"; \
    } while(0)

#endif // LOG_H
