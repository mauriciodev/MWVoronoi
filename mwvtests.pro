CONFIG += qtestlib #debug
TEMPLATE = app
TARGET =

INCLUDEPATH += ./include
DEPENDPATH += ./bin
DESTDIR +=./bin
OBJECTS_DIR+=./obj

SOURCES += \
    ./src/stl.cpp \
    ./src/circle.cpp \
    ./tests/circletest.cpp
    #./src/mwvoronoidiagramgenerator.cpp \
    #./src/main.cpp

HEADERS += \
    ./include/stl.h \
    ./include/circle.h
    #../include/testqstring.h
    #./include/mwvoronoidiagramgenerator.h
