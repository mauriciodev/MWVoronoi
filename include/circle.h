#ifndef TECIRCLE_H
#define TECIRCLE_H
#include <math.h>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include "stl.h"

#define pi 3.1415926535897



typedef struct Polar {
    double r, theta;
} polar;

class xy {
public:
    xy(double x=0, double y=0) {
        this->x=x;
        this->y=y;
    }
    double x,y;
    double distance(xy p1);
    double angle(xy &p2, xy &p0);
    xy & operator-=(const xy &);
    xy operator-(const xy &);
    double operator*(const xy &);
    xy operator*(const double &);
    xy operator+(const xy &);
};

class line {
public:
    line(xy p0, xy p1);
    line(double p0x,double p0y,double p1x,double p1y);
    xy p0,p1;
};

class CircularArc {
public:
    CircularArc();
    CircularArc(double r, double cx, double cy, double startAngle, double endAngle);
    CircularArc(xy p0, xy p1, xy p2);
    ~CircularArc();

    /*! Computes the distance of a point to the CircleArc. The result may be negative (inside), zero (coincident) or positive (distance to boundary).*/
    double distance(xy);
    /*! Computes the intersection points between 2 arcs.*/
    bool intersection(const CircularArc &, std::vector<xy> &intersections);
    /*! Computes the intersection points between an arc and a line. */
    bool intersection(line l, std::vector<xy> & intersections);
    /*! Checks if a point is touching the arc */
    bool touches(xy &p);


    /*! Computes the intersection between 2 arcs. */
    bool polarIntersection(CircularArc *, std::vector<double> &intersections);

    /*! Maps from polar coordinates on the center of the circle to global X,Y. If r=0, computes on the circle's boundary.*/
    xy polarToXy(double radians, double r=0);
    /*! Maps from global X,Y to polar coordinates on the center of the circle.*/
    double xyToPolar(xy);
    double reduceAngle(double theta);

    /*! Returns X,Y coordinates where the arc starts. */
    xy begin();
    /*! Returns X,Y coordinates where the arc ends. */
    xy end();

    /*! Aproximate the circle using npoints equaly spaced.*/
    bool getAproximatedCircleArc(std::vector<xy> &,int npoints);
    /*! Aproximate the circle using a percentual error tolerance.
        Aproximation error = R(1-cos(theta/2)).
        dtheta=2*acos(1-tolerance/r).
        divisions=arcLength/dtheta. */
    bool getAproximatedCircleArc(std::vector<xy> &,double tolerance=0.001);

    /*! Exports the coordinates to a string. */
    std::string asString();
    std::string asApproximatedString();
    //double pi();

    //Attributes
    /*! Angles, in radians, of the begining and end of the arc. */
    double startAngle,endAngle;
    /*! Radius */
    double r;
    /*! center */
    xy c;

};

/*! Circle is a CircularArc that begins in 0 and ends in 2*pi(). */
class Circle: public CircularArc {
public:
    /*! Constructor. */
    Circle();
    /*! Fast constructor. */
    Circle(double r, double cx=0, double cy=0);
    ~Circle();

    /*! Topological test of a circle and a point.*/
    double distance(xy coords);
    bool Contains(xy p);

    //bool getApproximatedCoordinates(std::vector<xy> &coordinates,double maxError);
};


class ST_CircularString {
public:
    ST_CircularString();
    ~ST_CircularString();
    xy getVertex(unsigned int);
    std::vector<CircularArc> arcList;
    xy * getAproximatedPolygon(double tolerance=0.001);
    bool importFromWkt(std::string); //CIRCULARSTRING(0 0, 4 0, 4 4, 0 4, 0 0)
    std::string exportToPolygonWkt();
    bool clip(Circle c);

};

class ST_CurvePolygon {
public:
    ST_CurvePolygon();
    ~ST_CurvePolygon();
    std::vector<ST_CircularString> rings; //first is outer ring. The others are holes.
    int getNRings();
    ST_CircularString * getRingN(int n);
    bool clip(Circle c);
    bool clipOutside(Circle c);
    xy * getAproximatedPolygon(double tolerance=0.001);
    bool importFromWkt(std::string); //CURVEPOLYGON(CIRCULARSTRING(0 0, 4 0, 4 4, 0 4, 0 0),(1 1, 3 3, 3 1, 1 1))
    std::string exportToPolygonWkt();

};

class ST_MultiSurface {
public:
    ST_MultiSurface();
    ~ST_MultiSurface();
private:
    std::vector<ST_CurvePolygon> polygons;
};

#endif // TECIRCLE_H

