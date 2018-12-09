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
	Region2DImpl(std::vector<RGPAnnotatedHalfSegment2D> listOfRegions);
	Region2DImpl();
	Region2DImpl(std::string listOfRegion2DString);
	Region2DImpl(std::ifstream& file); // Send in file for constructor (possibly .txt)
	~Region2DImpl();

	// Methods
	std::string getRegionString();                          // Get the region as human readable ASCII string
	Number area();
	bool isEmptyRegion(Region2DImpl region);
	bool isValidRegion(Region2DImpl region);
	int getNumberOfFaces();
	std::vector<RGPSegment2D> getBoundingBox();
	bool operator==(const Region2DImpl &p2d);
	bool operator!=(const Region2DImpl &p2d);
	std::vector<RGPSegment2D> getCycle(int index);
	std::vector<RGPAnnotatedHalfSegment2D> getFace(int index);
	bool addFace(std::vector<RGPSegment2D>);
	bool update(int index, std::vector<RGPSegment2D>);	// Updates a whole region at specified index
	bool remove(int index);	                                // Removes a region at specified index
	std::vector<RGPSegment2D> operator[](int index);	// Retrieves a region at specified index

private:
	class Region2DImplStore;
	bool parseWDR(std::string inputString);
	Number getAreaOfCycle(std::vector<RGPAnnotatedHalfSegment2D> vectorOfSegments);
	Region2DImplStore *handle;
	std::vector<RGPAnnotatedHalfSegment2D> constructRegion(std::string formattedInputString);
};

#endif // Region2DImpl_H
