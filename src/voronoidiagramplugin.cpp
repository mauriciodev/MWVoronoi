#include <voronoidiagramplugin.h>
#include <VoronoiWindow.h>

//Qt include file
#include <qaction.h>
#include <qmessagebox.h>

VoronoiDiagramPlugin::VoronoiDiagramPlugin(PluginParameters* params):
QObject(),
TViewAbstractPlugin(params)
{
	loadTranslationFiles("voronoi_");
}

VoronoiDiagramPlugin::~VoronoiDiagramPlugin()
{
	end();
}

void VoronoiDiagramPlugin::init()
{
	TerraViewBase* tview = getMainWindow();

    try
	{
		if(tview)
		{
            // Voronoi
			showVoronoiWinAction_ = new QAction(0, "Voronoi", false);
			showVoronoiWinAction_->setMenuText(tr("Voronoi"));
			showVoronoiWinAction_->setText(tr("Voronoi"));
            showVoronoiWinAction_->setIconSet(QIconSet(QPixmap::fromMimeSource("voronoi.png")));

            // Voronoi Ponderado Multiplicativamente 
			showMWVoronoiWinAction_ = new QAction(0, "Voronoi Ponderado Multiplicativamente", false);
			showMWVoronoiWinAction_->setMenuText(tr("Voronoi Ponderado Multiplicativamente"));
			showMWVoronoiWinAction_->setText(tr("Voronoi Ponderado Multiplicativamente"));
            showMWVoronoiWinAction_->setIconSet(QIconSet(QPixmap::fromMimeSource("mwvoronoi.png")));

            // Delaunay
            showDelaunayWinAction_ = new QAction(0, "Delaunay", false);
			showDelaunayWinAction_->setMenuText(tr("Delaunay"));
			showDelaunayWinAction_->setText(tr("Delaunay"));
            showDelaunayWinAction_->setIconSet(QIconSet(QPixmap::fromMimeSource("delaunay.png")));

            QString mainMenuName = "TerraViewPlugins.";
            mainMenuName += tr("Diagrams");
            QPopupMenu* mnu = getPluginsMenu(mainMenuName.latin1());

			if(mnu != 0)
			{
				if(!showVoronoiWinAction_->addTo(mnu))
					throw;
                if(!showMWVoronoiWinAction_->addTo(mnu))
					throw;
                if(!showDelaunayWinAction_->addTo(mnu))
					throw;

			}

			connect(showVoronoiWinAction_, SIGNAL(activated()), this, SLOT(showVoronoiWindow()));
            connect(showMWVoronoiWinAction_, SIGNAL(activated()), this, SLOT(showMWVoronoiWindow()));
            connect(showDelaunayWinAction_, SIGNAL(activated()), this, SLOT(showDelaunayWindow()));
		}
	}
	catch(...)
	{
		QMessageBox::critical(tview, tr("TerraView plug-in error"), tr("Can't create plug-in menu."));
		delete showVoronoiWinAction_;
		showVoronoiWinAction_ = 0;
        delete showMWVoronoiWinAction_;
		showMWVoronoiWinAction_ = 0;
        delete showDelaunayWinAction_;
		showDelaunayWinAction_ = 0;
        
	}
}

void VoronoiDiagramPlugin::end()
{   
	delete showVoronoiWinAction_;
    delete showMWVoronoiWinAction_;
    delete showDelaunayWinAction_;
}

void VoronoiDiagramPlugin::showVoronoiWindow()
{
	VoronoiWindow win(params_);
	win.showWindow();
}

void VoronoiDiagramPlugin::showMWVoronoiWindow()
{
	VoronoiWindow win(params_,MWVoronoi);
	win.showWindow();
}

void VoronoiDiagramPlugin::showDelaunayWindow()
{
	VoronoiWindow win(params_,Delaunay);
	win.showWindow();
}
