#-------------------------------------------------
#
# Project created by QtCreator 2013-09-21T12:19:59
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GuifiDecrypterNG
TEMPLATE = app


SOURCES += main.cpp\
        guifidecrypter.cpp \
    consoleout.cpp \
    unixifaceslist.cpp

HEADERS  += guifidecrypter.h \
    consoleout.h

FORMS    += guifidecrypter.ui
