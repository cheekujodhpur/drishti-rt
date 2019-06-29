#include "objects.hpp"
#include <limits> //infinity()
#include <math.h>

const double INF = std::numeric_limits<double>::infinity();

//object class
void object::setMaterial(material* m)
{
	mat = m;
}
material* object::getMaterial()
{
	return mat;
}

//sphere class
double sphere::getRadius()
{
	return radius;
}
std::vector<double> sphere::getCenter()
{
	return center;
}
void sphere::setRadius(double r)
{
	radius = r;
}
void sphere::setCenter(std::vector<double> center0)
{
	center = center0;
}

double sphere::intersect(ray Ray)
{
	std::vector<double> point_of_int = std::vector<double>(3);
	std::vector<double> dirn = Ray.get_direction();
	std::vector<double> origin_ray = Ray.get_origin();
	double x0 = origin_ray[0];
	double y0 = origin_ray[1];
	double z0 = origin_ray[2];
	double xd = dirn[0];
	double yd = dirn[1];
	double zd = dirn[2];
	double xc = this->center[0];
	double yc = this->center[1];
	double zc = this->center[2];
	double r = this->radius;
	//std::cout<<xc<<" "<<yc<<" "<<r<<std::endl;

	double a = 1;
	double b = 2*(xd*(x0-xc) + yd*(y0-yc) + zd*(z0-zc));
	double c = (x0-xc)*(x0-xc) + (y0-yc)*(y0-yc) + (z0-zc)*(z0-zc) - r*r;

	double d = b*b - 4*c;
	//std::cout<<d<<std::endl;
	if(d<0)
		return INF;
	else
	{
		double t0 = (-b - sqrt(d))/2;
		double t1 = (-b + sqrt(d))/2;

		if((t0 < 0) && (t1 < 0)) //t cant be negative by definition of ray.
			return INF;
		else if((t0 > 0) && (t1 > 0)) 
			return std::min(t0,t1); //we need first positive root
		else
			return std::max(t0,t1); //take the positive one among the two
	}
}

//cylinder class
double cylinder::get_radius()
{
	return radius;
}
double cylinder::get_height()
{
	return height;
}
std::vector<double> cylinder::get_axis()
{
	return axis;
}

std::vector<double> cylinder::get_center()
{
	return top_center;
}

void cylinder::setRadius(double r)
{
	radius = r;
}

void cylinder::setHeight(double h)
{
	height = h;
}

void cylinder::set_axis(std::vector<double> x)
{
	axis = x;
}

void cylinder::set_center(std::vector<double> v)
{
	top_center = v;
}

double cylinder::intersect(ray Ray)
{
	
}
//set functions and intersect remaining for cylinder 