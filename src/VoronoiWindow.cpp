// Voronoi
#include "VoronoiWindow.h"
#include "VoronoiDiagramGenerator.h"
#include "mwvoronoidiagramgenerator.h"
#include "Utils.h"

// TerraLib
#include <help.h>
#include <TeDatabase.h>
#include <TeVectorRemap.h>
#include <TeWaitCursor.h>
#include <TeQuerier.h>
#include <TeQuerierParams.h>
#include <TeGeoProcessingFunctions.h>

// Qt
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qtabwidget.h>

struct XYOrderFunctor
{
    bool operator()(const TePoint& p1, const TePoint& p2) const
    {
        if(p1.location().x_ < p2.location().x_)
            return true;
        else if(p1.location().x_ > p2.location().x_)
            return false;

        if(p1.location().y_ < p2.location().y_)
            return true;
        else if(p1.location().y_ > p2.location().y_)
            return false;

        return false;
    }
};

VoronoiWindow::VoronoiWindow(PluginParameters* pp, const enumDiagramType diagramType): 
UIVoronoi(0, "VoronoiWindow"),
plugin_params_(pp)
{
    /*! Selects what aditional parameters each diagram needs.*/
    weightGroupBox->hide();
    this->diagramType=diagramType;
    if(diagramType==Delaunay) {
        setCaption("Delaunay");
        boxButtonGroup->hide();
    }
    if(diagramType==MWVoronoi) {
        setCaption("Multiplicatively Weighted Voronoi");
        weightGroupBox->show();
    }
}

VoronoiWindow::~VoronoiWindow()
{}

void VoronoiWindow::generateLinesCheckBox_clicked()
{
    layerLinesButtonGroup->setEnabled(generateLinesCheckBox->isChecked());
}

void VoronoiWindow::themeComboBox_activated(const QString& themeName)
{
    TeTheme* theme = getTheme(themeName.latin1());
    if(theme == 0)
        return;
    // Updates the combo box with delimiters...
    TeLayer* layer = theme->layer();
    boxComboBox->setCurrentText(layer->name().c_str());
    
    // Lists attributes on the weightComboBox
    weightComboBox->clear();
    //if (text=="") text=themeComboBox->currentText().latin1();
    TeTable *attrTable = &layer->attrTables()[0];
    TeAttributeList * attrList=&attrTable->attributeList();
    for (std::vector<TeAttribute>::iterator i=attrList->begin(); i!=attrList->end();++i) {
        cout<<i->rep_.name_<<endl;
        weightComboBox->insertItem(i->rep_.name_);
    }
}

void VoronoiWindow::helpPushButton_clicked()
{
    Help* help = new Help(this, "help", false);
	help->init(""); // TODO: Voronoi.html and Delaunay.html
	if(help->erro_ == false)
	{
		help->show();
		help->raise();
	}
	else
		delete help;
}

