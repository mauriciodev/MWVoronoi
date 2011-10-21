#include "circle.h"

//////////////////
//Circle Methods
//////////////////


double xy::distance(xy p2) {
    double x2=(this->x-p2.x);
    x2*=x2;
    double y2=(this->y-p2.y);
    y2*=y2;
    return sqrt(x2+y2);
}



Circle::Circle() : CircularArc() {
    this->startAngle=0;
    this->endAngle=2*pi;
}

Circle::Circle(double r, double cx, double cy): CircularArc() {
    this->r=r;
    this->c.x=cx;
    this->c.y=cy;
    this->startAngle=0;
    this->endAngle=2*pi;
}

/*! Destructor */
Circle::~Circle() {
}

bool Circle::Contains(xy p) {
    double d=this->c.distance(p);
    if (d>r) {
        return false;
    } else {
        return true;
    }
}

/////////////////////
//CircularArc Methods
/////////////////////

/*double CircularArc::pi() {
    return acos(-1.);
}*/

double CircularArc::distance(xy coords) {
    double polar=this->xyToPolar(coords);
    double d;
    if ((polar<this->endAngle) && (polar>this->startAngle)) {
        d=this->c.distance(coords);
    }
    return d-this->r;
}

xy CircularArc::begin() {
    return this->polarToXy(this->startAngle);
}
xy CircularArc::end() {
    return this->polarToXy(this->endAngle);
}
double CircularArc::xyToPolar(xy coords) {
    double dx=coords.x-this->c.x;
    double dy=coords.y-this->c.y;
    //computing center inclination and fixing quadrant
    double theta0=atan( dy / dx );
    if ((theta0>0) && (dy<0)) theta0+=pi; //third quadrant
    if ((theta0<0) && (dy>0)) theta0+=pi; //second quadrant

    return this->reduceAngle(theta0);
}

xy CircularArc::polarToXy(double radians, double r) {
    xy res;
    if (r==0) r=this->r;
    res.x=this->c.x+r*cos(radians);
    res.y=this->c.y+r*sin(radians);
    return res;
}

double CircularArc::reduceAngle(double theta) {
    if (theta>2*pi) {
        return fmod(theta,2*pi);
    } else if (theta<0){
        return fmod(theta,2*pi)+2*pi;
    } else {
        return theta;
    }
}

bool CircularArc::polarIntersection(CircularArc *c2, std::vector<double> &intersections) {
    double dx=c2->c.x-this->c.x;
    double dy=c2->c.y-this->c.y;
    double d=sqrt(dx*dx+dy*dy);
    if ((d> (this->r + c2->r) ) || ( fabs(this->r - c2->r) > d)) {
        return false;
    }

    double theta= acos((this->r*this->r + d*d - c2->r*c2->r) / ( 2 * this->r * d)); //cossine's law
    //computing center inclination and fixing quadrant
    double theta0=atan( dy / dx );
    if ((theta0>0) && (dy<0)) theta0+=pi;
    if ((theta0<0) && (dy>0)) theta0+=pi;

    double res[2];
    //compute positive angles between 0 and 2*pi and store in counter clockwise order
    res[0]=reduceAngle(theta0-theta+2*pi);
    res[1]=reduceAngle(theta0+theta+2*pi);

    for (int i=0; i< 2; i++) {
        if ((res[i]>this->startAngle) && (res[i]<this->endAngle)) {
            intersections.push_back(res[i]);
        }
    }
    return true;
}

bool CircularArc::intersection(CircularArc *c2, std::vector<xy> &intersections) {
    double x1=this->c.x;
    double x2=c2->c.x;
    double y1=this->c.y;
    double y2=c2->c.y;
    double r1=this->r;
    double r2=c2->r;
    double d=sqrt(pow(x1-x2, 2)+pow(y1-y2, 2));
    if ((d> r1 + r2 ) || ( fabs(r1 - r2) > d)) {
        return false;
    }
    double z=sqrt( (pow(r1+r2, 2)-d*d)*(d*d-pow(r1-r2, 2) ));
    double m=(x2+x1)/2+(x2-x1)*(r1*r1-r2*r2)/(2*d*d);
    double n=(y2-y1)/(2*d*d)* z;
    double o=(y2+y1)/2+(y2-y1)*(r1*r1-r2*r2)/(2*d*d);
    double p=(x2-x1)/(2*d*d)*z;
    xy res2[2];
    res2[0].x=m+n;
    res2[0].y=o-p;
    res2[1].x=m-n;
    res2[1].y=o+p;

    intersections.clear();

    intersections.push_back(res2[0]);
    if (d != r1 + r2)
        intersections.push_back(res2[1]);
    return true;
}
bool CircularArc::getAproximatedCircleArc(std::vector<xy> & coordinates,int npoints) {
    double step=(this->endAngle-this->startAngle)/(npoints-1);
    for (int i=0;i<npoints;i++) {
        coordinates.push_back(this->polarToXy(this->startAngle+step*i,this->r));
    }
    return true;
}


