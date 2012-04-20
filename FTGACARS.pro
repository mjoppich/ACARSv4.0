#-------------------------------------------------
#
# Project created by QtCreator 2011-12-13T22:44:36
#
#-------------------------------------------------

QT       += core gui console

TARGET = FTGACARS
TEMPLATE = app


SOURCES   += main.cpp\
            Core/ACARSMenuView.cpp\
    Core/ACARSInputRegistry.cpp \
    Core/ACARSInput.cpp \
    Core/ACARSDataBunk.cpp \
    FlightSim/ACARSFlightSimData.cpp \
    Core/ACARSUser.cpp \
    Core/ACARSSystem.cpp

HEADERS  +=\
            Core/ACARSMenuView.h\
    Core/ACARSInputRegistry.h \
    Core/ACARSInput.h \
    Core/ACARSDataBunk.h \
    FlightSim/ACARSFlightSimData.h \
    Core/ACARSUser.h \
    Core/ACARSSystem.h

FORMS    += Core/ACARSMainWindow.ui