void VoronoiWindow::okPushButton_clicked()
{
    std::string layerName = layerNameLineEdit->text().utf8();	
	if(layerName.empty())
	{
		QMessageBox::information(this, tr("Information"), tr("Please, define a name to result Layer."));
        voronoiTabWidget->setCurrentPage(0);
        layerNameLineEdit->setFocus();
		return;
	}

    std::string layerLinesName;
    if(generateLinesCheckBox->isChecked())
    {
        layerLinesName = layerLinesLineEdit->text().ascii();
        if(layerLinesName.empty())
	    {
		    QMessageBox::information(this, tr("Information"), tr("Please, define a name to Layer of Lines."));
            voronoiTabWidget->setCurrentPage(1);
            layerLinesLineEdit->setFocus();
		    return;
	    }
    }

    if(!isLayerNameValid(layerName))
    {
        voronoiTabWidget->setCurrentPage(0);
        layerNameLineEdit->setFocus();
        return;
    }

    if(!isLayerNameValid(layerLinesName))
    {
        voronoiTabWidget->setCurrentPage(1);
        layerLinesLineEdit->setFocus();
        return;
    }

    if(layerName == layerLinesName)
    {
        QMessageBox::information(this, tr("Information"), tr("Please, define names differents to Layer result and Layer of Lines."));
	    return;
    }

	TeDatabase* db = plugin_params_->getCurrentDatabasePtr();
    TeTheme* theme = getTheme(themeComboBox->currentText().latin1());
	if(theme == 0)
	{
		QMessageBox::critical(this, tr("Error"), tr("Error getting the input Theme."));
		return;
	}
    
    TePrecision::instance().setPrecision(TeGetPrecision(theme->layer()->projection()));
    
    TeTheme *themeDelimiter = getTheme(boxComboBox->currentText().latin1());
    if(themeDelimiter == 0)
    {
        QMessageBox::critical(this, tr("Error"), tr("Error getting the delimiter Layer."));
		return;
    }

    // Verifies is the box chosen is valid
    TeBox b = themeDelimiter->layer()->box();
    TeProjection* projFrom = themeDelimiter->layer()->projection();
    TeProjection* projTo = theme->layer()->projection();
    if(!((*projFrom) == (*projTo))) // need remap?
        b = TeRemapBox(b, projFrom, projTo);

    TeBox& inputBox = theme->layer()->box();
    if(!TeIntersects(b, inputBox))
    {
        QMessageBox::information(this, tr("Information"), tr("The box chosen do not intercepts the input Theme. Please, try another."));
        voronoiTabWidget->setCurrentPage(1);
        boxComboBox->setFocus();
        return;
    }
    
    //preparing to read the layer
    bool loadAllAttributes=false;
    if (diagramType==MWVoronoi) loadAllAttributes = true;
    bool loadGeometries = true;
    TeQuerierParams querierParams(loadGeometries, loadAllAttributes);
    querierParams.setParams(theme->layer());
    TeQuerier  querier(querierParams);
    querier.loadInstances();
    //finding weight's attribute
    TeAttributeList attrList = querier.getAttrList();
    int weightAttrN=0;
    if (diagramType==MWVoronoi) {
        for (std::vector<TeAttribute>::iterator i=attrList.begin(); i!=attrList.end();++i) {
            if (weightComboBox->currentText()==i->rep_.name_) {
                break;
            }
            weightAttrN++;
        }    
    }
    int n=querier.numElemInstances();

    if(n==0)
    {
        QMessageBox::critical(this, tr("Error"), tr("Error getting the points of input Theme."));
        return;
    }

    TeWaitCursor wait;

    // Converts x,y to a float array in order to pass to VoronoiDiagramGenerator class
    float* x = new float[n];
	float* y = new float[n];
    //pointers for weighted voronoi
    float* w;
    int numPoints;
    w= new float[n];
    numPoints = 0;
    TeSTInstance sti;
    string peso;
    //TePoint pointBefore(0,0);
    while(querier.fetchInstance(sti)) { // for each point
        // Stores on float array
        if(sti.hasPoints())
            {
                TePointSet pointSet;
                //reading geometry
                sti.getGeometry(pointSet);
                x[numPoints] = pointSet[0].location().x();
                y[numPoints] = pointSet[0].location().y();
    
                //reading weight
                if (diagramType==MWVoronoi) {
                    stringstream ss;
                    sti.getPropertyValue(peso,weightAttrN);
                    ss<<peso;
                    ss>>w[numPoints];
                }                    
                numPoints++;
            }
        }
    //sort the vertexes for delaunay and voronoi
    if (diagramType!=MWVoronoi) {
        TePointSet ps;
        for (int i=0; i<numPoints;i++){
            ps.add(TePoint(x[i],y[i]));
        }
        sort(ps.begin(), ps.end(), XYOrderFunctor()); // need to compare equals points
        x[0] = ps[0].location().x_;
        y[0] = ps[0].location().y_;
        numPoints=1;
        for(unsigned int i = 1; i < ps.size(); ++i) { // for each point
            if(TeEquals(ps[i-1], ps[i])) // Do not consider equals
                continue;
            // Stores on float array
    		x[numPoints] = ps[i].location().x_;
    		y[numPoints] = ps[i].location().y_;
            numPoints++;
    	}
    }
    
    
    // Generates the Voronoi Diagram
    TeLineSet ls;
	float x1, y1, x2, y2;
    VoronoiDiagramGenerator * vdg;
    mwVoronoiDiagramGenerator *mwvdg;
    if(this->diagramType==Voronoi) {
        vdg= new VoronoiDiagramGenerator();
        vdg->generateVoronoi(x, y, numPoints, b.x1_, b.x2_, b.y1_, b.y2_, 0.0);
        vdg->resetVertexPairIterator();
        vdg->resetDelaunayEdgesIterator();
        while(vdg->getNextVertexPair(x1, y1, x2, y2))
        {
            if(x1 == x2 && y1 == y2)
                continue;

	        TeLine2D l;
	        l.add(TeCoord2D(x1, y1));
	        l.add(TeCoord2D(x2, y2));
	        ls.add(l);
        }
    }	
    
    if(this->diagramType==Delaunay)
    {
        vdg= new VoronoiDiagramGenerator();
        vdg->setGenerateDelaunay(true);
        vdg->setGenerateVoronoi(false);
        vdg->generateVoronoi(x, y, numPoints, b.x1_, b.x2_, b.y1_, b.y2_, 0.0);
        //creates the output lineset
        while(vdg->getNextDelaunay(x1, y1, x2, y2))
        {
            if(x1 == x2 && y1 == y2)
                continue;

	        TeLine2D l;
	        l.add(TeCoord2D(x1, y1));
	        l.add(TeCoord2D(x2, y2));
	        ls.add(l);
        }
    }
    
    
    TePolygonSet diagram; //MWVoronoi already creates the polygons.
    
    if(this->diagramType==MWVoronoi) {
        
        mwvdg= new mwVoronoiDiagramGenerator();
        mwvdg->generateVoronoi(x, y, w, numPoints, b.x1_, b.x2_, b.y1_, b.y2_);
        mwvdg->writeCSV("/home/mauricio/Projetos/mwvd/saida_terraview.csv");
        diagram=*mwvdg->domList;
    }
   
	
	
	delete [] x;
	delete [] y;
    delete [] w;


    if (diagramType!=MWVoronoi){
        if(ls.empty())
        {
            QMessageBox::information(this, tr("Information"), tr("No line of Voronoi Diagram crosses the box chosen. Please, try another."));
            voronoiTabWidget->setCurrentPage(1);
            boxComboBox->setFocus();
            wait.resetWaitCursor();
            return;
        }
    }


    // Adding the lines of box in order to cut the diagram
    if (this->diagramType==Voronoi)
    {
        TePolygon pbox = TeMakePolygon(ls.box());
        TeLinearRing& ring = pbox[0];
        for(unsigned int i = 0; i < ring.size() - 1; ++i)
        {
            TeLine2D line;
            line.add(TeCoord2D(ring[i]));
            line.add(TeCoord2D(ring[i+1]));
            ls.add(line);
        }
    }
    
    TeLineSet fixedLines;
    
    if (diagramType!=MWVoronoi){
        TeBreakLines(ls, fixedLines); 
    
        if(generateLinesCheckBox->isChecked())
            createLayer(layerLinesLineEdit->text().latin1(), db, theme->layer()->projection(), fixedLines);
    
        // Adds identifiers to polygonizer control...
        for(unsigned int i = 0; i < fixedLines.size(); ++i)
        {
            std::string sid = Te2String(i);	
    	    fixedLines[i].objectId(sid);
        }
    
        // Gets Polygons!
        
        Polygonizer(fixedLines, diagram);
    }

    TeLayer * diagramLayer=createLayer(layerNameLineEdit->text().latin1(), db, theme->layer()->projection(), diagram);
    if (diagramType==MWVoronoi) delete mwvdg;
    
    if(!diagramLayer)
    {
        wait.resetWaitCursor();
        return;
    }

    //if the layers are not equal, I should to clip the diagram
    if (theme->name()!=themeDelimiter->name()) {
        clipLayer(diagramLayer,themeDelimiter,db);
    } 

    wait.resetWaitCursor();

    if(this->diagramType!=Delaunay)
	    QMessageBox::information(this, tr("Information"), tr("The Voronoi Diagram was generated successfully!"));
    else
        QMessageBox::information(this, tr("Information"), tr("The Delaunay Diagram was generated successfully!"));

    close();

    plugin_params_->updateTVInterface();
}

