#-------------------------------------------------
#
# Project created by QtCreator 2011-12-13T22:44:36
#
#-------------------------------------------------

QT       += core gui console

TARGET = FTGACARS
TEMPLATE = app


SOURCES   += main.cpp\
            "Core\ACARSMainWindow.cpp"\
            "Core\ACARSMenuView.cpp"\
    Core/ACARSInputRegistry.cpp \
    Core/ACARSCore.cpp \
    Core/ACARSInput.cpp

HEADERS  += "Core\ACARSMainWindow.h"\
            "Core\ACARSMenuView.h"\
    Core/ACARSInputRegistry.h \
    Core/ACARSCore.h \
    Core/ACARSInput.h

FORMS    += "Core\ACARSMainWindow.ui"






