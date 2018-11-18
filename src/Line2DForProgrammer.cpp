#include "Line2D.h"
#include "Line2DForProgrammer.h"
#include <exception>

struct Line2DForProgrammer::Line2DImplStore {
	// data
	std::vector<RGPHalfSegment2D> vectorOfSegments;
	
	// constructors
	Line2DImplStore(std::vector<RGPHalfSegment2D> listOfSegments)
	{
		vectorOfSegments = listOfSegments;
	}

	Line2DImplStore(std::string listOfLine2DString)
	{
		//TODO
		vectorOfSegments = parseStringToVectorOfLines(listOfLine2DString);
	}

	Line2DImplStore(std::ifstream& file)
	{
		std::string inputString;
		if(file.is_open())
		{
			std::stringstream strBuffer;
			strBuffer << file.rdbuf();
			inputString = strBuffer;
		}
		else
		{
			throw std::exception("Error while reading the file");
		}

		//TODO
		vectorOfSegments = parseStringToVectorOfLines(inputString);
	}
};

Line2DForProgrammer::Line2DForProgrammer(std::vector<RGPHalfSegment2D> listOfSegments)
{
	impl = new Line2DImplStore(listOfSegments);
}

Line2DForProgrammer::Line2DForProgrammer(std::string listOfLine2DString)
{
	impl = new Line2DImplStore(listOfLine2DString);
}

Line2DForProgrammer::Line2DForProgrammer(std::ifstream& file) // Send in file for constructor
{
	impl = new Line2DImplStore(file);
}

Line2DForProgrammer::~Line2DForProgrammer()
{
	impl = nullptr;
}

// Methods
std::string Line2DForProgrammer::getLineString() // Get the line as human readable ASCII string
{
	std::string resultString;
	if(!isEmptyPoint()) 
	{
		resultString += "(";
		for (RGPHalfSegment2D rgpLine : impl->vectorOfSegments) 
		{
			std::ostringstream stream;
			stream << rgpLine;
			std::string str =  stream.str();
			
			resultString += str;
			resultString += ",";
		}
		resultString += ")";
	}

	return resultString;
}

// static
bool Line2DForProgrammer::isEmptyLine()
{
	return impl->vectorOfSegments.empty();
}

int Line2DForProgrammer::Line2DForProgrammer::getNumberOfSegments()
{
	return impl->vectorOfSegments.size();
}

std::vector<RGPSegment2D> Line2DForProgrammer::getBoundingBox()
{
	//TODO
	//Call convex hull implementation
	
	return NULL;
}

bool Line2DForProgrammer::add(RGPSegment2D rgp2d)
{
	try
	{
		int i = 0;
		while(rgp2d > impl->vectorOfSegments[i])
			i++;
		impl->vectorOfSegments.insert(impl->vectorOfSegments.begin()+i, rgp2d)
	}
	catch(exception& e)
	{
		return false;
	}
	return true;
}

bool Line2DForProgrammer::remove(int index)
{
	try
	{
		impl->vectorOfSegments.erase(index);
	}
	catch(exception& e)
	{
		return false;
	}
	return true;
}

bool update(int index, RGPSegment2D rgps2d)
{
	try
    {
		vectorOfSegments.erase(index);
		add(rgps2d);
    }
    catch(exception& e)
    {
        return false;
    }
    return true;
}

bool Line2DForProgrammer::operator==(const Line2D &l2d)
{
	int i = 0;
	if(impl->vectorOfSegments.size() != l2d->poi->impl->vectorOfSegments.size()){
		return false;
	}
	
	while(i < l2d->poi->impl->vectorOfSegments.size())
    {
		if(impl->vectorOfSegments[i] != l2d->poi->impl->vectorOfSegments[i])
			return false;
		else
			i++;
	}
	return true;
}

bool Line2DForProgrammer::operator!=(const Line2D &l2d)
{
	int i = 0;
	if(impl->vectorOfSegments.size() != l2d->poi->impl->vectorOfSegments.size()){
		return true;
	}

	while(i < l2d->poi->impl->vectorOfSegments.size())
    {
		if(impl->vectorOfSegments[i] != l2d->poi->impl->vectorOfSegments[i])
			return true;
		else
			i++;
	}
	return false;
}

RGPSegment2D Line2DForProgrammer::operator[](int index)
{
	return impl->vectorOfSegments[index];
}
