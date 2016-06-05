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
    gui/hightlighter.cpp \
    gui/cpuwidget.cpp \
    abstactcommand.cpp \
    compiler.cpp \
    commandsimpl.cpp \
    commandfactory.cpp \
    cell.cpp \
    memory.cpp \
    gui/memmorywidget.cpp \
    codegenerator.cpp \
    runer.cpp \
    gui/debugpanel.cpp \
    gui/codeeditor.cpp

HEADERS  += mainwindow.h \
    cpu.h \
    registerscpu.h \
    gui/hightlighter.h \
    gui/cpuwidget.h \
    abstactcommand.h \
    compiler.h \
    commandsimpl.h \
    commandfactory.h \
    cell.h \
    memory.h \
    gui/memmorywidget.h \
    mtypes.h \
    codegenerator.h \
    runer.h \
    gui/debugpanel.h \
    gui/codeeditor.h

FORMS    += mainwindow.ui \
    gui/cpuwidget.ui \
    gui/memmorywidget.ui \
    gui/debugpanel.ui

QMAKE_LFLAGS_RELEASE += -static -static-libgcc

win32 {
    RC_FILE += file.rc
    OTHER_FILES += file.rc
}

RESOURCES += \
    res.qrc
