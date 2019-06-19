#include "objects.hpp"

using namespace std;

//object class
void object::setMaterial(material m)
{
	mat = m;
}

//sphere class
double sphere::getRadius()
{
	return radius;
}
vector<double> sphere::getCenter()
{
	return center;
}
void sphere::setRadius(double r)
{
	radius = r;
}
void sphere::setCenter(vector<double> center0)
{
	center = center0;
}
vector<double> sphere::intersect(ray Ray)
{
	vector<double> point_of_int = vector<double>(3);

	//find intersection with Ray
	return point_of_int;
}