/*!
	\file Utils.cpp 
	\brief Utility methods for Voronoi plugin.
*/

// Voronoi
#include "Utils.h"

// TerraLib
#include <TeDatabase.h>
#include <TeRTree.h>
#include <TeOverlay.h>
#include <TeIntersector.h>

struct DistanceOrderFunctor
{
    TeCoord2D _reference;
    DistanceOrderFunctor(const TeCoord2D& reference)
    {
        _reference = reference;
    }

    bool operator()(const TeCoord2D& c1, const TeCoord2D& c2) const
    {
        double distance1 = TeDistance(_reference, c1);
        double distance2 = TeDistance(_reference, c2);

        if(distance1 < distance2)
            return true;

        return false;
    }
};

bool TeBreakLine(const TeLine2D& segment, std::vector<TeCoord2D>& vecCoords, std::vector<TeLine2D>& vecNewLines)
{
	if(segment.size() != 2)
		return false;

	DistanceOrderFunctor func(segment[0]);

	sort(vecCoords.begin(), vecCoords.end(), func);

	TeLine2D newLine;
	newLine.add(TeCoord2D(segment[0]));
	for(unsigned int i = 0; i < vecCoords.size(); ++i)
	{
		if(TeEquals(newLine[0], vecCoords[i]))
			continue;

		newLine.add(TeCoord2D(vecCoords[i]));
		vecNewLines.push_back(newLine);

		newLine = TeLine2D();
		newLine.add(TeCoord2D(vecCoords[i]));
	}

	newLine.add(TeCoord2D(segment[1]));

    if(TeLength(newLine) > 0.0)
    	vecNewLines.push_back(newLine);

	return true;
}

bool TeBreakLines(const TeLineSet& ls, TeLineSet& lsBroken)
{
    // Indexing...
	TeSAM::TeRTree<unsigned int> index(ls.box());
	TeSAM::TeRTree<unsigned int> indexNew(ls.box());
	TeLineSet lsSegments;
	for(unsigned int i = 0; i < ls.size(); ++i)
	{
		TeLine2D& line = ls[i];
		for(unsigned int j = 0; j < line.size() - 1; ++j)
		{
			TeLine2D newLine;
			newLine.add(line[j]);
			newLine.add(line[j+1]);

			lsSegments.add(newLine);
            
			index.insert(newLine.box(), lsSegments.size() - 1);
		}
	}

    for(unsigned int i = 0; i < lsSegments.size(); ++i) // for each line
	{
		TeLine2D& line = lsSegments[i];

		std::vector<unsigned int> vecReport;
		index.search(line.box(), vecReport);

        // first, broken the lines in all possible points
		std::vector<TeCoord2D> vecCoordsToAdd;
		for(unsigned int j = 0; j < vecReport.size(); ++j)
		{
			TeLine2D& candidateLine = ls[vecReport[j]];
			if(TeEquals(line, candidateLine))
				continue;
			
			TeINTERSECTOR2::TeBoundaryIP vecCoords;
			TeSegmentIntersectionType type;
			if(TeINTERSECTOR2::TeIntersection(line[0], line[1], candidateLine[0], candidateLine[1], vecCoords, type))
			{
				vecCoordsToAdd.push_back(vecCoords.coords_[0]);
				if(vecCoords.coords_.size() == 2)
					vecCoordsToAdd.push_back(vecCoords.coords_[1]);
			}
		}

		std::vector<TeLine2D> vecLines;
		TeBreakLine(line, vecCoordsToAdd, vecLines);

		for(unsigned int j = 0; j < vecLines.size(); ++j)
		{
			TeLine2D& candidateLine = vecLines[j];

			std::vector<unsigned int> vecReport2;
			if(indexNew.search(candidateLine.box(), vecReport2))
			{
				bool canAdd = true;
				for(unsigned int k = 0; k < vecReport2.size(); ++k)
				{
					if(TeEquals(candidateLine, lsBroken[vecReport2[k]]))
					{
						canAdd = false;
						break;
					}
				}
				if(canAdd == true)
				{
					lsBroken.add(candidateLine);
					indexNew.insert(candidateLine.box(), lsBroken.size()-1);
				}
			}
			else
			{
				lsBroken.add(candidateLine);
				indexNew.insert(candidateLine.box(), lsBroken.size()-1);
			}
		}
	}

	return true; // yeah!
}