void VoronoiWindow::showWindow()
{
	if(plugin_params_->getCurrentDatabasePtr() == 0)
	{
		QMessageBox::critical(this, tr("Error"), tr("Connect to a database first."));
		return;
	}

	themeComboBox->clear();

	TeThemeMap& themeMap = plugin_params_->getCurrentDatabasePtr()->themeMap();
	TeThemeMap::iterator themeIt;
    std::string delimiter;
	for(themeIt = themeMap.begin(); themeIt != themeMap.end(); ++themeIt)
	{
		TeTheme* t = dynamic_cast<TeTheme*>(themeIt->second);
		if(t == 0)
			continue;
		if(t->layer()->geomRep() & TePOINTS)
        {
            if(delimiter.empty())
                delimiter = t->layer()->name();
			themeComboBox->insertItem(QString(t->name().c_str()));
        }
	}

    if(themeComboBox->count() == 0)
    {
        QMessageBox::information(this, tr("Information"), tr("No Theme with point representation found."));
		return;
    }

    TeLayerMap& layerMap = plugin_params_->getCurrentDatabasePtr()->layerMap();
	TeLayerMap::iterator layerIt;
	for(layerIt = layerMap.begin(); layerIt != layerMap.end(); ++layerIt)
        boxComboBox->insertItem(QString(layerIt->second->name().c_str()));
    
    boxComboBox->setCurrentText(delimiter.c_str());

	exec();
}

