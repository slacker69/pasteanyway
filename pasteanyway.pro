#-------------------------------------------------
#
# Project created by QtCreator 2017-01-07T18:17:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pasteanyway
TEMPLATE = app

QMAKE_CXXFLAGS += -H

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

unix:contains(QMAKE_HOST.arch, x86_64):{
QMAKE_INCDIR_X11 = "/usr/include/X11"
LIBS += -L"/usr/lib/x86_64-linux-gnu/" -lX11 -lXtst
}


