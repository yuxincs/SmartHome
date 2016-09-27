#-------------------------------------------------
#
# Project created by QtCreator 2016-09-20T22:30:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartHome-Upper
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
		light.cpp\
		interface.cpp\
		serialcommunicator.cpp\
		model.cpp
		

HEADERS  += mainwindow.h\
		light.h\
		interface.h\
		serialcommunicator.h\
		model.h

FORMS    += mainwindow.ui
