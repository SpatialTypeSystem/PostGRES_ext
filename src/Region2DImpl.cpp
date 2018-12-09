#include "Region2DImpl.h"
#include<map>

struct Region2DImpl::Region2DImplStore 
{
	std::vector<RGPAnnotatedHalfSegment2D> vectorOfAnnHalfSegments;
	std::vector<std::vector<RGPAnnotatedHalfSegment2D>> vectorOfFaces;
	std::vector<std::vector<RGPAnnotatedHalfSegment2D>> vectorOfHoles;
	std::map<int,int> faceToHoleRelationMap;
	std::vector<RGPSegment2D> boundingBox;
	Number areaOfRegion;
};

//Constructors
Region2DImpl::Region2DImpl(std::string listOfRegion2DString)
{
	handle = new Region2DImplStore;
	bool result = parseWDR(listOfRegion2DString);
	if(result == true)
	{
		bool isValid = validateRegion();
		if(isValid == false)
		{
			throw std::invalid_argument("Invalid Constructed Region");
		}
		sortAnnotatedHS(handle->vectorOfAnnHalfSegments);
	}
	else
	{
		throw std::invalid_argument("Invalid Constructed Region");
	}
}

// Sorts all the annotated half segments using mergeSort technique
void Region2DImpl::sortAnnotatedHS(std::vector<RGPAnnotatedHalfSegment2D> vec)
{
	if(vec.size() < 1)
	{
		int mid = vec.size() / 2;
		// Partition through midway for merge sort
		std::vector<RGPAnnotatedHalfSegment2D> l;
		std::vector<RGPAnnotatedHalfSegment2D> r;

		for (size_t j = 0; j < mid; j++)
			l.push_back(vec[j]);
		for (size_t j = 0; j < (vec.size()) - mid; j++)
			r.push_back(vec[mid + j]);

		sortAnnotatedHS(l);
		sortAnnotatedHS(r);
		mergeSort(l, r, vec);
	}
}

// merge sort internal function used for sorting the annotated half segments
void Region2DImpl::mergeSort(std::vector<RGPAnnotatedHalfSegment2D> &left, std::vector<RGPAnnotatedHalfSegment2D> &right, std::vector<RGPAnnotatedHalfSegment2D> &bars)
{
	int nL = left.size();
    int nR = right.size();
    int i = 0, j = 0, k = 0;

    while (j < nL && k < nR) 
    {
        if (left[j] <=
		right[k]) {
            bars[i] = left[j];
            j++;
        }
        else {
            bars[i] = right[k];
            k++;
        }
        i++;
    }
    while (j < nL) {
        bars[i] = left[j];
        j++; i++;
    }
    while (k < nR) {
        bars[i] = right[k];
        k++; i++;
    }
}

// Computes the area of a region input 
// This has been used to compute areas of individual cycles of a region
Number Region2DImpl::computeArea()
{
	// compute area of all the faces
	Number tfaceArea("0");
	for(int i=0; i<handle->vectorOfFaces.size(); i++)
	{
		Number area = getAreaOfCycle(handle->vectorOfFaces[i]);
		if(area <= Number("0"))
		{
			return Number("0");
		}
		tfaceArea = tfaceArea + area;
	}
	// compute area of all the holes
	Number tholeArea("0");
	for(int i=0; i<handle->vectorOfHoles.size(); i++)
	{
		Number area = getAreaOfCycle(handle->vectorOfHoles[i]);
		if(area <= Number("0"))
		{
			return Number("0");
		}
		tholeArea = tholeArea + area;
	}
	handle->areaOfRegion = tfaceArea - tholeArea;
	return handle->areaOfRegion;
}

