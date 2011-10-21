#ifndef WSITE_H
#define WSITE_H
#include <string>
#include <TeGeometry.h>
#include <sstream>
#include "stl.h"


class wsite
{
public:
    /*! Default constructor with coordinates and weights equals zero*/
    wsite();

    /*! Constructor that loads x,y and weight.*/
    wsite(double x, double y, double w);

    ~wsite();

    std::string AsString();
    TePoint *asPoint();

    /*! Computes the weighted distance from a point p1 to the site. */
    double wDistance(TePoint p1); //weighted distance

    /*! Computes the weighted distance from a point with coordinates (x,y) to the site. */
    double wDistance(double x, double y); //weighted distance

    /*! Computes the euclidean distance from the site to a point with coordinates (x,y).*/
    double eDistance(double x, double y); //euclidean distance

    /*! Computes the euclidean distance to another site.*/
    double eDistance(wsite p); //euclidean distance

    /*! Site's weight. */
    double w;

    /*! Site's coordinates. */
    double x,y;
};


#endif // WSITE_H
