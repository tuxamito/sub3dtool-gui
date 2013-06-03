#-------------------------------------------------
#
# Project created by QtCreator 2013-05-31T11:13:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sub3dtool-gui
TEMPLATE = app


SOURCES += main.cpp\
        sub3dtoolgui.cpp \
    s3tdata.cpp \
    mainwindow.cpp

HEADERS  += sub3dtoolgui.h \
    s3tdata.h \
    mainwindow.h

FORMS    += sub3dtoolgui.ui \
    mainwindow.ui

RESOURCES += \
    sub3dtool-gui-images.qrc
