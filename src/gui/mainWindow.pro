#-------------------------------------------------
#
# Project created by QtCreator 2014-02-26T20:13:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mainWindow
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    menuwindow.cpp \
    loginscreenwidget.cpp \
    matchwidget.cpp \
    hexagon.cpp \
    teamhandlingwidget.cpp \
    auctionhousewidget.cpp

HEADERS  += mainwindow.h \
    menuwindow.h \
    loginscreenwidget.h \
    matchwidget.h \
    hexagon.h \
    teamhandlingwidget.h \
    auctionhousewidget.h

FORMS    +=

OTHER_FILES += \
    ../build-mainWindow-Desktop-Release/stylesheets/stylesheet.qss \
    stylesheets/stylesheet.qss
