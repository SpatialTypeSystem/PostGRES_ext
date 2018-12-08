#include "Point2DImpl.h"
#include "RGPPoint2D.h"
#include <Number.h>
#include <vector>


struct Point2DImpl::Point2DImplStore 
{
	std::vector<RGPPoint2D> vectorOfPoints;
	std::vector<RGPPoint2D> boundingBox;
};

Point2DImpl::iterator::iterator(RGPPoint2D *ptr1)
{
	ptr = ptr1;
}

RGPPoint2D Point2DImpl::iterator::operator*()
{
	return *ptr;
}

RGPPoint2D Point2DImpl::iterator::operator++(int junk)
{
	RGPPoint2D *ptr1;
	ptr1 = ptr;
	ptr++;
	return *ptr1;
}

RGPPoint2D Point2DImpl::iterator::operator++()
{
	ptr++;
	return *ptr;
}

bool Point2DImpl::iterator::operator!=(const iterator &it)
{
	if(it.ptr==ptr)
		return false;
	return true;
}
bool Point2DImpl::iterator::operator==(const iterator &it)
{
	if(it.ptr!=ptr)
		return false;
	return true;
}

Point2DImpl::iterator Point2DImpl::begin()
{
	RGPPoint2D *ptr = &(handle->vectorOfPoints[0]);
	return iterator(ptr);
}

Point2DImpl::iterator Point2DImpl::end()
{
	int t = handle->vectorOfPoints.size();
	return (iterator(&(handle->vectorOfPoints[t-1])));
}

//Constructors
Point2DImpl::Point2DImpl(std::vector<RGPPoint2D> listOfPoints)
{
	handle = new Point2DImplStore;
	handle->vectorOfPoints = listOfPoints;
}

Point2DImpl::Point2DImpl()
{
	handle = new Point2DImplStore;
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
	handle = new Point2DImplStore;
	std::cout<< "inside" << "\n";
	if(parseStringToVectorOfPoints(listOfPoint2DString))
	{
		std::cout<<"All points are added successfully"<<std::endl;
	}
	else
	{
		std::cout<<"Input Format is not correct"<<std::endl;
	}
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

void Point2DImpl::printAllPoints()
{
	std::cout<<"(";
	std::vector<RGPPoint2D> x = handle->vectorOfPoints;
	for(auto i = x.begin(); i!=x.end(); i++)
		std::cout<<*i;
	std::cout<<")";
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

Point2DImpl Point2DImpl::getBoundingBox()
{
	std::vector<RGPPoint2D> box;
	box = handle->boundingBox;
	Point2DImpl pt(box);
	return pt;
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

Point2DImpl Point2DImpl::operator[](int index)
{
	std::vector<RGPPoint2D> t;
	t.push_back(handle->vectorOfPoints[index]);
	Point2DImpl temp(t);
	return temp;
}

Point2DImpl Point2DImpl::operator=(const Point2DImpl &p2d)
{
	handle->vectorOfPoints.clear();
	handle->vectorOfPoints = p2d.handle->vectorOfPoints;
}

bool Point2DImpl::add(RGPPoint2D rgpp2d)
{
	
	//handle->vectorOfPoints.push_back(rgpp2d);
	try
    {
		if(handle->vectorOfPoints.empty()) {
			handle->vectorOfPoints.push_back(rgpp2d);
			return true;
		}

		int i=0;
		while(rgpp2d > handle->vectorOfPoints[i] && i < handle->vectorOfPoints.size())
			i++;
		if(i==handle->vectorOfPoints.size())
			handle->vectorOfPoints.push_back(rgpp2d);
		else
			handle->vectorOfPoints.insert(handle->vectorOfPoints.begin()+i, rgpp2d);
	}
	catch(int e)
    {
		return false;
	}
	return true;
}

bool Point2DImpl::update(Point2DImpl::iterator it, RGPPoint2D rgpp2d)
{
	try
    {
		if(isEmptyPoint())
		{
			return false;
		}
		else
		{
			int index = it.ptr - &(handle->vectorOfPoints[0]);
			handle->vectorOfPoints.erase(handle->vectorOfPoints.begin()+index);
			add(rgpp2d);
			pointSort(handle->vectorOfPoints);
		}
    }
    catch(int e)
    {
        return false;
    }
    return true;
}

bool Point2DImpl::remove(Point2DImpl::iterator it)
{
	try
    {
		if(isEmptyPoint())
		{
			return false;
		}
		else
		{
			int index = it.ptr - &(handle->vectorOfPoints[0]);
        	handle->vectorOfPoints.erase(handle->vectorOfPoints.begin()+index);
		}
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
	std::vector<RGPPoint2D> points;
	int pos,fl=0;
	std::string num1,num2;
	std::string s =st;
	std::vector<Number> nums;
	std::string delimeter = ",";
	s.erase(0,1);
	s.erase(s.length()-1,1);
  	s.append(",");
	std::cout << s << "\n";
	pos = s.find(delimeter);
	std::cout << pos << "\n";
	try{
		while(pos!= std::string::npos)
		{
			std::string a = s.substr(0, pos);
			if(a.length()>=2)
			{
				try
				{
					if(a[0]=='(')
					{
						std::string temp = "";
						int i =1;
						while(((a[i]<='9'&&a[i]>='0')||a[i]=='.'||a[i]=='-')&&i<a.length())
						{
							temp+=a[i];
							i++;
						} 
						num1=temp;
					}
					else if(a[a.length()-1]==')')
					{
						std::string temp = "";
						int i =0;
						while(((a[i]<='9'&&a[i]>='0')||a[i]=='.'||a[i]=='-')&&i<a.length()-1)
						{
							temp+=a[i];
							i++;
						} 
						num2=temp;
            			std::cout<<"num1 and num2 is "<<num1<<" "<<num2<<std::endl;	//numbers from points
						points.push_back(RGPPoint2D(Number(num1),Number(num2)));
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
      		std::cout <<"string s is"<< s << "\n";
			pos = s.find(delimeter);
		}
	}
	catch(int e){
		return false;
	}
	pointSort(points);

	std::vector<RGPPoint2D> boundPoints;
	boundPoints.push_back(points[0]);
	auto maxy = points[0].y;
	std::cout<<"bound box \n";
	for(auto it = points.begin(); it!=points.end() ;it++)
	{
		if((*it).y > maxy)
			maxy=(*it).y;
	}
	RGPPoint2D pt(points[points.size() - 1].x,maxy);
	boundPoints.push_back(pt);
	
	std::cout<<std::endl;
	handle->vectorOfPoints = points;
	handle->boundingBox = boundPoints;
	
}
