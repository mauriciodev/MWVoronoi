//************
//Classe wsite
//************
#include "wsite.h"

wsite::wsite() {
    this->w=0;
    this->x=0;
    this->y=0;
}

wsite::wsite(double x, double y, double w) {
    this->w=w;
    this->x=x;
    this->y=y;
}


wsite::~wsite() {

}

double wsite::wDistance(TePoint p1) {
    return wDistance(p1.elem().x(),p1.elem().y());
}

double wsite::wDistance(double x, double y) {
    return eDistance(x,y)/this->w;
}

double wsite::eDistance(double x, double y) {

    return sqrt(pow(x-this->x,2) + pow(y-this->y,2));
}
double wsite::eDistance(wsite p) {
    return this->eDistance(p.x,p.y);
}


TePoint *wsite::asPoint() {
    TePoint *p = new TePoint(this->x,this->y);
    return p;
}

std::string wsite::AsString() {
    stringstream ss (stringstream::in | stringstream::out);
    ss<<"x:" << FloatToStr(this->x) << " y:" << FloatToStr(this->y) << " w:" << FloatToStr(this->w);
    return ss.str();
}