// Validates a region input according to the face and cycle information
bool Region2DImpl::validateRegion()
{
	// check areas if adding upto positive Number
	std::vector<Number> faceAreas;
	std::vector<Number> holeAreas;

	Number tfaceArea("0");
	for(int i=0; i<handle->vectorOfFaces.size(); i++)
	{
		Number area = getAreaOfCycle(handle->vectorOfFaces[i]);
		if(area <= Number("0"))
		{
			return false;
		}
		faceAreas.push_back(area);
		tfaceArea = tfaceArea + area;
	}
	Number tholeArea("0");
	for(int i=0; i<handle->vectorOfHoles.size(); i++)
	{
		Number area = getAreaOfCycle(handle->vectorOfHoles[i]);
		if(area <= Number("0"))
		{
			return false;
		}
		holeAreas.push_back(area);
		tholeArea = tholeArea + area;
	}

	// The total area of faces when subtracted by that of holes has to be a positive number
	handle->areaOfRegion = tfaceArea - tholeArea;	
	if(handle->areaOfRegion <= Number("0"))
	{
		return false;
	}

	// Check if all holes are contained in their respective faces
	std::map<int, int>::iterator itr; 
	int faceIndex = 0;
	int holeIndex = 0;
	for (itr = handle->faceToHoleRelationMap.begin(); itr != handle->faceToHoleRelationMap.end(); ++itr) { 			
		Number fArea = faceAreas[faceIndex];
		Number hArea("0");
		for(int i=holeIndex; i<holeIndex + itr->second; i++)
		{
			hArea = hArea + holeAreas[i];
		}
			
		// Check if the face area is more than that of all the holes inside it
		if(fArea - hArea <= Number("0"))
		{
			return false;
		}

		faceIndex++;
		holeIndex = holeIndex + itr->second;
	} 		

	std::vector<RGPAnnotatedHalfSegment2D> allCyclesVec;
	//Check if any 2 cycles are intersecting
	for(int i=0; i<handle->vectorOfFaces.size(); i++)
	{
		for(int j=0; j<handle->vectorOfFaces[i].size(); j++)
		{
			allCyclesVec.push_back(handle->vectorOfFaces[i][j]);
		}
	}
	for(int i=0; i<handle->vectorOfHoles.size(); i++)
	{
		for(int j=0; j<handle->vectorOfHoles[i].size(); j++)
		{
			allCyclesVec.push_back(handle->vectorOfHoles[i][j]);
		}
	}
	handle->vectorOfAnnHalfSegments = allCyclesVec;

	// Check for intersection between any two segments of the region including all the faces and cycles
	for(int i=0; i<allCyclesVec.size(); i=i+2)
	{
		for(int j=i+2; j<allCyclesVec.size(); j=j+2)
		{
			// check intersection for segments
			bool flag = doSegmentsIntersect(allCyclesVec[i].segment,allCyclesVec[j].segment);
			if(flag == true)
			{
				return false;
			}
		}
	}

	return true;
}

// To check if given 2 segments intersect at any point.
// Returns true if they do intersect. false for the other scenario
bool Region2DImpl::doSegmentsIntersect(RGPSegment2D a, RGPSegment2D b) 
{
	RGPPoint2D a_p1 = a.point1;
	RGPPoint2D a_p2 = a.point2;
	RGPPoint2D b_p3 = b.point1;
	RGPPoint2D b_p4 = b.point2;
	
	Number d1 = computeDirection(b_p3,b_p4,a_p1);
	Number d2 = computeDirection(b_p3,b_p4,a_p2);
	Number d3 = computeDirection(a_p1,a_p2,b_p3);
	Number d4 = computeDirection(a_p1,a_p2,b_p4);
	
	Number zero("0");

	if (((d1 > zero && d2 < zero) || (d1 < zero && d2 > zero)) &&
		((d3 > zero && d4 < zero) || (d3 < zero && d4 > zero)))
	{
		return true;	
	}
	else 
	{
		return false;
	}
}

Number Region2DImpl::computeDirection(RGPPoint2D pi, RGPPoint2D pj, RGPPoint2D pk) 
{
	Number g = (pk.x - pi.x)*(pj.y - pi.y) - (pj.x - pi.x)*(pk.y - pi.y);
	return g;
}

// Used for computing the area of a cycle given all the points
Number Region2DImpl::getAreaOfCycle(std::vector<RGPAnnotatedHalfSegment2D> vectorOfSegments) 
{
	Number area("0");
	Number xCoord[vectorOfSegments.size()/2];
	Number yCoord[vectorOfSegments.size()/2];
	int j =0;
	for(int i=0; i<vectorOfSegments.size();i=i+2)
	{
		xCoord[j] = vectorOfSegments[i].dominantPoint.x;
		yCoord[j] = vectorOfSegments[i].dominantPoint.y;
		j++;
	}

	int k = j-1;
	for(int a=0; a<j; a++)
	{
		area = area + (xCoord[k]+xCoord[a]) * (yCoord[k]-yCoord[a]); 
		k = a;
	}	
	if(area < Number("0"))
	{
		area = area * Number("-1");
	}

	return area/Number("2");

}

