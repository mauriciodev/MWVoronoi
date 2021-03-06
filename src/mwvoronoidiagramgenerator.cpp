/*
Multiplicatively Weighted Voronoi Diagram
Copyright (C) 2011  Instituto Nacional de Pesquisas Espaciais

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "mwvoronoidiagramgenerator.h"
//********************************
//Classe mwVoronoiDiagramGenerator
//********************************

mwVoronoiDiagramGenerator::mwVoronoiDiagramGenerator(  ) 
{
    this->siteList=new vector<wsite>;
    this->domList=new TePolygonSet;

}

mwVoronoiDiagramGenerator::~mwVoronoiDiagramGenerator(  ) 
{
    delete this->siteList;
    delete this->domList;
    //delete this->areaBox;
}

void mwVoronoiDiagramGenerator::printSites() {
    for (vector<wsite>::iterator i=this->siteList->begin(); i!=this->siteList->end();++i) {
        cout << i->AsString() <<endl;
    }

}


TePolygon *mwVoronoiDiagramGenerator::apolonio(wsite s1, wsite s2, int nsides) {
    double w1=s1.w;
    double w2=s2.w;
    if(w1==w2) w2+=w2/1000;
    double cx=(w1*w1*s2.x-w2*w2*s1.x)/(w1*w1-w2*w2);
    double cy=(w1*w1*s2.y-w2*w2*s1.y)/(w1*w1-w2*w2);
    TePoint *center = new TePoint(cx,cy);
    double r=w1*w2*s1.eDistance(s2)/(w1*w1-w2*w2);
    if (r<0) r=r*-1;
    TePolygon *circle=new TePolygon();
    TeBUFFERREGION::TeBufferRegion(center->elem(),r,nsides,*circle);
    /*Testando a propriedade das distancias serem iguais*/
    wsite teste(circle->begin()->begin()->x(),circle->begin()->begin()->y(),1); //primeiro ponto do circulo
    double x=circle->begin()->begin()->x();
    double y=circle->begin()->begin()->y();
    x=cx+r;
    y=cy;
    delete center;
    return circle;
}


TePolygon * mwVoronoiDiagramGenerator::boxFromExtent(double xmin, double xmax,double ymin,double ymax) {
    TeLine2D line2;
    line2.add(TeCoord2D(xmin,ymin));
    line2.add(TeCoord2D(xmin,ymax));
    line2.add(TeCoord2D(xmax,ymax));
    line2.add(TeCoord2D(xmax,ymin));
    line2.add(TeCoord2D(xmin,ymin));

    TeLinearRing r2(line2);
    TePolygon * p =new TePolygon();
    p->add(r2);
    return p;
}

bool mwVoronoiDiagramGenerator::generateVoronoi(float *xValues, float *yValues,  float *wValues, int numPoints,double minX, double maxX, double minY, double maxY, TeLineSet & breakLines) {
    this->areaBox=boxFromExtent(minX*0.999,maxX*1.001,minY*0.999,maxY*1.001);
    //carregando os geradores:
    wsite * site;
    for (int i=0;i<numPoints;i++) {
        site=new wsite(xValues[i],yValues[i],wValues[i]);
        this->siteList->push_back(*site);
    }

    bool result=generateVoronoi2();
    delete this->areaBox;
    return result;
}

bool mwVoronoiDiagramGenerator::generateVoronoi2() {
    int polId=0;
    TePolygonSet *area=new TePolygonSet;
    TePolygonSet *circleSet,*saida,*region;
    TePolygon *circle;
    area->add(*this->areaBox);
    /*!The goal of each iteration is to construct the dominance of each vertex. */
    for (vector<wsite>::iterator i=this->siteList->begin();i!=this->siteList->end();++i) {
        //loop for every generator
        region=new TePolygonSet();
        region->copyElements(*area); //region of dominance, starts as the whole area minus the already dominated areas
        for (vector<wsite>::iterator j=this->siteList->begin();j!=this->siteList->end();++j) {
            //loop for every generator not analised yet;
            if (i!=j) {
                //every arc of the region is a piece of the appolonius circle between the two generators.
                circle=apolonio(*i,*j);
                circleSet=new TePolygonSet();
                circleSet->add(*circle);
                if (i->w>j->w) {
                    //w_i > w_j then j is dominated by i, I must invert the area
                    saida=new TePolygonSet();
                    TeOVERLAY::TeDifference(*area,*circleSet,*saida);
                    delete circleSet;
                    circleSet=saida; //saida was just to store the result.
                }
                //To be the dominance, the region must be the intersection of every dominance_i
                saida=new TePolygonSet();
                TeOVERLAY::TeIntersection(*region,*circleSet,*saida);
                delete region;
                region=saida;
                delete circle;
                delete circleSet;
            }
        }
        //cout <<polId<<endl;
        //when finished j, one dominance is done. let's write it out.
        TePolygon t;
        string objectId;
        if (region->size()>0) {
            stringstream ss;
            ss<<polId;
            for (TePolygonSet::iterator pi=region->begin(); pi!=region->end();++pi) {
                pi->geomId(polId);
                pi->objectId(ss.str());
                this->domList->add(*pi);
            }

        }
        polId++;
        delete region;
    }
    if (this->domList->size()>0) {
        return true;
    } else {
        return false;
    }
}


void mwVoronoiDiagramGenerator::readSites(const char * filename) {
    std::string line;
    std::vector<std::string> coordlist;
    float x,y,w;
    std::ifstream myfile (filename);
    if (myfile.is_open())
    {
        while (! myfile.eof() )
        {
            std::getline (myfile,line);
            std::cout << line << std::endl;

            StringToVector(line,coordlist,",");
            if (coordlist.size()>0 ){
                w=StrToFloat(coordlist[0]);
                x=StrToFloat(coordlist[1]);
                y=StrToFloat(coordlist[2]);
                this->siteList->push_back(wsite(x,y,w));
            }
        }
        myfile.close();
    }
    else std::cout << "Nao foi possivel abrir o arquivo"<<std::endl;
    cout << "Foram lidos " << this->siteList->size() << " vertices."<<endl;
}
void mwVoronoiDiagramGenerator::writeCSV(const char * filename) {
    std::ofstream myfile;
    myfile.open (filename);
    myfile << "X , Y" <<std::endl;
    /*for (TeLineSet::iterator arc=this->arcList->begin(); arc!=this->arcList->end();++arc) {
        for (TeLine2D::iterator p=arc->begin();p!=arc->end();++p){
            myfile << p->x() << ","<<p->y()<<std::endl;
        }
    }*/
    for (TePolygonSet::iterator area=this->domList->begin(); area!=this->domList->end();++area) {
        cout << area->size() << endl;
        TePolygon::iterator arc= area->begin();
        TeLinearRing::iterator p=arc->begin();
        for (TeLinearRing::iterator p=arc->begin();p!=arc->end();++p){
            myfile << p->x() << ","<<p->y()<<std::endl;
        }
    }
    myfile.close();
}
