#-------------------------------------------------
#
# Project created by QtCreator 2020-09-13T12:36:16
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = example
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    data.cpp \
    dialog.cpp \
    model.cpp \
    application.cpp

HEADERS  += mainwindow.h \
    data.h \
    dialog.h \
    model.h \
    application.h

FORMS    += mainwindow.ui \
    dialog.ui