// Parses the given input string and creates the vector of faces and cycles
bool Region2DImpl::parseWDR(std::string inputString) 
{
	std::map<int,int> faceToHoleMap;
	if(inputString.length() < 2)
	{
		return false;
	}
	
	std::string firstChar = inputString.substr(0,1);
	std::string lastChar = inputString.substr(inputString.length()-1, inputString.length());
	if(firstChar != "[" || lastChar != "]")
	{
		return false;
	}

	std::string notation = inputString.substr(1,3);
	if(notation != "WCR")
	{
		return false;
	}
	
	// formattedString = ((1 1,2 2),(1 1,2 2))&
	std::string formattedString = inputString.substr(4);
	formattedString.erase(formattedString.length()-1,1);

	std::string delimiter = "&";

	int numOfFaces = 1;
	int numOfHoles = 0;
	
	while(formattedString.length() > 0)
	{
		// ((1 1,2 2),(1 1,3 3)) = faceHoleSetString
		int pos = formattedString.find(delimiter);
		std::string faceHoleSetString = formattedString;
		if(pos != -1)
		{
			faceHoleSetString = formattedString.substr(0,pos);
		}

		// (1 1,2 2),(1 1,3 3) = partString
		std::string partString = faceHoleSetString.substr(0,pos);
		partString.erase(0,1);
		partString.erase(partString.length()-1,1);
		
		// 1 1,2 2 = faceSegmentString
		std::vector<RGPPoint2D> facePoints;
		int faceClosingPoint = partString.find(")");
		std::string faceSegmentString = partString.substr(1,faceClosingPoint-1);
		int faceSegmentStringLength = faceSegmentString.length();
		while(faceSegmentString.length() > 0)
		{
			int l = faceSegmentString.find(" ");
			std::string coord1 = faceSegmentString.substr(0,l);
			faceSegmentString.erase(0,l+1);
			int r = faceSegmentString.find(",");
			std::string coord2 = faceSegmentString.substr(0,r);
			if(r == -1) 
			{
				faceSegmentString.erase(0,faceSegmentString.length());
			} 
			else 
			{
				faceSegmentString.erase(0,r+1);
			}
			facePoints.push_back(RGPPoint2D(Number(coord1), Number(coord2)));
		}
		// If start and end point of a cycle are not same, return false
		if(facePoints[0] != facePoints[facePoints.size()-1])
		{
			return false;
		}

		std::vector<RGPAnnotatedHalfSegment2D> emptyFaceVec;
		handle->vectorOfFaces.push_back(emptyFaceVec);
		
		// Fill the currently parsed vector into the face vector of region
		for(int i=0; i<facePoints.size()-1;i++)
		{
			RGPSegment2D seg(facePoints[i],facePoints[i+1]);
			RGPAnnotatedHalfSegment2D annHS(seg,facePoints[i],true);
			RGPAnnotatedHalfSegment2D annHS2(seg,facePoints[i+1],true);
			handle->vectorOfFaces[numOfFaces-1].push_back(annHS);
			handle->vectorOfFaces[numOfFaces-1].push_back(annHS2);
		}

		std::vector<std::vector<RGPPoint2D>> holePointVector;
		std::string holesString = partString.substr(faceSegmentStringLength+3, partString.length());
		
		while(holesString.find(")") != std::string::npos)
		{
			int holeClosingPoint = holesString.find(")");
			std::string holeSegmentString = holesString.substr(1,holeClosingPoint-1);
			int holeSegmentStringLength = holeSegmentString.length();
			std::vector<RGPPoint2D> emptyVec;
			std::vector<RGPAnnotatedHalfSegment2D> emptyHoleVec;
			holePointVector.push_back(emptyVec);
			handle->vectorOfHoles.push_back(emptyHoleVec);
			while(holeSegmentString.length() > 0)
			{
				int l = holeSegmentString.find(" ");
				std::string coord1 = holeSegmentString.substr(0,l);
				holeSegmentString.erase(0,l+1);
				int r = holeSegmentString.find(",");
				std::string coord2 = holeSegmentString.substr(0,r);
				if(r == -1) 
				{
					holeSegmentString.erase(0,holeSegmentString.length());
				} 
				else 
				{
					holeSegmentString.erase(0,r+1);
				}

				holePointVector[numOfHoles].push_back(RGPPoint2D(Number(coord1), Number(coord2)));
			}

			std::vector hole = holePointVector[numOfHoles];
			// Check if the first and last point for a hole cycle is the same
			if(hole[0] != hole[hole.size()-1])
			{
				return false;
			}

			// Add the parsed hole cycle into the vector of holes of the region
			for(int i=0; i<hole.size()-1;i++)
			{
				RGPSegment2D seg(hole[i],hole[i+1]);
				RGPAnnotatedHalfSegment2D annHS(seg,hole[i],true);
				RGPAnnotatedHalfSegment2D annHS2(seg,hole[i+1],true);
				handle->vectorOfHoles[numOfHoles].push_back(annHS);
				handle->vectorOfHoles[numOfHoles].push_back(annHS2);
			}

			holesString = holesString.substr(holeSegmentStringLength+2, holesString.length());
			if(holesString.length() != 0 && holesString.substr(0,1) == ",")
			{
					holesString.erase(0,1);
			}
			// Keep track of number of holes being added
			numOfHoles++;
		}

		// Maintain the relation of face to corresponding hole
		faceToHoleMap.insert(std::pair<int, int>(numOfFaces,numOfHoles));
		numOfFaces++;	

		int faceHoleSetStringLength = faceHoleSetString.length();
		if(pos != -1)
		{
			faceHoleSetStringLength++;
		}
		formattedString = formattedString.substr(faceHoleSetStringLength,formattedString.length());		
	}

	std::map<int, int>::iterator itr; 
	handle->faceToHoleRelationMap = faceToHoleMap;
	return true;
}

