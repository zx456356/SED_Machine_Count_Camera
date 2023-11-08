QT       += core gui
QT += core gui sql serialbus
QT += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = SED_LineScanCount


#CONFIG += build_all
OTHER_FILES += exeico.rc
RC_FILE = exeico.rc

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

Release:DESTDIR = ../../bin/release
Debug:DESTDIR = ../../bin/debug

INCLUDEPATH += ../../include

LIBS += ../../lib/Halcon/halcon.lib
LIBS += ../../lib/Halcon/halconcpp.lib

LIBS += ../../lib/VGraph/VisionGraph.lib
LIBS += ../../lib/MindVision/MVCAMSDK.lib
LIBS += ../../lib/CountGrain/CountGrain.lib
LIBS += ../../lib/DaHua/ImageConvert.lib
LIBS += ../../lib/DaHua/MVSDKmd.lib
LIBS += ../../lib/Modbus/modbus.lib
LIBS += ../../lib/XVLog.lib
LIBS += ../../lib/Preprocess.lib
LIBS += ../../lib/BlobAnalysisPro.lib

SOURCES += \
    countprocess.cpp \
    dahuacamera.cpp \
    login.cpp \
    logwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    modbust.cpp \
    settingwidget.cpp \
    tinyxml2.cpp \
    unitspainbox.cpp \
    viewwidget.cpp

HEADERS += \
    MessageQue.h \
    countprocess.h \
    dahuacamera.h \
    login.h \
    logwidget.h \
    mainwindow.h \
    modbust.h \
    settingwidget.h \
    tinyxml2.h \
    unitspainbox.h \
    viewwidget.h  \


FORMS += \
    login.ui \
    logwidget.ui \
    mainwindow.ui \
    settingwidget.ui \
    viewwidget.ui

RESOURCES += \
    ico.qrc


