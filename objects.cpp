#include "objects.hpp"
#include<limits>
using namespace std;
double INF = numeric_limits<double>::infinity();

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
	vector<double> dirn = Ray.get_direction;
	vector<double> origin_ray = Ray.get_origin;
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

	double a = 1;                                                // return normalised direction.
	double b = 2*(xd*(x0-xc) + yd*(y0-yc) + zd*(z0-zc));
	double c = (x0-xc)*(x0-xc) + (y0-yc)*(y0-yc) + (z0-zc)*(z0-zc) - r*r;

	double d = b*b - 4*c;
	vector<double> v(3,INF);                               //returning a vector containing all three coordinates as infinity when ray doesnt intersect.
	if(d<0)
	{
		return v;
	}
	else
	{
		double t0 = (-b - sqrt(d))/2;
		double t1 = (-b + sqrt(d))/2;

		if((t0 < 0) && (t1 < 0))                               // t cant be negative by definition of ray.
			return v;
		else
		{
			if((t0 > 0) && (t1 > 0))
			{													//we need first positive root
				double t = min(t0,t1);
				return Ray.get_point(t);
			}
			else
			{
				double t = max(t0,t1);
				if(t>0)											//take the positive one amongst both.
					return Ray.get_point(t);
				else
					return v;
			}
		}
	}

	//find intersection with Ray
	//return point_of_int;
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
vector<double> cylinder::get_axis()
{
	return axis;
}

vector<double> cylinder::get_center()
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

void cylinder::set_axis(vector<double> x)
{
	axis = x;
}

void cylinder::set_center(vector<double> v)
{
	top_center = v;
}

vector<double> cylinder::intersect(ray Ray)
{
	
}
//set functions remaining for cylinder and intersect