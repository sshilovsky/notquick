#include "database.h"
#include <notmuch.h>
#include <QProcessEnvironment>
#include "log.h"

namespace notmuch {

Database::Database(QObject *parent) :
    QObject(parent)
{
}

Database::~Database()
{
    dispose();
}

bool Database::open(QString path, bool readonly)
{
    // TODO if db != 0
    if(path.isEmpty()) {
        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        path = env.value("MAILDIR");
        if(path.isEmpty()) {
            path = env.value("HOME")+"/mail";
        }
    }

    notmuch_database_mode_t mode = readonly ? NOTMUCH_DATABASE_MODE_READ_ONLY
                                            : NOTMUCH_DATABASE_MODE_READ_WRITE;
    ON_NOTMUCH_ERROR(notmuch_database_open(path.toLocal8Bit().data(), mode, &libnotmuch_database)) {
        LOG_NOTMUCH_ERROR("notmuch_database_open");
        return false;
    }
    return true;
}

bool Database::openReadonly(QString path)
{
    return open(path, true);
}

void Database::dispose()
{
    dispose_children(this);
    if(libnotmuch_database) {
        ON_NOTMUCH_ERROR(notmuch_database_destroy(libnotmuch_database)) {
            LOG_NOTMUCH_ERROR("notmuch_database_destroy");
        }
        libnotmuch_database = 0;
    }
}

QObject *Database::query_threads(QString query_string)
{
    notmuch_query_t* libnotmuch_query = notmuch_query_create(libnotmuch_database, query_string.toLocal8Bit());
    if(!libnotmuch_query) {
        LOG_NOTMUCH_INSUFFICIENT_MEMORY("notmuch_query_create");
        return 0;
    }

    notmuch_threads_t* libnotmuch_threads = notmuch_query_search_threads(libnotmuch_query);
    if(!libnotmuch_threads) {
        LOG_NOTMUCH_XAPIAN_EXCEPTION("notmuch_query_search_threads");
        notmuch_query_destroy(libnotmuch_query);
        return 0;
    }

    Threads* threads = new Threads(libnotmuch_threads, this);
    threads->dispose_libnotmuch_query = libnotmuch_query;
    threads->loadAll();
    return threads;
}

DatabaseProxy::DatabaseProxy(Database *database)
    : database(database)
{
}

QObject *DatabaseProxy::query_threads(QString query_string)
{
    return database->query_threads(query_string);
}

} // namespace notmuch
