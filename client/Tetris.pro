#-------------------------------------------------
#
# Project created by QtCreator 2014-07-18T16:28:30
#
#-------------------------------------------------

QT       += core gui
QT       += opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tetris
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Glass.cpp \
    Figure.cpp \
    SocketStorage.cpp \
    SOCKET.cpp \
    MyThread.cpp \
    Thread.cpp

HEADERS  += mainwindow.h \
    Glass.h \
    Figure.h \
    Thread.h \
    SocketStorage.h \
    MyThread.h \
    Mutex.h \
    Autolock.h \
    SOCKET.h \
    Queue.h

FORMS    += mainwindow.ui
