#include<iostream>
#include "materials.cpp"
using namespace std;
class object{
protected:
	material mat;
public:
	object(material m){
		mat = m;
	}
}

class sphere{
	vector<double> center(3);
	double radius;
public:
	sphere(double r, vector<double> c, material mat):object(mat){
		radius = r;
		center = c;
	}
}