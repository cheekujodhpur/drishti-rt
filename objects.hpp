#ifndef __OBJECTS_HPP_INCLUDED__
#define __OBJECTS_HPP_INCLUDED__
#include "materials.hpp"
#include "ray.hpp"
#include <vector>

class object{

protected:
	material mat;
public:
	object(){}
	// object(material m):mat(m){}
	void setMaterial(material m);
	virtual double intersect(ray Ray) = 0; //abstract intersect function
};

class sphere: public object{
	std::vector<double> center;
	double radius;
public:
	sphere(){}
	// sphere(material m):object(m){}
	double getRadius();
	std::vector<double> getCenter();
	void setRadius(double r);
	void setCenter(std::vector<double> center0);
	double intersect(ray Ray);
};

class cylinder: public object{
	
	double radius;
	double height;
	std::vector<double> axis;
	std::vector<double> top_center;

	public:
	cylinder(){}
	double get_radius();
	double get_height();
	std::vector<double> get_axis();
	std::vector<double> get_center();
	double intersect(ray Ray);
	void setRadius(double r);
	void setHeight(double h);
	void set_center(std::vector<double> v);
	void set_axis(std::vector<double> x);
};
#endif