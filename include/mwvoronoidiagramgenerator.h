#ifndef MWVORONOIDIAGRAMGENERATOR_H
#define MWVORONOIDIAGRAMGENERATOR_H
//

#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include "stl.h"


#include <TeGeometry.h>
#include <TeBufferRegion.h>
#include <TeOverlay.h>


class wsite
{
public:
    wsite();
    wsite(double x, double y, double w);
    wsite(std::vector<std::string>);
    ~wsite();
    std::string AsString();
    TePoint *asPoint();
    double distance(TePoint p1); //weighted distance
    double distance(double x, double y); //weighted distance
    double eDistance(double x, double y); //euclidean distance
    double eDistance(wsite p); //euclidean distance
    double w,x,y;
};

class mwVoronoiDiagramGenerator//: VoronoiDiagramGenerator
{

public:
    mwVoronoiDiagramGenerator();
    ~mwVoronoiDiagramGenerator();
    float tol;
    void printSites();
    void readSites(const char * filename);
    void writeCSV(const char * filename);


    bool isMinimumDistance(TePoint x, double d);
    bool generateVoronoi(float *xValues, float *yValues,  float *wValues, int numPoints, double minX, double maxX, double minY, double maxY);
    bool generateVoronoi2();
    bool generateVoronoi();
    /*!
        Método que retorna um polígono de nsides lados representando o círculo de apolônio formado entre dois pontos geradores ponderados.
    */
    TePolygon *apolonio(wsite s1, wsite s2, int nsides=360);
    /*!
      Retorna um polígono retangular a partir das coordenadas de canto. Utilizada para calcular a área máxima do diagrama.
    */
    TePolygon *boxFromExtent(double xmin, double xmax,double ymin,double ymax);
    TePolygonSet *domList;
private:
    vector<wsite> *siteList;
    TePolygon *areaBox;
    
    


};
#endif




