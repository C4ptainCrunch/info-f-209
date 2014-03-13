#-------------------------------------------------
#
# Project created by QtCreator 2014-02-26T20:13:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mainWindow
TEMPLATE = app
QMAKE_CXX=clang++


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
    ../receive-views/views.cpp

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

LIBS+= ../../../build/libjson.a ../../../build/libsocket.a ../../../build/libexception.a

CONFIG += c++11
