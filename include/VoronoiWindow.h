#ifndef __VORONOIDIAGRAM_WINDOW_H_
#define __VORONOIDIAGRAM_WINDOW_H_
  
#include "UIVoronoi.h"

// TerraLib
#include <PluginParameters.h>
#include <TeDataTypes.h>
#include <stdlib.h>

// forward declarations
class TeDatabase;
class TeLayer;
class TeLineSet;
class TePolygonSet;
class TeProjection;
class TeTheme;

enum enumDiagramType {
        Voronoi,
        MWVoronoi,
        Delaunay,
    };

class VoronoiWindow : public UIVoronoi
{
    Q_OBJECT

public:
   
    VoronoiWindow(PluginParameters* pp, enumDiagramType=Voronoi);
    
    ~VoronoiWindow();
    
public slots:

    void generateLinesCheckBox_clicked();
    void themeComboBox_activated(const QString& themeName);
	void okPushButton_clicked();
    void helpPushButton_clicked();

    void showWindow();

private:

    TeLayer* createLayer(const std::string& name, TeDatabase* db, TeProjection* proj, const TeGeomRep& rep);

    bool createLayer(const std::string& name, TeDatabase* db, TeProjection* proj, TeLineSet& ls);
    
    TeLayer * createLayer(const std::string& name, TeDatabase* db, TeProjection* proj, TePolygonSet& ps);
    TeTheme * createTheme(std::string layername, TeDatabase *db, TeView *view);
    bool clipLayer(TeLayer *diagramLayer, TeTheme *themeDelimiter, TeDatabase *db);
    bool copyAttributes(TeLayer *diagramLayer, TeTheme *points, TeDatabase *db);
    TeTheme* getTheme(const std::string& name);
    TeLayer* getLayer(const std::string& name);
    std::vector<std::string> listAttributes(TeTheme* theme);
    bool isLayerNameValid(const std::string& name);
		
private:

    PluginParameters* plugin_params_;
    enumDiagramType diagramType;
};

#endif // __VORONOIDIAGRAM_WINDOW_H_
