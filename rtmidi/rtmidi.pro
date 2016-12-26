TEMPLATE = lib
TARGET = rtmidi

DEFINES += __WINDOWS_MM__

LIBS += -lwinmm

include(../config.pri)

DEFINES += RTMIDI_COMPILING

HEADERS += \
    RtMidi.h \
    rtmidi_c.h

SOURCES += \
    RtMidi.cpp \
    rtmidi_c.cpp