TeLayer* VoronoiWindow::createLayer(const std::string& name, TeDatabase* db, TeProjection* proj, const TeGeomRep& rep)
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
		QMessageBox::critical(this, tr("Error"), tr("Error creating the new layer table."));
		db->deleteLayer(layer->id());
        return 0;
	}

    if(!layer->addGeometry(rep))
	{
		QMessageBox::critical(this, tr("Error"), tr("Error adding geometric representation to new layer."));
		db->deleteLayer(layer->id());
		return 0;
	}

    return layer;
}

bool VoronoiWindow::createLayer(const std::string& name, TeDatabase* db, TeProjection* proj, TeLineSet& ls)
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
	    QMessageBox::critical(this, tr("Error"), tr("Error saving the new layer table."));
	    db->deleteLayer(layer->id());
	    return false;
    }

    if(!layer->addLines(ls))
    {
	    QMessageBox::critical(this, tr("Error"), tr("Error adding geometries to new layer."));
	    db->deleteLayer(layer->id());
	    return false;
    }

    return true;
}
    
TeLayer * VoronoiWindow::createLayer(const std::string& name, TeDatabase* db, TeProjection* proj, TePolygonSet& ps)
{
    TeLayer* layer = createLayer(name, db, proj, TePOLYGONS);
    if(layer == 0)
        return NULL;

    TeTable& attrTable = layer->attrTables()[0];
    std::string sid; //= Te2String(i);
    for(unsigned int i = 0; i < ps.size(); ++i)
    {
        if (sid=="") sid=Te2String(i); //in case there is no id, create one.
        if (sid!=ps[i].objectId()) { //in case the id is equal to the last one, it's a multipolygon
            sid=ps[i].objectId();
            TeTableRow row;
            row.push_back(sid);
            attrTable.add(row);
        }
    }

    if(!layer->saveAttributeTable(attrTable))
    {
	    QMessageBox::critical(this, tr("Error"), tr("Error saving the new layer table."));
	    db->deleteLayer(layer->id());
	    return NULL;
    }

    if(!layer->addPolygons(ps))
    {
	    QMessageBox::critical(this, tr("Error"), tr("Error adding geometries to new layer."));
	    db->deleteLayer(layer->id());
	    return NULL;
    }
    
    return layer;
}

TeTheme* VoronoiWindow::getTheme(const std::string& name)
{
    TeDatabase* db = plugin_params_->getCurrentDatabasePtr();
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

TeLayer* VoronoiWindow::getLayer(const std::string& name)
{
    TeDatabase* db = plugin_params_->getCurrentDatabasePtr();
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

bool VoronoiWindow::isLayerNameValid(const std::string& name)
{
    TeDatabase* db = plugin_params_->getCurrentDatabasePtr();
    if(db->layerExist(name))
    {
        QMessageBox::information(this, tr("Information"), tr("The Layer name already exist. Please, try another."));
        return false;
    }

    bool changed;
    std::string errorMessage;
    TeCheckName(name, changed, errorMessage);
    if(changed)
    {
        QString msg = tr("The Layer name is invalid: \n") + errorMessage.c_str();
		msg += "\n" + tr("Please, try another.");
        QMessageBox::information(this, tr("Information"), msg);
        return false;
    }

    return true;
}

TeTheme * VoronoiWindow::createTheme(string layername, TeDatabase *db, TeView *view) {
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

bool VoronoiWindow::clipLayer(TeLayer *diagramLayer, TeTheme *themeDelimiter, TeDatabase *db) {
    TeView* view = new TeView("Voronoi");
    view->projection(diagramLayer->projection());
    db->insertView(view);
    TeTheme * diagramTheme=createTheme(diagramLayer->name(),db,view);

    TeBox bInvalid;
    TeLayer *clippedLayer=new TeLayer((diagramLayer->name()+"_clipped"), db, bInvalid, diagramLayer->projection());
    bool result=TeGeoOpOverlayIntersection(clippedLayer,diagramTheme,themeDelimiter,TeAll,TeAll,true);
    //delete clippedLayer;
    db->deleteTheme(diagramTheme->id());
    db->deleteView(view->id());
    return result;
}

bool VoronoiWindow::copyAttributes(TeLayer *diagramLayer, TeTheme *pointsTheme, TeDatabase *db) {
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