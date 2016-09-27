#-------------------------------------------------
#
# Project created by QtCreator 2016-09-21T20:16:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartHome-Lower
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
		adc.cpp\
		interface.cpp\
		light.cpp\
		motor.cpp\
		model.cpp\
		serialcommunicator.cpp\
		
		

HEADERS  += mainwindow.h\
		adc.h\
		interface.h\
		light.h\
		motor.h\
		model.h\
		serialcommunicator.h\
		ApiEx.h

FORMS    += mainwindow.ui
