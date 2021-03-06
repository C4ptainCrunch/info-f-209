#-------------------------------------------------
#
# Project created by QtCreator 2014-02-26T20:13:07
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
CONFIG += debug

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = ../../../build

TARGET = bin/client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    menuwindow.cpp \
    loginscreenwidget.cpp \
    matchwidget.cpp \
    hexagon.cpp \
    teamhandlingwidget.cpp \
    auctionhousewidget.cpp \
    infrastructurewidget.cpp\
    ../receive-views/serverhandler.cpp\
    ../receive-views/views.cpp\


HEADERS  += mainwindow.h \
    menuwindow.h \
    loginscreenwidget.h \
    matchwidget.h \
    hexagon.h \
    teamhandlingwidget.h \
    auctionhousewidget.h \
    infrastructurewidget.h\
    ../receive-views/serverhandler.h\
    ../receive-views/views.h

FORMS    +=

OTHER_FILES += \
    ../build-mainWindow-Desktop-Release/stylesheets/stylesheet.qss \
    stylesheets/stylesheet.qss

LIBS+= $$DESTDIR/libjson.a $$DESTDIR/libsocket.a $$DESTDIR/libexception.a $$DESTDIR/client-send-views.a $$DESTDIR/libthread.a $$DESTDIR/models.a


OBJECTS_DIR = $$DESTDIR/qclient/
MOC_DIR = $$DESTDIR/qclient/.moc
RCC_DIR = $$DESTDIR/qclient/.rcc
UI_DIR = $$DESTDIR/qclient/.ui

