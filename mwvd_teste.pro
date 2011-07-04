#-------------------------------------------------
#
# Project created by QtCreator 2011-05-03T21:19:38
#
#-------------------------------------------------
TE_PROJECT_TYPE=DEBUG
#include(../../terraViewPlugins/base/base.pro)
include(../../examples/base/base.pro)
include(../../build/qt/PostgreSQL/PostgreSQL.pro)
include(../../build/qt/terraView/terraview.pro)
INCLUDEPATH += ./include



QT       += core

QT       -= gui

TARGET = mwvd_teste
CONFIG   += console
CONFIG   -= app_bundle dll qt

TEMPLATE = app
LIBS+=-lterralib -lte_apputils -lterraViewCore -lte_spl -lte_utils -lterralibpdi -lqwt -lte_functions -lte_qwt -lte_shapelib -lte_postgresql -lte_oracle -lte_firebird -lclntsh -lnnz10 -lfbembed -licuuc -licudata -licui18n -lspl

SOURCES += \
    ./src/stl.cpp \
    ./src/mwvoronoidiagramgenerator.cpp \
    ./src/main.cpp

HEADERS += \
    ./include/stl.h \
    ./include/mwvoronoidiagramgenerator.h
