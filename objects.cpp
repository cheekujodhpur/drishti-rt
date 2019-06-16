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