Region2DImpl::~Region2DImpl()
{
	delete handle;
}

Number Region2DImpl::area()
{
	return handle->areaOfRegion;
}

bool Region2DImpl::isEmptyRegion()
{
	return handle->vectorOfFaces.empty();
}

int Region2DImpl::getNumberOfFaces()
{
	return handle->vectorOfFaces.size();
}

int Region2DImpl::getNumberOfHoles()
{
	return handle->vectorOfHoles.size();
}

RGPSegment2D Region2DImpl::getBoundingBox()
{
	std::vector<RGPAnnotatedHalfSegment2D> halfSegments;
	halfSegments = handle->vectorOfAnnHalfSegments;

	//p1 is the first point of the bounding box segment
	RGPPoint2D p1(halfSegments[0].segment.point1.x,halfSegments[0].segment.point1.y);
	RGPPoint2D p2(halfSegments[halfSegments.size()-1].segment.point2.x,halfSegments[halfSegments.size()-1].segment.point2.y);
	auto maxy = halfSegments[0].segment.point2.y;

	//iterate through the loop to find max y coordinate in the given lis of points
	for(auto it = halfSegments.begin();it!= halfSegments.end();it++)
	{
		if(maxy<(*it).segment.point1.y)
			maxy = (*it).segment.point1.y;
		if(maxy<(*it).segment.point2.y)
			maxy = (*it).segment.point2.y;	
	}

	//we make the next point taking the x of p2 and maxy found in the above loop
	RGPSegment2D seg(p1,RGPPoint2D(p2.x,maxy));
	handle->boundingBox.push_back(seg);
	//returing the diagonal that tells us the bounding box
	return handle->boundingBox[0];
}

bool Region2DImpl::addFace(std::vector<RGPSegment2D> faceVec)
{
	std::vector<RGPAnnotatedHalfSegment2D> vecToAdd;
	// Iterate and create annotated half segments
	for(int i=0; i<faceVec.size(); i++)
	{
		faceVec[i];
		RGPAnnotatedHalfSegment2D a(faceVec[i],faceVec[i].point1,true);
		RGPAnnotatedHalfSegment2D b(faceVec[i],faceVec[i].point2,true);
		vecToAdd.push_back(a);
		vecToAdd.push_back(b);
		handle->vectorOfAnnHalfSegments.push_back(a);
		handle->vectorOfAnnHalfSegments.push_back(b);
	}
	handle->vectorOfFaces.push_back(vecToAdd);
	handle->faceToHoleRelationMap.insert(std::pair<int, int>(handle->vectorOfFaces.size()+1,0));
	
	// Might throw exception as and when the validation fails
	validateRegion();
	// Sort the newly added half segments as well
	sortAnnotatedHS(handle->vectorOfAnnHalfSegments);
}

