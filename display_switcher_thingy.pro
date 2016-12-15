#-------------------------------------------------
#
# Project created by QtCreator 2016-12-12T21:43:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#QMAKE_CXXFLAGS += -std=c++14
CONFIG += c++11

TARGET = display_switcher_thingy
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    displayfixer.cpp \
    nativeeventfilter.cpp

HEADERS  += mainwindow.h \
    displayfixer.h \
    nativeeventfilter.h

RESOURCES += \
    resources.qrc

LIBS += -lUser32
