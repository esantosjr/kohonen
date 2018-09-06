#-------------------------------------------------
#
# Project created by QtCreator 2016-05-16T14:32:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Koh
CONFIG += console
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv /usr/local/include/opencv2
LIBS += -L/usr/local/lib -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core

SOURCES += main.cpp\
        dialog.cpp \
    node.cpp \
    network.cpp \
    kohonen.cpp \
    dialog2.cpp \
    dialog3.cpp

HEADERS  += dialog.h \
    node.h \
    network.h \
    kohonen.h \
    dialog2.h \
    dialog3.h

FORMS    += dialog.ui \
    dialog2.ui \
    dialog3.ui
