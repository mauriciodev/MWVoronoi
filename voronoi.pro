TARGET = voronoi
include( ../base/base.pro ) \
TRANSLATIONS = voronoi_pt.ts voronoi_sp.ts
INCLUDEPATH += ./include
HEADERS += ./include/voronoidiagramplugin.h \
 ./include/voronoidiagramPluginCode.h \
 ./include/VoronoiDiagramGenerator.h \
 ./include/VoronoiWindow.h \
 ./include/Utils.h \
 include/stl.h \
 include/mwvoronoidiagramgenerator.h
SOURCES += ./src/voronoidiagramplugin.cpp \
 ./src/voronoidiagramPluginCode.cpp \
 ./src/VoronoiDiagramGenerator.cpp \
 ./src/VoronoiWindow.cpp \
 ./src/Utils.cpp \
 src/stl.cpp \
 src/mwvoronoidiagramgenerator.cpp
FORMS += ./ui/UIVoronoi.ui 
IMAGES = ./images/voronoi.png ./images/delaunay.png ./images/mwvoronoi.png
TEMPLATE = lib
