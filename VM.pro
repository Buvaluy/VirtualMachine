#-------------------------------------------------
#
# Project created by QtCreator 2016-05-29T10:05:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cpu.cpp \
    registerscpu.cpp \
    gui/hightlighter.cpp

HEADERS  += mainwindow.h \
    cpu.h \
    registerscpu.h \
    gui/hightlighter.h

FORMS    += mainwindow.ui
