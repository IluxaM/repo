#-------------------------------------------------
#
# Project created by QtCreator 2014-08-12T16:45:51
#
#-------------------------------------------------

QT       += core gui
QT       += opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Figure.cpp \
    MyThread.cpp \
    SOCKET.cpp \
    SocketStorage.cpp \
    Thread.cpp

HEADERS  += mainwindow.h \
    Autolock.h \
    Figure.h \
    Mutex.h \
    MyThread.h \
    Queue.h \
    SOCKET.h \
    SocketStorage.h \
    Thread.h

FORMS    += mainwindow.ui
