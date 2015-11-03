#-------------------------------------------------
#
# Project created by QtCreator 2015-04-20T20:18:59
#
#-------------------------------------------------

QT       += core gui
QT += printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = drawingboard
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    drawingboard.cpp

HEADERS  += mainwindow.h \
    drawingboard.h

FORMS    += mainwindow.ui

RESOURCES += \
    drawing.qrc

DISTFILES +=

