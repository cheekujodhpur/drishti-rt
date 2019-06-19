#ifndef __OBJECTS_HPP_INCLUDED__
#define __OBJECTS_HPP_INCLUDED__
#include "materials.hpp"
#include "materials.cpp"

#include<vector>
using namespace std;

class object{

protected:
	material mat;
public:
	object(){}
	// object(material m):mat(m){}
	void setMaterial(material m);
	virtual vector<double> intersect(ray Ray) = 0; //abstract intersect function
};

class sphere: public object{
	vector<double> center;
	double radius;
public:
	sphere(){}
	// sphere(material m):object(m){}
	double getRadius();
	vector<double> getCenter();
	void setRadius(double r);
	void setCenter(vector<double> center0);
	vector<double> intersect(ray Ray);
};
#endif