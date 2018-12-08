#ifndef SPATIALOPERATIONS_H
#define SPATIALOPERATIONS_H

#include "STO.h"

class SpatialOperations{
public:
	SpatialOperations();
	~SpatialOperations();

	Point2D union(Point2D F, Point2D G);
	Point2D intersection(Point2D F, Point2D G);
	Line2D intersection(Line2D F, Line2D G)
	Region2D intersection(Region2D F, Region2D G);
	Line2D intersection(Region2D F, Line2D G);
private:
	
};

#endif //SPATIALOPERATIONS_H
