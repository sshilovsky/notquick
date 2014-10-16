TEMPLATE = app

QT += qml widgets
CONFIG += c++11

SOURCES += \
    src/notmuch/thread.cpp \
    src/notmuch/threads.cpp \
    src/notmuch/database.cpp \
    src/main.cpp \
    src/disposable.cpp \
    src/notmuch/tags.cpp

RESOURCES += qml.qrc

HEADERS += \
    src/notmuch/thread.h \
    src/notmuch/threads.h \
    src/notmuch/database.h \
    src/log.h \
    src/disposable.h \
    src/notmuch/tags.h

INCLUDEPATH += src/

LIBS += -lnotmuch