bool CircularArc::getAproximatedCircleArc(std::vector<xy> &coordinates,double tol) {
    double dtheta=2*acos(1-tol/this->r);
    int divisions=int(ceil((this->endAngle-this->startAngle)/dtheta));
    return this->getAproximatedCircleArc(coordinates, divisions+1);
}

std::string CircularArc::asApproximatedString()  {
    std::vector<xy> lines;
    this->getAproximatedCircleArc(lines);
    std::string res;
    std::stringstream ss;
    for (std::vector<xy>::iterator i=lines.begin(); i!=lines.end(); ++i ) {
        ss<<i->x << " "<<i->y<<";";
    }
    return ss.str();
}

CircularArc::CircularArc() {
    this->r=0;
    this->c.x=0;
    this->c.y=0;
    this->startAngle=0;
    this->endAngle=2*pi;
}
CircularArc::CircularArc(double r, double cx, double cy, double startAngle, double endAngle) {
    this->r=r;
    this->c.x=cx;
    this->c.y=cy;
    this->startAngle=startAngle;
    this->endAngle=endAngle;
}




CircularArc::~CircularArc() {

}

////////////////////////
//CircularString Methods
////////////////////////
ST_CircularString::ST_CircularString() {

}
ST_CircularString::~ST_CircularString() {

}

xy ST_CircularString::getVertex(unsigned int n) {
    if (n<this->arcList.size()) {
        return arcList[n].begin();
    } else if (n==this->arcList.size()) {
        return this->arcList[n].end();
    } else {
        xy t;
        t.x=0;
        t.y=0;
        return t;
    }

}

bool ST_CircularString::clip(Circle c) {
    int nintersections=0;
    std::vector<double> intersections;
    //traverses this strings' arcs finding intersections.
    for_each(arc, this->arcList) {
        double startAngle=NULL;
        arc->polarIntersection(&c,intersections);
        if (intersections.size()==2) {//found two intersections, this arc must be broken in 3 pieces.
            double oldEndAngle=arc->endAngle;
            //first arc
            arc->endAngle=intersections[0];
            //second arc begins on the other arc's end
            double arcBegin, arcEnd;
            arcBegin=c.xyToPolar( arc->polarToXy(intersections[0]) );
            arcEnd=c.xyToPolar( arc->polarToXy(intersections[1]) );
            CircularArc secondArc(c.r,c.c.x,c.c.y,arcBegin, arcEnd);
            this->arcList.insert(++arc,secondArc);
            CircularArc thirdArc(arc->r,arc->c.x,arc->c.y,intersections[1],oldEndAngle);
            this->arcList.insert(++arc,thirdArc);

        } else {
            //check if the starting point is inside the circle
            if (c.Contains(arc->polarToXy(arc->startAngle)) ) {
                arc->startAngle=intersections[0];
            }
            if (c.Contains(arc->polarToXy(arc->endAngle)) ) {
                arc->endAngle=intersections[1];
            }
            if (startAngle) {

            }

        }
    }
}

ST_CurvePolygon::ST_CurvePolygon() {

}

int ST_CurvePolygon::getNRings() {
    return this->rings.size();
}

ST_CircularString* ST_CurvePolygon::getRingN(int n) {
    ST_CircularString* res= &(this->rings[n]);
    return res;
}

bool ST_CurvePolygon::clip(Circle c) {
    std::vector<double> intersections;
    bool intersects=false;
    for_each(ring, this->rings) {

    }
    return true;
}

