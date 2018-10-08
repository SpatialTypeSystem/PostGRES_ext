#ifndef LINE2D_H
#define LINE2D_H

#include "Number.h"
#include "RGP.h"
#include <string>
#include <vector>

class Line2D{
public:
	// Constructors
	Line2D();
	Line2D(std::vector<RGPSegment2D> listOfSegments);
	Line2D(std::string listOfLine2DString);
	Line2D(std::ifstream& file); // Send in file for constructor
	~Line2D();

	// Methods
	std::string getLineString(); // Get the line as human readable ASCII string
	static bool isEmptyLine();
	int getNumberOfSegments();	// Get the total number of RGPSegment2Ds listed
	std::vector<RGPSegment2D> getBoundingBox();
	bool operator==(const Line2D &l2d);	// Override of operator == to check equality of two Line2Ds
	bool operator!=(const Line2D &l2d);	// Override of operator != to check inequality of two Line2Ds
	bool add(RGPSegment2D rgpSeg2d);	// Adds a new RGPSegment2D 
	bool update(int index, RGPSegment2D rgpSeg2d);	// Updates RGPSegment2D existing at specified index
	bool remove(int index);	// Removes a RGPSegment2D at specified index
	RGPSegment2D operator[](int index);	// Retrieves a RGPSegment2D at specified index

	class Line2DImpl {
		public:
			Line2DImpl(Line2D *l2D);
			
		private:
			std::vector<RGPSegment2D> vecOfRGPSegments;
	};
	
	private:	
		// Fields
		std::vector<RGPSegment2D> vecOfRGPSegments;
};

#endif //LINE2D
