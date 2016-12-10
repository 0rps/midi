#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T13:05:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = midi_test
TEMPLATE = app

include(../config.pri)

LIBS += -L../debug -lnoteface

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
