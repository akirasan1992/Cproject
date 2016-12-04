#-------------------------------------------------
#
# Project created by QtCreator 2016-11-20T21:05:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ccc
TEMPLATE = app

INCLUDEPATH += 3rdparty/tiff-4.0.7/libtiff

SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h

FORMS    += \
    mainwindow.ui

LIBS += -L"3rdparty/tiff-4.0.7/libtiff" -llibtiff
