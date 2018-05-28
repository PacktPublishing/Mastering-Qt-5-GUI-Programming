#-------------------------------------------------
#
# Project created by QtCreator 2018-01-14T01:28:14
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = filtering
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    colorpicker.cpp \
    viridisdialog.cpp

HEADERS += \
        mainwindow.h \
    photomodel.h \
    picturefilter.h \
    colorpicker.h \
    luminosity_calc.h \
    viridisdialog.h

RESOURCES += \
    ../pictures.qrc
