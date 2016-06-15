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
    gui/hightlighter.cpp \
    gui/cpuwidget.cpp \
    gui/memmorywidget.cpp \
    gui/debugpanel.cpp \
    gui/codeeditor.cpp \
    gui/microcommandview.cpp \
    gui/displaywidget.cpp \
    gui/timerview.cpp \
    gui/keyview.cpp \
    builder/codegenerator.cpp \
    builder/compiler.cpp \
    builder/runer.cpp \
    commands/abstactcommand.cpp \
    commands/commandfactory.cpp \
    commands/commandsimpl.cpp \
    devise/cell.cpp \
    devise/cpu.cpp \
    devise/memory.cpp \
    devise/registerscpu.cpp

HEADERS  += mainwindow.h \
    gui/hightlighter.h \
    gui/cpuwidget.h \
    gui/memmorywidget.h \
    gui/debugpanel.h \
    gui/codeeditor.h \
    gui/microcommandview.h \
    gui/displaywidget.h \
    gui/timerview.h \
    gui/keyview.h \
    builder/codegenerator.h \
    builder/compiler.h \
    builder/runer.h \
    commands/abstactcommand.h \
    commands/commandfactory.h \
    commands/commandsimpl.h \
    devise/cell.h \
    devise/cpu.h \
    devise/memory.h \
    devise/registerscpu.h

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
