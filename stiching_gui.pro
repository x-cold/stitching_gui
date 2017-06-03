#-------------------------------------------------
#
# Project created by QtCreator 2017-03-28T17:55:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stiching_gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    conf.cpp \
    helper.cpp \
    stitching.cpp \
    logger.cpp \
    stiching_old.cpp

HEADERS  += mainwindow.h \
    logger.h

FORMS    += mainwindow.ui

INCLUDEPATH += D:/OpenCV/necessary_file/include/opencv
INCLUDEPATH += D:/OpenCV/necessary_file/include/opencv2
INCLUDEPATH += D:/OpenCV/necessary_file/include

LIBS += -L D:/OpenCV/necessary_file/lib/libopencv_*.a

RC_ICONS = stitching.ico

DISTFILES += \
    stitching.ico
