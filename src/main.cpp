#include "TePostGIS.h"
#include "TeQuerier.h"
#include "TeQuerierParams.h"
#include "TeAsciiFile.h"
#include "mwvoronoidiagramgenerator.h"
#include "TeGeoProcessingFunctions.h"
#include "tecircle.h"
#include <QtTest>

TeTheme * createTheme(string layername, TeDatabase *db, TeView *view) {
    TeLayer* layer = new TeLayer(layername,db);
    TeTable attTable2;
    layer->getAttrTablesByName(layername,attTable2);
    TeTheme* theme = new TeTheme(layername, layer);
    view->add(theme);
    theme ->addThemeTable(attTable2);
    theme->visibleRep(layer->geomRep());
    if (!theme->save() || !theme->buildCollection())
    {
        cout << "Error trying to create the theme"
               << db->errorMessage() << endl;
        return NULL;
    }
    cout << "Theme created ..\n";
    return theme;
}

bool copyAttributes(TeLayer *diagramLayer, TeTheme *pointsTheme, TeDatabase *db) {
    TeView* view = new TeView("Voronoi");
    view->projection(diagramLayer->projection());
    db->insertView(view);
    TeTheme * diagramTheme=createTheme(diagramLayer->name(),db,view);

    //attribute mapper
    TeGroupingAttr measuresColl;
    //pointsTheme->loadThemeTables ();
    TeAttrTableVector attrTables;
    pointsTheme->getAttTables(attrTables);
    TeAttributeList attrList= attrTables[0].attributeList ();
    for (TeAttributeList::iterator i=attrList.begin(); i!=attrList.end();++i) {
        measuresColl.push_back(make_pair<TeAttributeRep, TeStatisticType>(i->rep_, TeMODE));
    }
    bool result=TeGeoOpAssignByLocationCollect(diagramTheme,pointsTheme,diagramLayer->name(),measuresColl   ,TeINTERSECTS);

    db->deleteTheme(diagramTheme->id());
    db->deleteView(view->id());
    return result;
}


TeLayer* createLayer(const std::string& name, TeDatabase* db, TeProjection* proj, const TeGeomRep& rep)
{
    TeLayer* layer = new TeLayer(name, db, proj);

    TeAttributeList attList;
    TeAttribute at;
    at.rep_.type_ = TeSTRING;
    at.rep_.numChar_ = 255;
    at.rep_.name_ = "object_id";
    at.rep_.isPrimaryKey_ = true;
    attList.push_back(at);

    TeTable attTable(name, attList, "object_id", "object_id");
    if(!layer->createAttributeTable(attTable))
    {
        cout<<"Error creating the new layer table."<<endl;
        db->deleteLayer(layer->id());
        return 0;
    }

    if(!layer->addGeometry(rep))
    {
        cout<<"Error adding geometric representation to new layer."<<endl;
        db->deleteLayer(layer->id());
        return 0;
    }

    return layer;
}

TeLayer * createLayer(const std::string& name, TeDatabase* db, TeProjection* proj, TePolygonSet& ps)
{
    TeLayer* layer = createLayer(name, db, proj, TePOLYGONS);
    if(layer == 0)
        return NULL;

    TeTable& attrTable = layer->attrTables()[0];
    std::string sid; //= Te2String(i);
    for(unsigned int i = 0; i < ps.size(); ++i)
    {
        if (sid!=ps[i].objectId()) {
            sid=ps[i].objectId();
            TeTableRow row;
            row.push_back(sid);
            attrTable.add(row);
        }
    }

    if(!layer->saveAttributeTable(attrTable))
    {
        db->deleteLayer(layer->id());
        return NULL;
    }

    if(!layer->addPolygons(ps))
    {
        db->deleteLayer(layer->id());
        return NULL;
    }

    return layer;
}


bool createLayer(const std::string& name, TeDatabase* db, TeProjection* proj, TeLineSet& ls)
{
    TeLayer* layer = createLayer(name, db, proj, TeLINES);
    if(layer == 0)
        return false;

    TeTable& attrTable = layer->attrTables()[0];
    for(unsigned int i = 0; i < ls.size(); ++i)
    {
        std::string sid = Te2String(i);
        ls[i].objectId(sid);
        TeTableRow row;
        row.push_back(sid);
        attrTable.add(row);
    }

    if(!layer->saveAttributeTable(attrTable))
    {
        cout<<"Error saving the new layer table."<<endl;
        db->deleteLayer(layer->id());
        return false;
    }

    if(!layer->addLines(ls))
    {
        cout<<"Error adding geometries to new layer."<<endl;
        db->deleteLayer(layer->id());
        return false;
    }

    return true;
}

TeTheme* getTheme(TeDatabase * db, const std::string& name)
{
    TeThemeMap& themeMap = db->themeMap();
    TeTheme* theme = 0;
    TeThemeMap::iterator themeIt;
    for(themeIt = themeMap.begin(); themeIt != themeMap.end(); ++themeIt)
    {
        if(themeIt->second->name() == name)
        {
            theme = dynamic_cast<TeTheme*>(themeIt->second);
            break;
        }
    }
    return theme;
}

