#ifndef __OBJECTS_HPP_INCLUDED__
#define __OBJECTS_HPP_INCLUDED__
#include "materials.hpp"
#include "ray.hpp"
#include "vector.hpp"
#include <memory>

class object{

protected:
	material* mat;
	static const double eff_zero_intersection = 1e-8;
public:
	object(){}
	// object(material m):mat(m){}
	void setMaterial(material* m);
	material* getMaterial();
	virtual double intersect(ray Ray) = 0; //abstract intersect function
};

class sphere: public object{
	vec center;
	double radius;
public:
	sphere(){}
	// sphere(material m):object(m){}
	double getRadius();
	vec getCenter();
	void setRadius(double r);
	void setCenter(vec center0);
	double intersect(ray Ray);
	
};

class cylinder: public object{
	
	double radius;
	double height;
	vec axis;
	vec top_center;

	public:
	cylinder(){}
	double get_radius();
	double get_height();
	vec get_axis();
	vec get_center();
	double intersect(ray Ray);
	void setRadius(double r);
	void setHeight(double h);
	void set_center(vec v);
	void set_axis(vec x);
};
#endif