double Theta(const TeCoord2D& c1, const TeCoord2D& c2)
{
	register double dx = c2.x() - c1.x();
	register double ax = fabs(dx);
	register double dy = c2.y() - c1.y();
	register double ay = fabs(dy);
	register double t = 0.0;

	if((dx == 0.0) && (dy == 0.0))
		t = 0.0;
	else
		t = dy / (ax + ay);

	if(dx < 0.0)
		t = 2 - t;
	else
		if(dy < 0.0)
			t = 4.0 + t;

	return t * 90.0;
}

void Polygonizer(const TeLineSet& ls, TePolygonSet& ps)
{
    std::map<std::string, bool> mapUsed;

    // Indexing...
    TeSAM::TeRTree<unsigned int> indexRTree(ls.box());
	for(unsigned int i = 0; i < ls.size(); ++i)
	{
		TeLine2D& line = ls[i];

        TeCoord2D c1(line[0]);
        TeCoord2D c2(line[1]);

        TeBox b1(c1, c1);
        TeBox b2(c2, c2);

        indexRTree.insert(b1, i);
        indexRTree.insert(b2, i);

        mapUsed[line.objectId()] = false;
	}    

    double p = TePrecision::instance().precision();
    for(unsigned int i = 0; i < ls.size(); ++i)
	{
        TeLine2D& currentLine = ls[i];

        if(mapUsed[currentLine.objectId()] == true)
            continue;

        std::vector<std::string> vecIdsUsed; 
        vecIdsUsed.push_back(currentLine.objectId());

        TeLinearRing ring;
        ring.add(TeCoord2D(currentLine[0]));
		ring.add(TeCoord2D(currentLine[1]));
        
        while(true)
        {
            TeCoord2D lastCoord = ring[ring.size() - 1];
            
            TeBox boxToSearch = TeBox(lastCoord.x() - p, lastCoord.y() - p,
								      lastCoord.x() + p, lastCoord.y() + p);

            std::vector<unsigned int> vecIndexes;
            indexRTree.search(boxToSearch, vecIndexes);

            if(vecIndexes.size() == 1)
                break;

			TeLine2D lastLine;
			lastLine.add(ring[ring.size() - 2]);
			lastLine.add(lastCoord);

            double theta = Theta(lastLine[1], lastLine[0]);
            int indexToUse = -1;
            double minAngle = TeMAXFLOAT;
    	    for(unsigned int j = 0; j < vecIndexes.size(); ++j)
		    {
			    unsigned int pos = vecIndexes[j];
			    TeLine2D& nextLine = ls[pos];

                if(TeEquals(lastLine, nextLine))
                    continue;

                double nextTheta = 0.0;
				if(TeEquals(lastCoord, nextLine[0]))
					nextTheta = Theta(nextLine[0],  nextLine[1]); 
                else
					nextTheta = Theta(nextLine[1],  nextLine[0]);

			    double angle = 0.0;
				if(theta > nextTheta)
					angle = theta - nextTheta;
                else
					angle = 360 + theta - nextTheta;

				if(angle < minAngle)
				{
					indexToUse = pos;
					minAngle = angle;
				}
            }
            
            if(indexToUse == -1)
				break;

            TeLine2D& lineFound = ls[indexToUse];
             
			if(TeEquals(lineFound[0], lastCoord))
            {
                ring.add(TeCoord2D(lineFound[1]));
                vecIdsUsed.push_back(lineFound.objectId());
            }
			else
				ring.add(TeCoord2D(lineFound[0]));

			if(ring.isRing())
			{
				TePolygon polygon;
				polygon.add(ring);

                for(unsigned int j = 0; j < vecIdsUsed.size(); ++j)
                    mapUsed[vecIdsUsed[j]] = true;

                if(TeOrientation(ring) == TeCOUNTERCLOCKWISE)
                    ps.add(polygon);

				break;
			}
        }
    }
}
