#-------------------------------------------------
#
# Project created by QtCreator 2018-09-13T09:38:53
#
#-------------------------------------------------

QT       += widgets

TARGET = XVLog
TEMPLATE = lib

DEFINES += XVLOG_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

Debug:MOC_DIR =             $$PWD/../../../../tmp/debug/common
Debug:RCC_DIR =             $$PWD/../../../../tmp/debug/common
Debug:UI_DIR =              $$PWD/../../../../tmp/debug/common
Debug:OBJECTS_DIR =         $$PWD/../../../../tmp/debug/common

Release:MOC_DIR =           $$PWD/../../../../tmp/release/common
Release:RCC_DIR =           $$PWD/../../../../tmp/release/common
Release:UI_DIR =            $$PWD/../../../../tmp/release/common
Release:OBJECTS_DIR =       $$PWD/../../../../tmp/release/common

Debug:DESTDIR = ../../../bin/debug
Release:DESTDIR = ../../../bin/release

CONFIG += build_all



SOURCES += xvlog.cpp \
    myutils.cpp \
    xvlogwidget.cpp

HEADERS += xvlog.h\
        xvlog_global.h \
    log.h \
    myutils.h \
    xvloglevel.h \
    xvlogwidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
