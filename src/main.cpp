#include <QtQml>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "src/notmuch/thread.h"
#include "src/notmuch/threads.h"
#include "src/notmuch/database.h"
#include "src/notmuch/tags.h"

notmuch::DatabaseProxy *proxy = 0;

static QObject* databaseSingleton(QQmlEngine* engine, QJSEngine* scriptEngine) {
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return proxy; // owned by QML anyway despite of setObjectOwnership, so proxying
}

int main(int argc, char *argv[])
{
    notmuch::Database db;
    db.openReadonly();
    proxy = new notmuch::DatabaseProxy(&db);

    qmlRegisterSingletonType<notmuch::Database>("Notmuch", 1, 0, "NotmuchDatabase", databaseSingleton);
    //qmlRegisterType<notmuch::Threads>("Notmuch", 1, 0, "NotmuchThreads");
    //qmlRegisterType<notmuch::Tags>("Notmuch", 1, 0, "NotmuchTags");

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/ThreadItem.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/Tag.qml")));

    return app.exec();
}
