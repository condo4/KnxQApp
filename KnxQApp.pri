# KnxQApp
HEADERS += \
    $$PWD/knxinterface.h \
    $$PWD/knxobject.h \
    $$PWD/appstatus.h \
    $$PWD/knxobjectproxy.h

SOURCES += \
    $$PWD/knxobject.cpp \
    $$PWD/knxinterface.cpp \
    $$PWD/appstatus.cpp \
    $$PWD/knxobjectproxy.cpp

include(QtSsh/QtSsh.pri)
INCLUDEPATH += "$$PWD"
