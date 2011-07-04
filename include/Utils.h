 /*!
	\file Utils.h  
	\brief Utility methods for Voronoi plugin.
*/

#ifndef __VORONOIDIAGRAM_PLUGIN_UTILS_H_
#define __VORONOIDIAGRAM_PLUGIN_UTILS_H_

// TerraLib 
#include <TeDataTypes.h>
#include <TeGeometry.h>

// STL
#include <string>
#include <vector>

/** @name Methods related with Geometries.*/
//@{
void Polygonizer(const TeLineSet& ls, TePolygonSet& ps);
bool TeBreakLines(const TeLineSet& ls, TeLineSet& lsBroken);
bool TeBreakLine(const TeLine2D& segment, std::vector<TeCoord2D>& vecCoords, std::vector<TeLine2D>& vecNewLines);
//@}

#endif //__VORONOIDIAGRAM_PLUGIN_UTILS_H_