TeLayer* getLayer(TeDatabase *db, const std::string& name)
{
    TeLayerMap& layerMap = db->layerMap();
    TeLayer* layer = 0;
    TeLayerMap::iterator layerIt;
    for(layerIt = layerMap.begin(); layerIt != layerMap.end(); ++layerIt)
    {
        if(layerIt->second->name() == name)
        {
            layer = layerIt->second;
            break;
        }
    }
    return layer;
}



void testeAlg() {
    mwVoronoiDiagramGenerator *mwvg= new mwVoronoiDiagramGenerator();
    //mwvg->readSites("/home/mauricio/Projetos/mwvd/teste1.csv");
    mwvg->readSites("/home/mauricio/Projetos/mwvd/UrbGDR.csv");
    mwvg->generateVoronoi2();
    //cout<<mwvg->arcList->size()<<endl;
    mwvg->writeCSV("/home/mauricio/Projetos/mwvd/saida.csv");
    delete mwvg;
}

void runTest01() {
    mwVoronoiDiagramGenerator* mwvg= new mwVoronoiDiagramGenerator();
    float * x,*y,*w;
    int n=100;
    //conectando ao banco
    TeDatabase * db=new TePostGIS();
    db->connect("localhost","postgres","teste","terralib",5432);
    TeLayer* layer=new TeLayer("ConsultaUrg09");//TeLayer();"pontos_vendas_pt"
    db->loadLayer(layer);

    //Loading geometries and attributes (geom+attributos)
    bool loadAllAttributes = true;
    bool loadGeometries = true;
    TeQuerierParams querierParams(loadGeometries, loadAllAttributes);
    querierParams.setParams(layer);
    TeQuerier  querier(querierParams);
    querier.loadInstances();
    TeAttributeList attrList = querier.getAttrList();
    //finding weight's attribute
    int weightAttrN=0;
    for (std::vector<TeAttribute>::iterator i=attrList.begin(); i!=attrList.end();++i) {
        if ("qtd_aprese"==i->rep_.name_) {//"DDD_ANO"
            break;
        }
        weightAttrN++;
    }
    n=querier.numElemInstances();
    x=new float[n];
    y=new float[n];
    w=new float[n];
    int numPoints=0;
    TeSTInstance sti;
    string peso;
    while(querier.fetchInstance(sti)) { // for each point
            // Stores on float array
            if(sti.hasPoints())
                {
                    TePointSet pointSet;
                    sti.getGeometry(pointSet);
                    x[numPoints]=pointSet[0].location().x();
                    y[numPoints] = pointSet[0].location().y();
                    //weights
                    sti.getPropertyValue(peso,weightAttrN);
                    w[numPoints]=atof(peso.c_str());
                    numPoints++;
                }

        }
    TeBox b=layer->box();
    mwvg->generateVoronoi(x,y,w,numPoints,b.x1_, b.x2_, b.y1_, b.y2_);
    //mwvg->writeCSV("/home/mauricio/Projetos/mwvd/saida2.csv");
    TePolygonSet ps=*(mwvg->domList);
    cout<<ps.size()<<endl;

    string name="teste1";
    //TeLayer * diagramLayer =createLayer(name,db,layer->projection(),ps);
    //clipping the result layer
    //delete diagramLayer;
    //TeLayer * diagramLayer=new TeLayer("t1");

    //TeTheme* theme=getTheme(db,"ConsultaUrg09");
    //copyAttributes(diagramLayer,theme,db);
}

class TestCircles: public QObject {
    Q_OBJECT
private slots:

};

bool testCircleIntersection() {
    Circle *t1 =  new Circle(1,0,0);
    Circle *t2 =  new Circle(1,1.5,0);

    cout<< "First circle: "<< t1->asString() <<endl;
    std::vector<xy> * res=t1->intersection(t2);
    if (res!=NULL) {
        cout << "Cartesian intersection" <<endl;
        cout << "Intersection 1: "<<(*res)[0].x << "," << (*res)[0].y <<endl;
        cout << "Intersection 2: "<<(*res)[1].x << "," << (*res)[1].y <<endl;
    }
    std::vector<double> * res2=t1->polarIntersection(t2);
    if (res2!=NULL) {
        cout << "Polar intersection" <<endl;
        cout << "Intersection 1: radians:"<<(*res2)[0]<<" : "<< t1->polarToXy((*res2)[0]).x <<","<< t1->polarToXy((*res2)[0]).y << endl;
        cout << "Intersection 2: radians:"<<(*res2)[1]<<" : "<< t1->polarToXy((*res2)[1]).x <<","<< t1->polarToXy((*res2)[1]).y << endl;
    }
    return true;
}



class TestStress: public QObject
{
    Q_OBJECT
public:
    float * newRandomArray(int,double,double);
private slots:
    void randomTest();
};
float * TestStress::newRandomArray(int n, double min, double max) {
    float *arr=new float[n];
}
void TestStress::randomTest() {
    srand((unsigned)time(0));
    //tested sizes
    for (int n=10; n<10000;n*=10) {
        //many samples for each size
        for (int m; m<10;m++) {
            float * x=newRandomArray(n,0,5000);
            float * y=newRandomArray(n,0,5000);
            float * w=newRandomArray(n,0,10);
        }
    }
}


int main()
{

    //runTest01();
    //testCircleIntersection();
    //mwvStressTest();


}


QTEST_MAIN(TestStress)
#include "testqstring.moc"

