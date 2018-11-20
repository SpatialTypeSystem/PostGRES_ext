#include "Point2DImpl.h"
#include "RGPPoint2D.h"
#include"Number.h"

struct Point2DImpl::Point2DImplStore 
{
	std::vector<RGPPoint2D> vectorOfPoints;
};

//Constructors
Point2DImpl::Point2DImpl(std::vector<RGPPoint2D> listOfPoints)
{
	handle = new Point2DImplStore;
	handle->vectorOfPoints = listOfPoints;
}

Point2DImpl::Point2DImpl(std::ifstream& file)
{
	/*std::string inputString;
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
	vectorOfPoints = parseStringToVectorOfPoints(inputString);
	*/
}

Point2DImpl::Point2DImpl(std::string listOfPoint2DString)
{
	//TODO
	std::cout<< "inside" << "\n";
	parseStringToVectorOfPoints(listOfPoint2DString);
}

Point2DImpl::~Point2DImpl()
{
	//TODO
	//default;
}

bool Point2DImpl::isEmptyPoint()
{
	return handle->vectorOfPoints.empty();
}

// Get the point as human readable ASCII string
std::string Point2DImpl::getPointString() 
{
	std::string resultString = "test";
	/*
	bool p = isEmptyPoint();
	if(p==false) 
	{
		resultString += "(";
		for (RGPPoint2D rgpPoint : vectorOfPoints) 
		{
			std::ostringstream stream;
			stream << rgpPoint;
			std::string str =  stream.str();
			
			resultString += str;
			resultString += ",";
		}
		resultString += ")";
	}
	*/
	return resultString;
}


bool Point2DImpl::isValidPoint()
{
	bool validity = false;
	if(!handle->vectorOfPoints.empty()) 
	{
		//Check for validity
		//TODO
	}

	return validity;
}

int Point2DImpl::getNumberOfPoints()
{
	return handle->vectorOfPoints.size();
}

std::vector<RGPSegment2D> Point2DImpl::getBoundingBox()
{
	//TODO
	//Call convex hull implementation
	
	//return NULL;
}

bool Point2DImpl::operator==(const Point2DImpl &p2d)
{
	int i=0;
	while(i< p2d.handle->vectorOfPoints.size())
    {
		if(handle->vectorOfPoints[i] != p2d.handle->vectorOfPoints[i])
			return false;
		else
			i++;
	}
	if(handle->vectorOfPoints.size() == p2d.handle->vectorOfPoints.size())
		return true;
	else
		return false;
}

bool Point2DImpl::operator!=(const Point2DImpl &p2d)
{
	int i=0;
	if(handle->vectorOfPoints.size() != p2d.handle->vectorOfPoints.size())
		return true;
	while(i< p2d.handle->vectorOfPoints.size())
    {
		if(handle->vectorOfPoints[i] != p2d.handle->vectorOfPoints[i])
			return true;
		else
			i++;
	}
	return false;
}

RGPPoint2D Point2DImpl::operator[](int index)
{
	return handle->vectorOfPoints[index];
}
/*
Point2DImpl Point2DImpl::operator=(const Point2D &p2d)
{
	// Emtpy
}*/

bool Point2DImpl::add(RGPPoint2D rgpp2d)
{
	try
    {
		if(handle->vectorOfPoints.empty()) {
			handle->vectorOfPoints.push_back(rgpp2d);
		}

		int i=0;
		while(rgpp2d > handle->vectorOfPoints[i])
			i++; 
		handle->vectorOfPoints.insert(handle->vectorOfPoints.begin()+i, rgpp2d);
	}
	catch(int e)
    {
		return false;
	}
	return true;
}

bool Point2DImpl::update(std::vector<RGPPoint2D>::iterator it, RGPPoint2D rgpp2d)
{
	try
    {
	    int index = distance(handle->vectorOfPoints.begin(), it);
        handle->vectorOfPoints.erase(handle->vectorOfPoints.begin()+index);
        add(rgpp2d);
    }
    catch(int e)
    {
        return false;
    }
    return true;
}

bool Point2DImpl::remove(std::vector<RGPPoint2D>::iterator it)
{
	try
    {
	    int index = distance(handle->vectorOfPoints.begin(), it);
        handle->vectorOfPoints.erase(handle->vectorOfPoints.begin()+index);
    }
    catch(int e)
    {
        return false;
    }
    return true;
}


void Point2DImpl::pointSort(std::vector<RGPPoint2D> &bar)
{
	if (bar.size() <= 1) 
		return;

    int mid = bar.size() / 2;
    std::vector<RGPPoint2D> l;
    std::vector<RGPPoint2D> r;

    for (size_t j = 0; j < mid;j++)
        l.push_back(bar[j]);
    for (size_t j = 0; j < (bar.size()) - mid; j++)
        r.push_back(bar[mid + j]);

    pointSort(l);
    pointSort(r); 
    mergeSort(l, r, bar);
}


void Point2DImpl::mergeSort(std::vector<RGPPoint2D> &left, std::vector<RGPPoint2D> &right, std::vector<RGPPoint2D> &bars)
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

bool Point2DImpl::parseStringToVectorOfPoints(std::string st)
{
	int pos;
	std::string num1;
	std::string s =st;
	std::string delimeter = ",";
	s.erase(0,1);
	s.erase(s.length()-1,1);
	std::cout << s << "\n";
	pos = s.find(delimeter);
	std::cout << pos << "\n";
	try{
		while(pos!= std::string::npos)
		{
			std::string a = s.substr(0, pos);
			std::cout << a << "\n";
			if(a.length()==2)
			{
				try
				{
					if(a[0]=='(')
					{
						num1 = a[1];
					}
					else if(a[1]==')')
					{
						std::string temp = a[0]+"";
						std::cout << temp << "\t" << num1 << "\n";
						Number q(temp);
						Number p(num1);
						RGPPoint2D poi(p,q);
						add(poi);
					}
					else
						return false;
				}
				catch(int e){
					return false;
				}
			}
			else
			{
				return false;
			}
			s.erase(0, pos + delimeter.length());
			pos = s.find(delimeter);
			
		}
	}
	catch(int e){
		return false;

	}
}