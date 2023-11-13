QT -= gui

QT += network
QT += sql

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mytcpserver.cpp \
    functionsforserver.cpp \
    database.cpp

HEADERS += \
    mytcpserver.h \
    functionsforserver.h \
    database.h
