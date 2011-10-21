TARGET = voronoi
#TE_PROJECT_TYPE=DEBUG
include( ../base/base.pro ) 
LIBS += -L../../Debug 
TRANSLATIONS = voronoi_pt.ts voronoi_sp.ts
INCLUDEPATH += ./include
HEADERS += ./include/voronoidiagramplugin.h \
 ./include/voronoidiagramPluginCode.h \
 ./include/VoronoiDiagramGenerator.h \
 ./include/VoronoiWindow.h \
 ./include/Utils.h \
 ./include/stl.h \
 ./include/wsite.h \
 ./include/mwvoronoidiagramgenerator.h
SOURCES += ./src/voronoidiagramplugin.cpp \
 ./src/voronoidiagramPluginCode.cpp \
 ./src/VoronoiDiagramGenerator.cpp \
 ./src/VoronoiWindow.cpp \
 ./src/Utils.cpp \
 ./src/stl.cpp \
 ./src/wsite.cpp \
 ./src/mwvoronoidiagramgenerator.cpp \
 ../../src/terralib/functions/TeGeoProcessingFunctions.cpp \
 ../../src/terralib/functions/TeCellAlgorithms.cpp
FORMS += ./ui/UIVoronoi.ui 
IMAGES = ./images/voronoi.png ./images/delaunay.png ./images/mwvoronoi.png
TEMPLATE = lib
