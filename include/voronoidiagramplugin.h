#ifndef __VORONOIDIAGRAM_PLUGIN_H_
#define __VORONOIDIAGRAM_PLUGIN_H_

#include <TViewAbstractPlugin.h>

//Qt include files
#include <qobject.h>

class VoronoiDiagramPlugin: public QObject, public TViewAbstractPlugin
{
	Q_OBJECT

public:
	/**	\brief Constructor.
	 *	\param params Plugin parameters.
	 */
	VoronoiDiagramPlugin(PluginParameters* params);

	/**	\brief Destructor.
	 */
	~VoronoiDiagramPlugin();

	/**	\brief Initializer method.
	 */
	void init();

	/**	\brief Finalizer method.
	 */
	void end();

protected slots:

	void showVoronoiWindow();
    void showDelaunayWindow();
    void showMWVoronoiWindow();


protected:

	QAction* showVoronoiWinAction_;
    QAction* showDelaunayWinAction_;
    QAction* showMWVoronoiWinAction_;
};

#endif //__VORONOIDIAGRAM_PLUGIN_H_