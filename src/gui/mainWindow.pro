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
    loginscreenwidget.cpp

HEADERS  += mainwindow.h \
    menuwindow.h \
    loginscreenwidget.h

FORMS    +=

OTHER_FILES += \
    ../build-mainWindow-Desktop-Release/stylesheets/stylesheet.qss
