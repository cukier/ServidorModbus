#-------------------------------------------------
#
# Project created by QtCreator 2019-04-22T08:26:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ServidorModbus
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    serial.cpp \
    servidor.cpp \
    libmodbus/src/modbus.c \
    libmodbus/src/modbus-ascii.c \
    libmodbus/src/modbus-data.c \
    libmodbus/src/modbus-rtu.c \
    libmodbus/src/modbus-tcp.c \
    modbuslistner.cpp

HEADERS += \
    serial.h \
    servidor.h \
    libmodbus/src/modbus.h \
    libmodbus/src/modbus-ascii.h \
    libmodbus/src/modbus-ascii-private.h \
    libmodbus/src/modbus-private.h \
    libmodbus/src/modbus-rtu.h \
    libmodbus/src/modbus-rtu-private.h \
    libmodbus/src/modbus-tcp.h \
    libmodbus/src/modbus-tcp-private.h \
    libmodbus/src/modbus-version.h \
    libmodbus/config.h \
    modbuslistner.h

FORMS += \
    serial.ui \
    servidor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/libmodbus
INCLUDEPATH += $$PWD/libmodbus/src

LIBS += -lws2_32
