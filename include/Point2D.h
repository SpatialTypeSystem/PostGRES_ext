#ifndef POINT2D_H
#define POINT2D_H

#include "Number.h"
#include "RGP.h"
#include <string>
#include <vector>
#include <iterator>

struct Line2DImplStruct;

class Point2D{
private:
	// Fields
	Line2DImplStruct *implStruct;

public:
	// Fields

	// Constructors
	Point2D();
	Point2D(std::vector<RGPPoint2D> listOfPoints);
	Point2D(std::ifstream& file);
	Point2D(std::string listOfPoint2DString);
	~Point2D();

	// Methods
	std::string getPointString();  // Get the point as human readable ASCII string
	static bool isValidPoint();
	bool operator==(const Point2D &p2d);
	bool operator!=(const Point2D &p2d);
	int getNumberPoints();
	std::vector<RGPSegment2D> getBoundingBox();
	bool add(RGPPoint2D rgpp2d);
	template <class T> bool update(T it, RGPPoint2D rgpp2d);
	template <class T> bool remove(T it);
};

#endif //POINT2D_H
