#-------------------------------------------------
#
# Project created by QtCreator 2011-12-13T22:44:36
#
#-------------------------------------------------
QT       += core gui console

TARGET = FTGACARS
TEMPLATE = app


SOURCES   += main.cpp\
    Core/ACARSInputRegistry.cpp \
    Core/ACARSInput.cpp \
    Core/ACARSDataBunk.cpp \
    FlightSim/ACARSFlightSimData.cpp \
    Core/ACARSUser.cpp \
    Core/ACARSSystem.cpp \
    Core/ACARSEvents.cpp \
    Core/ACARSMenuPage.cpp \
    Core/ACARSMenu.cpp \
    Menus/LOGIN/MENULogin.cpp \
    Menus/LOGIN/MENUPAGELogin.cpp \
    Menus/INIT/MENUInit.cpp \
    Menus/INIT/MENUPAGEInit1.cpp \
    Menus/INIT/MENUPAGEInit2.cpp

HEADERS  +=\
    Core/ACARSInputRegistry.h \
    Core/ACARSInput.h \
    Core/ACARSDataBunk.h \
    FlightSim/ACARSFlightSimData.h \
    Core/ACARSUser.h \
    Core/ACARSSystem.h \
    Core/ACARSEvents.h \
    Core/ACARSMenuPage.h \
    Core/ACARSMenu.h \
    Menus/LOGIN/MENULogin.h \
    Menus/LOGIN/MENUPAGELogin.h\
    Menus/INIT/MENUInit.h \
    Menus/INIT/MENUPAGEInit1.h \
    Menus/INIT/MENUPAGEInit2.h

FORMS    += Core/ACARSMainWindow.ui






