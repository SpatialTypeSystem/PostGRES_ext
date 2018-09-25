class Point2D{
private:
	vector<RGPPoint2D> listOfPoints;
public:
	Point2D();
	Point2D(vector<RGPPoint2D> listOfPoints);
	Point2D(ifstream& file);
	Point2D(string listOfPoint2DString);
	~Point2D(); // Destructor
	String getPointString();  // Get the point as human readable ASCII string
};
