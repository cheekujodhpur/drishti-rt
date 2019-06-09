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
	objects(material m):mat(m);	
};

class sphere{
	vector<double> center;
	double radius;
public:
	  void setRadius(double r);
	  void setCenter(vector<double> center0);
	  
};
#endif