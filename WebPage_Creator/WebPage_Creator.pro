#-------------------------------------------------
#
# Project created by QtCreator 2017-09-26T09:06:17
#
#-------------------------------------------------

QT       += core gui
QT       += webenginewidgets webchannel
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WebPage_Creator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    codeeditor.cpp \
    clicklabel.cpp

HEADERS  += mainwindow.h \
    codeeditor.h \
    clicklabel.h

FORMS    += mainwindow.ui

RESOURCES += \
    ziyuan1.qrc
