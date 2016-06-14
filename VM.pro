#-------------------------------------------------
#
# Project created by QtCreator 2016-05-29T10:05:36
#
#-------------------------------------------------

QT       += core gui testlib

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
    gui/codeeditor.cpp \
    gui/microcommandview.cpp \
    gui/displaywidget.cpp \
    gui/timerview.cpp \
    gui/keyview.cpp \
    tst_main.cpp \
    tst_cpu.cpp

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
    gui/codeeditor.h \
    gui/microcommandview.h \
    gui/displaywidget.h \
    gui/timerview.h \
    gui/keyview.h

FORMS    += mainwindow.ui \
    gui/cpuwidget.ui \
    gui/memmorywidget.ui \
    gui/debugpanel.ui \
    gui/microcommandview.ui \
    gui/displaywidget.ui \
    gui/timerview.ui \
    gui/keyview.ui

QMAKE_LFLAGS_RELEASE += -static -static-libgcc

win32 {
    RC_FILE += file.rc
    OTHER_FILES += file.rc
}

RESOURCES += \
    res.qrc