bool Region2DImpl::operator==(const Region2DImpl &p2d)
{
	int i = 0;
	//Check if size equal
	if(handle->vectorOfAnnHalfSegments.size() != p2d.handle->vectorOfAnnHalfSegments.size())
	{
		return false;
	}
	
	// Check iteratively if each segment is equal to other
	while(i < p2d.handle->vectorOfAnnHalfSegments.size())
    {
		if(handle->vectorOfAnnHalfSegments[i] != p2d.handle->vectorOfAnnHalfSegments[i])
		{
			return false;
		}
		else
			i++;
	}
	return true;
}

bool Region2DImpl::operator!=(const Region2DImpl &p2d)
{
	int i = 0;
	//Check if size equal
	if(handle->vectorOfAnnHalfSegments.size() != p2d.handle->vectorOfAnnHalfSegments.size())
	{
		return true;
	}
	
	// Check iteratively if each segment is equal to other
	while(i < p2d.handle->vectorOfAnnHalfSegments.size())
    {
		if(handle->vectorOfAnnHalfSegments[i] != p2d.handle->vectorOfAnnHalfSegments[i])
		{
			return true;
		}
		else
			i++;
	}
	return false;
}

// Iterators for faces and hole cycles
Region2DImpl::iteratorforFaces::iteratorforFaces(std::vector<RGPAnnotatedHalfSegment2D> *ptr1)
{
	ptr = ptr1;
}

std::vector<RGPAnnotatedHalfSegment2D> Region2DImpl::iteratorforFaces::operator*()
{
	return *ptr;
}

std::vector<RGPAnnotatedHalfSegment2D> Region2DImpl::iteratorforFaces::operator++(int junk)
{
	std::vector<RGPAnnotatedHalfSegment2D> *ptr1;
	ptr1 = ptr;
	ptr++;
	return *ptr1;
}

std::vector<RGPAnnotatedHalfSegment2D> Region2DImpl::iteratorforFaces::operator++()
{
	ptr++;
	return *ptr;
}

bool Region2DImpl::iteratorforFaces::operator!=(const iteratorforFaces &it)
{
	if(it.ptr==ptr)
		return false;
	return true;
}

bool Region2DImpl::iteratorforFaces::operator==(const iteratorforFaces &it)
{
	if(it.ptr!=ptr)
		return false;
	return true;
}

Region2DImpl::iteratorforFaces Region2DImpl::beginFaces()
{
	std::vector<RGPAnnotatedHalfSegment2D> *ptr = &(handle->vectorOfFaces[0]);
	return iteratorforFaces(ptr);
}

Region2DImpl::iteratorforFaces Region2DImpl::endFaces()
{
	int t = handle->vectorOfFaces.size();
	return (iteratorforFaces(&(handle->vectorOfFaces[t-1])));
}

Region2DImpl::iteratorforHoles::iteratorforHoles(std::vector<RGPAnnotatedHalfSegment2D> *ptr1)
{
	ptr = ptr1;
}

std::vector<RGPAnnotatedHalfSegment2D> Region2DImpl::iteratorforHoles::operator*()
{
	return *ptr;
}

std::vector<RGPAnnotatedHalfSegment2D> Region2DImpl::iteratorforHoles::operator++(int junk)
{
	std::vector<RGPAnnotatedHalfSegment2D> *ptr1;
	ptr1 = ptr;
	ptr++;
	return *ptr1;
}

std::vector<RGPAnnotatedHalfSegment2D> Region2DImpl::iteratorforHoles::operator++()
{
	ptr++;
	return *ptr;
}

bool Region2DImpl::iteratorforHoles::operator!=(const iteratorforHoles &it)
{
	if(it.ptr==ptr)
		return false;
	return true;
}

bool Region2DImpl::iteratorforHoles::operator==(const iteratorforHoles &it)
{
	if(it.ptr!=ptr)
		return false;
	return true;
}

Region2DImpl::iteratorforHoles Region2DImpl::beginHoles()
{
	std::vector<RGPAnnotatedHalfSegment2D> *ptr = &(handle->vectorOfHoles[0]);
	return iteratorforHoles(ptr);
}

Region2DImpl::iteratorforHoles Region2DImpl::endHoles()
{
	int t = handle->vectorOfHoles.size();
	return (iteratorforHoles(&(handle->vectorOfHoles[t-1])));
}