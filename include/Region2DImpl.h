#ifndef Region2DImpl_H
#define Region2DImpl_H

#include "Number.h"
#include "RGP.h"
#include <string>
#include <vector>

class Region2DImpl
{
public:
	// Constructors
	Region2DImpl(std::string listOfRegion2DString);
	~Region2DImpl();

	class iteratorforFaces
	{
		public:
			iteratorforFaces(std::vector<RGPAnnotatedHalfSegment2D>*);
			std::vector<RGPAnnotatedHalfSegment2D> operator*();
			std::vector<RGPAnnotatedHalfSegment2D> operator++(int);
			std::vector<RGPAnnotatedHalfSegment2D> operator++();
			bool operator!=(const iteratorforFaces&);
			bool operator==(const iteratorforFaces&);
			std::vector<RGPAnnotatedHalfSegment2D> *ptr;
	};

	class iteratorforHoles
	{
		public:
			iteratorforHoles(std::vector<RGPAnnotatedHalfSegment2D>*);
			std::vector<RGPAnnotatedHalfSegment2D> operator*();
			std::vector<RGPAnnotatedHalfSegment2D> operator++(int);
			std::vector<RGPAnnotatedHalfSegment2D> operator++();
			bool operator!=(const iteratorforHoles&);
			bool operator==(const iteratorforHoles&);
			std::vector<RGPAnnotatedHalfSegment2D> *ptr;
	};

	iteratorforHoles beginHoles();
	iteratorforHoles endHoles();
	iteratorforFaces beginFaces();
	iteratorforFaces endFaces();

	// Methods
	Number area();
	bool isEmptyRegion();
	int getNumberOfFaces();
	int getNumberOfHoles();
	bool operator==(const Region2DImpl &p2d);
	bool operator!=(const Region2DImpl &p2d);
	bool addFace(std::vector<RGPSegment2D>);
	bool removeFace(int index);	                                // Removes a region at specified index
	RGPSegment2D getBoundingBox();

private:
	class Region2DImplStore;
	Number computeArea();
	void sortAnnotatedHS(std::vector<RGPAnnotatedHalfSegment2D> vec);
	void mergeSort(std::vector<RGPAnnotatedHalfSegment2D> &left, std::vector<RGPAnnotatedHalfSegment2D> &right, std::vector<RGPAnnotatedHalfSegment2D> &bars);
	bool parseWDR(std::string inputString);
	Number computeDirection(RGPPoint2D pi, RGPPoint2D pj, RGPPoint2D pk); 
	bool doSegmentsIntersect(RGPSegment2D a, RGPSegment2D b);
	bool validateRegion();
	Number getAreaOfCycle(std::vector<RGPAnnotatedHalfSegment2D> vectorOfSegments);
	Region2DImplStore *handle;
	std::vector<RGPAnnotatedHalfSegment2D> constructRegion(std::string formattedInputString);
};

#endif // Region2DImpl_H
