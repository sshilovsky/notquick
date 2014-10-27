// TODO license note into all sources

#include <QtQml>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <gmime/gmime.h>


#include "notmuch/database.h"
#include "mime/fileentity.h"

notmuch::DatabaseProxy *proxy = 0;

static QObject* databaseSingleton(QQmlEngine* engine, QJSEngine* scriptEngine) {
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return proxy; // owned by QML anyway despite of setObjectOwnership, so proxying
}

int main(int argc, char *argv[])
{
    g_mime_init(0);
    atexit(g_mime_shutdown);

    notmuch::Database db;
    db.open();
    proxy = new notmuch::DatabaseProxy(&db); // owned by QML, so GC-ed later

    qmlRegisterSingletonType<notmuch::Database>("Notquick", 1, 0, "NotmuchDatabase", databaseSingleton);
    qmlRegisterType<mime::FileEntity>("Notquick", 1, 0, "MimeFileEntity");

    QApplication app(argc, argv); // TODO maybe switch to QGuiApplication
    QQmlApplicationEngine engine; // TODO maybe switch to QQmlEngine

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
