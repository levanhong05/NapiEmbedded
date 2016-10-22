#-------------------------------------------------
#
# Project created by QtCreator 2016-10-14T15:50:20
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = napiLCD
TEMPLATE = app

unix:TARGET = NapiLCD
win32:TARGET = ../../bin/NapiLCD

DEFINES += QWT_DLL

SOURCES +=  main.cpp\
            napilcddisplay.cpp \
            distancewidget.cpp \
            alignmentwidget.cpp \
            pressurewidget.cpp \
            chartwidget.cpp \
            tcpserver.cpp \
            udplistener.cpp \
    androidsender.cpp \
    splashscreen.cpp \
    tcpclient.cpp

HEADERS  += napilcddisplay.h \
            distancewidget.h \
            alignmentwidget.h \
            pressurewidget.h \
            chartwidget.h \
            tcpserver.h \
            udplistener.h \
            singleton.h \
            keywords.h \
    androidsender.h \
    splashscreen.h \
    tcpclient.h

FORMS    += napilcddisplay.ui \
            distancewidget.ui \
            alignmentwidget.ui \
            pressurewidget.ui \
            chartwidget.ui \
    splashscreen.ui

RESOURCES += \
            napilcd_res.qrc

# libqwt
win32:LIBS += -L$$OUT_PWD/../bin -lqwt
unix:LIBS += -L$$OUT_PWD/../qwt/lib -lqwt

INCLUDEPATH += $$PWD/../../qwt/src
DEPENDPATH += $$PWD/../../qwt/src

unix: INCLUDEPATH += /usr/local/qwt-6.1.2/include
