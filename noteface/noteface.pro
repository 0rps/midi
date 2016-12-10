TEMPLATE = lib
TARGET = noteface

CONFIG += c++11

QT += core
QT -= gui

LIBS += -L../debug -lrtmidi

include(../config.pri)

INCLUDEPATH += ./include/noteface
VPATH += ./include/noteface

DEFINES += NOTEFACE_DLL

include(noteface.pri)
