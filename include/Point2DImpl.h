#ifndef POINT2DIMPL_H
#define POINT2DIMPL_H

#include <vector>
#include "RGPPoint2D.h"
#include "RGPSegment2D.h"

class Point2DImpl
{
	public:
		Point2DImpl(std::vector<RGPPoint2D> pointVector);
		Point2DImpl();
		Point2DImpl(std::ifstream& file);	// Take input from a file, convert the data into a Point2D  
		Point2DImpl(std::string listOfPoint2DString);	// Read the string as a vector of RGPPoint2D and form a Point2D
		~Point2DImpl();
		class iterator
		{
			public:
				iterator(RGPPoint2D*);
				RGPPoint2D operator*();
				RGPPoint2D operator++(int);
				RGPPoint2D operator++();
				bool operator!=(const iterator&);
				bool operator==(const iterator&);
				RGPPoint2D *ptr;
		};

		// Methods
		std::string getPointString();  // Get the point as human readable ASCII string
		void printAllPoints();
		bool isEmptyPoint();	// Checks if the Point2D object is empty
		bool isValidPoint();	// Checks if the Point2D object is empty
		int getNumberOfPoints();	// Get the total number of RGPPoint2Ds listed
		iterator begin();
		iterator end();
		Point2DImpl getBoundingBox();	

		bool add(RGPPoint2D rgpp2d);	// Adds a new RGPPoint2D to the existing Point2D object
		bool update(iterator it, RGPPoint2D rgpp2d);	// Updates RGPPoint2D existing at specified index
		bool remove(iterator it);	// Removes a RGPPoint2D at specified index

		bool operator==(const Point2DImpl &p2d);	// Override of operator == to check equality of two Point2Ds
		bool operator!=(const Point2DImpl &p2d);	// Override of operator != to check inequality of two Point2Ds
		Point2DImpl operator[](int index);	// Retrieves a RGPPoint2D at specified index
		Point2DImpl operator=(const Point2DImpl &p2dImpl);
	
	private:
		struct Point2DImplStore;
		Point2DImplStore *handle;
		void pointSort(std::vector<RGPPoint2D> &bar);
		void mergeSort(std::vector<RGPPoint2D> &left, std::vector<RGPPoint2D> &right, std::vector<RGPPoint2D> &bars);
		bool parseStringToVectorOfPoints(std::string st);
};

#endif //POINT2DIMPL_H
