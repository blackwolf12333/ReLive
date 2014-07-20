#-------------------------------------------------
#
# Project created by QtCreator 2014-07-18T15:07:59
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReLive
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    delayedvideosurface.cpp

HEADERS  += mainwindow.h \
    delayedvideosurface.h

FORMS    += mainwindow.ui
