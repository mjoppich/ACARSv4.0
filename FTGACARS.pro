# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = FTGACARS
DESTDIR = ./debug
QT += core network widgets gui xml
CONFIG += debug
CONFIG += embed_manifest_exe
DEFINES += _WINDOWS _WINDOWS QT_LARGEFILE_SUPPORT QT_DLL QT_HAVE_MMX QT_HAVE_3DNOW QT_HAVE_SSE QT_HAVE_MMXEXT QT_HAVE_SSE2 QT_NETWORK_LIB QT_NETWORK_LIB QT_WIDGETS_LIB
INCLUDEPATH += ./debug \
    ./GeneratedFiles \
    ./debug \
    ./GeneratedFiles \
    ./
LIBS += -L"E:\Qt\angle\lib" \ -ldnsapi \
    -lwinspool \
    -lshlwapi \
    -lrpcrt4 \
    -lcomdlg32 \
    -loleaut32 \
    -limm32 \
    -lwinmm \
    -lglu32 \
    -lopengl32 \
    -lgdi32 \
    -lkernel32 \
    -luser32 \
    -lshell32 \
    -luuid \
    -lole32 \
    -ladvapi32 \
    -lws2_32 \
	-legl
DEPENDPATH += .
MOC_DIR += debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(FTGACARS.pri)
