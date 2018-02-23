#-------------------------------------------------
#
# Project created by QtCreator 2017-03-30T18:17:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ebooks
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    stilform.cpp

HEADERS  += mainwindow.h \
    stilform.h

FORMS    += mainwindow.ui \
    stilform.ui

include(BookParser.pri)
include(Latex.pri)
