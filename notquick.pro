TEMPLATE = app

QT += qml widgets
CONFIG += link_pkgconfig c++11 no_keywords

SOURCES += \
    src/notmuch/thread.cpp \
    src/notmuch/threads.cpp \
    src/notmuch/database.cpp \
    src/main.cpp \
    src/disposable.cpp \
    src/notmuch/tags.cpp \
    src/notmuch/messages.cpp \
    src/notmuch/message.cpp \
    src/mime/fileentity.cpp

RESOURCES += qml.qrc

HEADERS += \
    src/notmuch/thread.h \
    src/notmuch/threads.h \
    src/notmuch/database.h \
    src/log.h \
    src/disposable.h \
    src/notmuch/tags.h \
    src/notmuch/messages.h \
    src/notmuch/message.h \
    src/mime/fileentity.h

INCLUDEPATH += src/

PKGCONFIG += gmime-2.6

LIBS += -lnotmuch

OTHER_FILES +=
