#-------------------------------------------------
#
# Project created by QtCreator 2015-06-18T23:24:13
#
#-------------------------------------------------

QT       += core gui\
            printsupport\
            sql widgets\
            widgets serialport\
            quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

OTHER_FILES += \
    TODO.txt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Dosing
TEMPLATE = app

#include(3dParty/qextserialport/src/qextserialport.pri)

SOURCES += main.cpp\
        dose.cpp \
    hled.cpp \
    timer.cpp \
    solution.cpp \
    tools.cpp \
    usb_thread.cpp

HEADERS  += dose.h \
    hled.h \
    usb_thread.h

FORMS    += dose.ui

RESOURCES += \
    icon.qrc

DISTFILES +=
