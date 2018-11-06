// PRIVATE HEADER FILE

#ifndef POINT2DIMPL_H
#define POINT2DIMPL_H

#include "Number.h"
#include "RGP.h"
#include "Point2D.h"
#include <string>
#include <vector>
#include <iterator>

class Point2DImpl : public Point2D{
private:
	struct Point2DStruct
	{
		std::vector<RGPPoint2D> points;
	};
	
	Point2DStruct mystruct;
};

#endif //POINT2DIMPL_H